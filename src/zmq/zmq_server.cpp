//-----------------------------------------------------------------------------
// Copyright © 2016-2025 AMBITECS <info@ambi.biz>
//-----------------------------------------------------------------------------
#include "zmq_server.h"
#include "reg_server.h"
#include "crc_utils.h"

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <regex>

using namespace std::chrono;

// Получаем путь к директории, где находится исполняемый файл
std::filesystem::path get_deploy_root_path() {
    // Путь к текущему исполняемому файлу
    std::filesystem::path exe_path = std::filesystem::canonical("/proc/self/exe").parent_path(); // Linux
    // Или для Windows: GetModuleFileName(NULL, ...)

    // Поднимаемся на уровень выше (из bin в .deploy)
    return exe_path.parent_path(); // Переход из .deploy/bin в .deploy
}

ZmqServer &ZmqServer::instance(const std::string &configPath) {
    static ZmqServer instance(configPath); // Потокобезопасно с C++11
    return instance;
}

ZmqServer::ZmqServer(const std::string& configPath)
        : config_(cfg::ConfigLoader<cfg::ZmqServerConfig>(configPath).getConfig())
        {
    config_.validate();

    // Получаем корень .deploy
    std::filesystem::path deploy_root = get_deploy_root_path();

    // Собираем полный путь к programs_dir
    programs_dir_ = deploy_root / config_.programsDir;
    programs_dir_ = std::filesystem::absolute(programs_dir_);

    // Создаем директорию, если ее нет
    std::filesystem::create_directories(programs_dir_);

    if (config_.debugMode) {
        std::cout << "Programs directory: " << programs_dir_ << std::endl;
    }
}

//ZmqServer::ZmqServer(const cfg::ZmqServerConfig& config)
//        : config_(config) {
//    config_.validate();
//
//}

ZmqServer::~ZmqServer() {
    try {
        stop();
    } catch (...) {
        // Гарантируем отсутствие исключений в деструкторе
    }
}

void ZmqServer::start() {
    if (state_ != ServerState::STOPPED && state_ != ServerState::ERROR) {
        throw ZmqServerException("Server already running or starting");
    }

    changeState(ServerState::STARTING);

    try {
        context_ = std::make_unique<zmq::context_t>(config_.workerThreads);
        initSockets();
        changeState(ServerState::RUNNING);
        startWorkerThreads();
    } catch (...) {
        changeState(ServerState::ERROR);
        throw;
    }
}

void ZmqServer::stop() {
    if (state_ == ServerState::STOPPED || state_ == ServerState::STOPPING) {
        return;
    }

    changeState(ServerState::STOPPING);
    stop_tag_processing_ = true;
    tag_queue_cv_.notify_all();
    stopWorkerThreads();
    cleanupSockets();
    changeState(ServerState::STOPPED);
}

void ZmqServer::setMessageHandler(std::shared_ptr<IMessageHandler> handler) {
    message_handler_ = std::move(handler);
}

void ZmqServer::pushTagUpdates(const std::vector<Tag>& tags) {
    if (state_ != ServerState::RUNNING) return;

    std::lock_guard<std::mutex> lock(tag_queue_mutex_);
    tagUpdatesQueue_.push(tags);
    tag_queue_cv_.notify_one();
}

// =============== Socket Management ===============
void ZmqServer::initSockets() {
    adm_socket_ = std::make_unique<zmq::socket_t>(*context_, ZMQ_ROUTER);
    pub_socket_ = std::make_unique<zmq::socket_t>(*context_, ZMQ_PUB);

    // Socket options
    adm_socket_->set(zmq::sockopt::rcvhwm,      config_.maxQueueSize);
    adm_socket_->set(zmq::sockopt::sndhwm,      config_.maxQueueSize);
    adm_socket_->set(zmq::sockopt::rcvtimeo,    config_.operationTimeout);
    adm_socket_->set(zmq::sockopt::sndtimeo,    config_.operationTimeout);

    pub_socket_->set(zmq::sockopt::sndhwm,      config_.maxQueueSize);
    pub_socket_->set(zmq::sockopt::sndtimeo,    config_.operationTimeout);

    // Bind sockets
    adm_socket_->bind("tcp://*:" + std::to_string(config_.admPort));
    pub_socket_->bind("tcp://*:" + std::to_string(config_.pubPort));
}

void ZmqServer::cleanupSockets() {
    try {
        if (adm_socket_) adm_socket_->close();
        if (pub_socket_) pub_socket_->close();
        if (context_)    context_->close();
    } catch (...) {} // Игнорируем ошибки при закрытии
    adm_socket_.reset();
    pub_socket_.reset();
//    sub_socket_.reset();
    context_.reset();
}

// =============== Thread Workers ===============
void ZmqServer::startWorkerThreads() {
    adm_thread_ = std::thread(&ZmqServer::admWorker, this);
    pub_thread_ = std::thread(&ZmqServer::pubWorker, this);
    heartbeat_thread_ = std::thread(&ZmqServer::heartbeatWorker, this);
    tag_processing_thread_ = std::thread(&ZmqServer::tagProcessingWorker, this);
}

void ZmqServer::stopWorkerThreads() {
    if (context_) { context_->shutdown(); }
    if (adm_thread_.joinable()) adm_thread_.join();
    if (pub_thread_.joinable()) pub_thread_.join();
    if (heartbeat_thread_.joinable()) heartbeat_thread_.join();
    if (tag_processing_thread_.joinable()) tag_processing_thread_.join();
}

// ----------------------------------------------------------------------------
// Поток (1) - Приём и обработка административных сообщений
// ----------------------------------------------------------------------------
void ZmqServer::admWorker() {
    zmq::pollitem_t items[] = {{*adm_socket_, 0, ZMQ_POLLIN, 0}};

    while (state_ == ServerState::RUNNING) {
        try {
            // 1. Проверяем входящие сообщения с таймаутом 100ms
            zmq::poll(items, 1, 100ms);

            // 2. Если есть сообщение
            if (items[0].revents & ZMQ_POLLIN) {
                zmq::message_t msg;

                // 3. Получаем сообщение (блокирующий вызов с таймаутом)
                if (adm_socket_->recv(msg, zmq::recv_flags::none)) {
                    std::string message(static_cast<char*>(msg.data()), msg.size());

                    // Определяем формат JSON-сообщения
                    if (!message.empty() && (message[0] == '{' || message[0] == '[')) {
                        processAdminMessage(message);
                    }

                }
            }
        }
        catch (const zmq::error_t& e) {
            // 4. Игнорируем ошибки завершения (ETERM)
            if (e.num() != ETERM) {
                std::cerr << "Admin worker error: " << e.what() << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception in admin worker: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown error in admin worker" << std::endl;
        }
    }
}

// ----------------------------------------------------------------------------
// Поток (2) - Публикация сообщений клиентам
// ----------------------------------------------------------------------------
void ZmqServer::pubWorker() {
    while (state_ == ServerState::RUNNING) {
        std::vector<std::shared_ptr<IDto>> messagesToSend;

        // 1. Фаза сбора сообщений (минимальное время блокировки)
        {
            std::lock_guard<std::mutex> lock(clients_mutex_);
            for (auto& [_, client] : clients_) {
                while (auto dto = client->getNextMessage(0)) {
                    messagesToSend.emplace_back(std::move(dto));
                }
            }
        }

        // 2. Фаза отправки
        for (auto& dto : messagesToSend) {
            const std::string& client_id = dto->getKey();

            try {
                // Оптимизированная отправка (1 часть - JSON)
                zmq::message_t msg(dto->toJSON());
                if (!pub_socket_->send(msg, zmq::send_flags::dontwait)) {
                    throw zmq::error_t(EAGAIN);
                }

                if (config_.debugMode) {
                    std::cout << "Sent to " << client_id << " [" << msg.size() << " bytes]\n";
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Send failed to " << client_id << ": " << e.what() << "\n";

                std::lock_guard<std::mutex> lock(clients_mutex_);
                if (auto it = clients_.find(client_id); it != clients_.end()) {
                    it->second->enqueueMessage(dto);
                }
            }
        }

        // Оптимальная пауза
        if (messagesToSend.empty()) { std::this_thread::sleep_for(10ms); }
    }
}

// ----------------------------------------------------------------------------
// Поток (3) - Удаление "мёртвых" клиентов
// ----------------------------------------------------------------------------
void ZmqServer::heartbeatWorker() {
    while (state_ == ServerState::RUNNING) {
        try {
            auto now = steady_clock::now();

            // Проверка неактивных клиентов
            {
                auto timeout = milliseconds(config_.clientTimeout);

                std::lock_guard<std::mutex> clients_lock(clients_mutex_);
                std::lock_guard<std::mutex> subs_lock(subscriptions_mutex_);

                for (auto it = clients_.begin(); it != clients_.end();) {
                    if ((now - it->second->getLastActivity()) > timeout) {
                        const std::string &client_id = it->first;

                        // 1. Получаем все подписки клиента
                        auto client_subs = it->second->getSubscriptions();

                        // 2. Формируем полный список тегов для отписки
                        std::unordered_set<std::string> all_tags;
                        for (const auto &sub: client_subs) {
                            all_tags.insert(sub.keys.begin(), sub.keys.end());
                        }

                        // 3. Удаляем клиента из tagSubscriptions_
                        std::vector<Address> addrs_to_unsub;
                        for (const auto &tag: all_tags) {
                            auto entry_it = tagSubscriptions_.find(tag);
                            if (entry_it != tagSubscriptions_.end()) {
                                auto &clients = entry_it->second;
                                clients.erase(std::remove(clients.begin(), clients.end(), client_id),
                                              clients.end());

                                if (clients.empty()) {
                                    addrs_to_unsub.emplace_back(Address::of(tag));
                                    tagSubscriptions_.erase(entry_it);
                                }
                            }
                        }

                        // 4. Отписываемся от RegServer
                        if (!addrs_to_unsub.empty() && reg_client_) {
                            reg_client_->unsubscribe(addrs_to_unsub);
                        }

                        // 5. Удаляем клиента
                        it = clients_.erase(it);
                    } else {
                        ++it;
                    }
                }
            }

            // Точная пауза до следующего цикла
            auto elapsed = steady_clock::now() - now; //start_time;
            auto remaining = milliseconds(config_.heartbeatInterval) - elapsed;
            if (remaining.count() > 0) {
                std::this_thread::sleep_for(remaining);
            }

        } catch (...) {
            if (state_ == ServerState::RUNNING) {
                std::cerr << "Error in heartbeat worker" << std::endl;
            }
        }
    }
}

// ----------------------------------------------------------------------------
// Поток (5) - Обработка обновлений тегов
// ----------------------------------------------------------------------------
void ZmqServer::tagProcessingWorker() {
    while (!stop_tag_processing_) {
        try {
            // 1. выбираем теги из очереди
            std::vector<Tag> tags;
            {
                std::unique_lock<std::mutex> lock(tag_queue_mutex_);
                tag_queue_cv_.wait(lock, [this]() {
                    return !tagUpdatesQueue_.empty() || stop_tag_processing_;
                });

                if (stop_tag_processing_) break;

                if (!tagUpdatesQueue_.empty()) {
                    tags = std::move(tagUpdatesQueue_.front());
                    tagUpdatesQueue_.pop();
                }
            }

            // 2. обрабатываем теги из очереди
            if (!tags.empty()) {
                processTagUpdates(tags);
            }
        } catch (...) {
            if (!stop_tag_processing_) {
                std::cerr << "Error in tag processing worker" << std::endl;
            }
        }
    }
}

// ----------------------------------------------------------------------------
// Обработчик административных сообщений
// ----------------------------------------------------------------------------
void ZmqServer::processAdminMessage(const std::string& message) {
    json json_msg;

    try {
        json_msg = json::parse(message);
        std::string client_id = json_msg["key"].get<std::string>();

        if (json_msg.contains("request")) {
            std::string request_type = json_msg["request"].get<std::string>();

            if (request_type == "connect") {
                auto connect = Request::fromJSON(message);
                Response response = handleConnectRequest(connect);
                sendResponse(client_id, std::make_shared<Response>(response));

            }
            else if (request_type == "disconnect") {
                disconnectClient(client_id);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "disconnect", "Disconnected successfully")
                ));

            }
            else if (request_type == "subscribe_values") {
                auto subscribe = Subscribe::fromJSON(message);
                processSubscribe(subscribe);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "subscribe_values", "Subscription successful")
                ));

            }
            else if (request_type == "unsubscribe_values") {
                auto unsubscribe = Unsubscribe::fromJSON(message);
                processUnsubscribe(unsubscribe);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "unsubscribe_values", "Unsubscribed successfully")
                ));
            }
            else if (request_type == "prog_start") {
                auto prog_start = ProgStart::fromJSON(message);
                handleProgStart(prog_start);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "prog_start", "Program transfer started")
                ));
            }
            else if (request_type == "file_start") {
                auto file_start = FileStart::fromJSON(message);
                handleFileStart(file_start);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "file_start", "File transfer started")
                ));
            }
            else if (request_type == "file_chunk") {
                auto file_chunk = FileChunk::fromJSON(message);
                handleFileChunk(file_chunk);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "file_chunk", "Chunk received")
                ));
            }
            else if (request_type == "file_end") {
                auto file_end = FileEnd::fromJSON(message);
                handleFileEnd(file_end);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "file_end", "File transfer completed")
                ));
            }
            else if (request_type == "prog_end") {
                auto prog_end = ProgEnd::fromJSON(message);
                handleProgEnd(prog_end);
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "prog_end", "Program transfer completed")
                ));
            }

            else if (request_type == "heartbeat") {
                std::lock_guard<std::mutex> lock(clients_mutex_);
                if (clients_.count(client_id)) {
                    clients_[client_id]->updateLastActivity();
                }
                // Отправляем ответ через административный канал
                sendResponse(client_id, std::make_shared<Response>(
                        Response::success(client_id, "heartbeat", "alive")
                ));

            } else {
                sendResponse(client_id, std::make_shared<Response>(
                        Response::error(client_id, request_type, "Unknown request type")
                ));
            }
        } else {
            sendResponse(client_id, std::make_shared<Response>(
                    Response::error(client_id, "", "Missing 'request' field")
            ));
        }
    } catch (const json::exception& e) {
        try {
            std::string client_id = json_msg.empty() ? "" : json_msg.value("key", "");
            sendResponse(client_id, std::make_shared<Response>(
                    Response::error(client_id, "", "Invalid JSON: " + std::string(e.what()))
            ));
        } catch (...) {
            std::cerr << "Double error while handling JSON exception\n";
        }
    } catch (const std::exception& e) {
        try {
            std::string client_id = json_msg.empty() ? "" : json_msg.value("key", "");
            sendResponse(client_id, std::make_shared<Response>(
                    Response::error(client_id, "", "Processing error: " + std::string(e.what()))
            ));
        } catch (...) {
            std::cerr << "Double error while handling processing exception\n";
        }
    } catch (...) {
        try {
            std::string client_id = json_msg.empty() ? "" : json_msg.value("key", "");
            sendResponse(client_id, std::make_shared<Response>(
                    Response::error(client_id, "", "Unknown server error")
            ));
        } catch (...) {
            std::cerr << "Double error while handling unknown exception\n";
        }
    }
}

// ----------------------------------------------------------------------------
// --- Connection Management
// ----------------------------------------------------------------------------
Response ZmqServer::handleConnectRequest(const Request& request) {
    // 1. Проверка на пустой ключ клиента
    if (request.key.empty()) {
        if (config_.debugMode) {
            std::cerr << "Connect error: Empty client key" << std::endl;
        }
        return Response::error(request.key, request.request, "Empty client key");
    }

    std::unique_lock<std::mutex> clients_lock(clients_mutex_);

    // 2. Проверка максимального количества клиентов
    if (clients_.size() >= config_.maxClients) {
        if (config_.debugMode) {
            std::cerr << "Connect error: Max clients reached (" << config_.maxClients
                      << ") from client " << request.key << std::endl;
        }
        return Response::error(request.key, request.request, "Maximum clients reached");
    }

    // 3. Проверка существующего подключения
    auto it = clients_.find(request.key);
    if (it != clients_.end()) {
        // Клиент уже подключен - просто обновляем активность
        it->second->updateLastActivity();

        if (config_.debugMode) {
            std::cout << "Client reconnected: " << request.key << std::endl;
        }
        return Response::success(request.key, request.request, "Client already connected");
    }

    try {
        // 4. Создаем и регистрируем нового клиента
        auto new_client = std::make_shared<ZmqClient>(request.key);
        new_client->updateLastActivity();

        // 5. Добавляем клиента в коллекцию
        clients_[request.key] = new_client;
        clients_lock.unlock();

        if (config_.debugMode) {
            std::cout << "New client connected: " << request.key << std::endl;
        }

        // 6. Отправляем успешный ответ
        return Response::success(request.key, request.request, "Connected successfully");

    } catch (const std::exception& e) {
        if (clients_lock.owns_lock()) {
            clients_lock.unlock();
        }

        if (config_.debugMode) {
            std::cerr << "Connect error for client " << request.key
                      << ": " << e.what() << std::endl;
        }
        return Response::error(request.key, request.request,
                               "Connection error: " + std::string(e.what()));
    } catch (...) {
        if (clients_lock.owns_lock()) {
            clients_lock.unlock();
        }

        if (config_.debugMode) {
            std::cerr << "Unknown connect error for client " << request.key << std::endl;
        }
        return Response::error(request.key, request.request, "Unknown connection error");
    }
}

void ZmqServer::disconnectClient(const std::string& key) {
    std::unique_lock<std::mutex> clients_lock(clients_mutex_);
    auto client_it = clients_.find(key);
    if (client_it == clients_.end()) {
        return;
    }

    try {
        // Сохраняем хост перед удалением клиента
        std::string host = client_it->second->getHost();

        if (config_.debugMode) {
            std::cout << "Disconnecting client " << key << std::endl;
        }

        // Удаляем клиента (разблокируем мьютекс сразу после этого)
        clients_.erase(client_it);
        clients_lock.unlock();

        // Очищаем подписки клиента
        std::lock_guard<std::mutex> sub_lock(subscriptions_mutex_);
        for (auto& [tag, client_ids] : tagSubscriptions_) {
            client_ids.erase(
                    std::remove(client_ids.begin(), client_ids.end(), key),
                    client_ids.end()
            );
        }

        // Удаляем пустые записи подписок
        auto sub_it = tagSubscriptions_.begin();
        while (sub_it != tagSubscriptions_.end()) {
            if (sub_it->second.empty()) {
                sub_it = tagSubscriptions_.erase(sub_it);
            } else {
                ++sub_it;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error disconnecting client " << key << ": " << e.what() << std::endl;
        if (clients_lock.owns_lock()) {
            clients_lock.unlock();
        }
    }
}

// ----------------------------------------------------------------------------
// --- Updates
// ----------------------------------------------------------------------------
void ZmqServer::processTagUpdates(const std::vector<Tag>& tags) {
    std::unordered_map<
            std::string,
            std::unordered_map<std::string, std::vector<Tag>>
    > clientUpdates;

    // 1. Собираем обновления для каждого клиента
    {
        std::lock_guard<std::mutex> clients_lock(clients_mutex_);
        std::lock_guard<std::mutex> sub_lock(subscriptions_mutex_);

        for (const auto& tag : tags) {
            auto it = tagSubscriptions_.find(tag.key);
            if (it != tagSubscriptions_.end())
            {
                for (const auto& clientId : it->second) {
                    auto clientIt = clients_.find(clientId);
                    if (clientIt != clients_.end()) {
                        // Находим topic для этого тега у клиента
                        for (const auto& sub : clientIt->second->getSubscriptions())
                        {
                            // поиск в векторе подписки
                            if (std::find(sub.keys.begin(), sub.keys.end(), tag.key) != sub.keys.end()) {
                                clientUpdates[clientId][sub.topic].push_back(tag);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // 2. Создаем DTO и отправляем клиентам
    for (const auto& [clientId, topics] : clientUpdates) {
        for (const auto& [topic, tagList] : topics)
        {
            auto dto = std::make_shared<SendValues>(clientId, topic, tagList);
            sendDtoToClient(clientId, dto);

            // Логирование в debug режиме
            if (config_.debugMode) {
                std::cout << "Sent " << tagList.size() << " tag updates to client: "
                    << clientId << " for topic: " << topic << std::endl;
            }
        }
    }
}

// ----------------------------------------------------------------------------
// --- Subscribtions
// ----------------------------------------------------------------------------
void ZmqServer::updateOutputs(const std::vector<OnDataChange>& changes) {
    std::vector<Tag> tags;
    tags.reserve(changes.size());

    std::lock_guard<std::mutex> lock(subscriptions_mutex_);

    for (const auto& change : changes) {
        try {
            // Преобразуем ключ обратно в итератор
            auto entry_pair = reinterpret_cast< const std::pair<const std::string, std::vector<std::string>>* >(change.key);

            // Проверка того, что итератор валиден
            if (entry_pair) {
                const auto& tag_key = entry_pair->first;

                Tag tag;
                tag.key = tag_key;

                //tag.value = VARIANT(change.data);
                tag.value = change.data; //*** uint64_t напрямую

                tag.quality = Quality::GOOD;
                tag.timestamp = std::chrono::system_clock::now();

                tags.push_back(std::move(tag));
            }
        } catch (...) {
            // Логирование ошибки
        }
    }

    if (!tags.empty()) {
        pushTagUpdates(tags);
    }
}

////*** Новая функция конвертации
//double convertRegisterValueToDouble(uint64_t raw, Address::Type type) {
//    switch(type) {
//        case Address::TYPE_REAL: {
//            float f;
//            memcpy(&f, &raw, sizeof(float));
//            return static_cast<double>(f);
//        }
//        case Address::TYPE_LREAL: {
//            double d;
//            memcpy(&d, &raw, sizeof(double));
//            return d;
//        }
//        default:
//            return static_cast<double>(raw); // Для целочисленных типов
//    }
//}

// ----------------------------------------------------------------------------
void ZmqServer::processSubscribe(const Subscribe& sub) {
    // 1. Блокировки и базовая проверка
    std::unique_lock<std::mutex> clients_lock(clients_mutex_);
    std::unique_lock<std::mutex> subs_lock(subscriptions_mutex_);

    auto clientIt = clients_.find(sub.key);
    if (clientIt == clients_.end()) {
        throw ZmqServerException("Client not found");
    }

    // 2. Добавляем подписку клиента
    clientIt->second->addSubscription(sub);

    // 3. Подготовка данных
    std::vector<RegItem> reg_items;
    std::vector<Tag> initial_tags;
    reg_items.reserve(sub.keys.size());
    initial_tags.reserve(sub.keys.size());

    // 4. Сбор данных и подписок
    for (const auto& key : sub.keys) {
        Address addr = Address::of(key);

        // 4.1 Получаем текущее значение
        uint64_t raw_value = RegServer::instance().getProxyValue(addr);

        initial_tags.push_back({
               key,

               //VARIANT(raw_value),
               raw_value, //*** Сохраняем сырое значение

               Quality::GOOD,
               std::chrono::system_clock::now()
        });

        // 4.2 Обновляем локальные подписки
        auto& clients = tagSubscriptions_[key];
        if (std::find(clients.begin(), clients.end(), sub.key) == clients.end()) {
            clients.push_back(sub.key);
        }

        // 4.3 Формируем подписку для RegServer
        uint64_t subscription_key = reinterpret_cast<uint64_t>(&(*tagSubscriptions_.find(key)));
        reg_items.emplace_back(RegItem{addr, subscription_key});
    }

    // 5. Создаем DTO для начальных значений
    auto initial_dto = std::make_shared<SendValues>(sub.key, sub.topic, initial_tags);

    // 6. Инициализация reg_client_ (если нужно)
    if (!reg_client_ && !reg_items.empty()) {
        reg_client_ = RegServer::instance().createClient(
                "zmq_server",
                static_cast<IClientCallback*>(this)
        );
    }

    // 7. Разблокируем мьютексы перед внешними вызовами
    clients_lock.unlock();
    subs_lock.unlock();

    // 8. Подписка в RegServer
    if (!reg_items.empty()) {
        reg_client_->subscribe(reg_items);
    }

    // 9. Прямая отправка начальных значений
    if (!initial_tags.empty()) {
        sendDtoToClient(sub.key, initial_dto);

        if (config_.debugMode) {
            std::cout << "Sent initial " << initial_tags.size()
                      << " values to client: " << sub.key
                      << " (topic: " << sub.topic << ")\n";
        }
    }
}

// ----------------------------------------------------------------------------
void ZmqServer::processUnsubscribe(const Unsubscribe& unsub) {
    std::lock_guard<std::mutex> clients_lock(clients_mutex_);
    std::lock_guard<std::mutex> sub_lock(subscriptions_mutex_);

    // 1. Поиск класса клиента
    auto clientIt = clients_.find(unsub.key);
    if (clientIt == clients_.end()) { throw ZmqServerException("Client not found"); }

    // 2. Получаем подписки клиента для этого топика
    auto subscriptions = clientIt->second->getSubscriptions();
    auto sub_it = std::find_if(subscriptions.begin(), subscriptions.end(),
                               [&](const auto& s) { return s.topic == unsub.topic; });
    if (sub_it == subscriptions.end()) return;

    // 3. Формируем список адресов для отписки
    std::vector<Address> addrs_to_unsub;
    for (const auto& key : sub_it->keys)
    {
        auto entry_it = tagSubscriptions_.find(key);
        if (entry_it != tagSubscriptions_.end()) {

            // Удаляем клиента из entry
            auto& clients = entry_it->second;
            clients.erase(std::remove(clients.begin(), clients.end(), unsub.key), clients.end());

            // Если больше нет подписчиков - добавляем в отписку
            if (clients.empty()) {
                addrs_to_unsub.emplace_back(Address::of(key));
                tagSubscriptions_.erase(entry_it);
            }
        }
    }

    // 4. Выполняем отписку в RegServer
    if (!addrs_to_unsub.empty() && reg_client_) {
        reg_client_->unsubscribe(addrs_to_unsub);
    }

    // 5. Удаляем топик в ZmqClient
    clientIt->second->removeSubscription(unsub.topic);
}

// ----------------------------------------------------------------------------
// --- File transfer management
// ----------------------------------------------------------------------------
void ZmqServer::handleProgStart(const ProgStart &prog_start) {
    std::lock_guard<std::mutex> lock(transfer_mutex_);

    // Создаем каталог для программы
    auto save_path = programs_dir_ / prog_start.prog_name;
    std::filesystem::create_directories(save_path);

    // Инициализируем передачу
    active_transfers_[prog_start.key] = {
            prog_start.key,
            prog_start.prog_name,
            prog_start.prog_hash,
            "", 0, // file_name и file_size будет установлен в file_start
            0,          // bytes_received
            0xFFFFFFFF, // Инициализация CRC
            save_path
            //, std::chrono::steady_clock::now()
    };

    auto it = active_transfers_.find(prog_start.key);
    auto& transfer = it->second;

    if (config_.debugMode) {
        std::cout << "Starting program transfer: " << prog_start.prog_name
                  << " from client " << prog_start.key << std::endl;
    }
}

// ----------------------------------------------------------------------------
void ZmqServer::handleFileStart(const FileStart& file_start) {
    std::lock_guard<std::mutex> lock(transfer_mutex_);
    auto it = active_transfers_.find(file_start.key);
    if (it == active_transfers_.end()) {
        throw ZmqServerException("No active program transfer for client");
    }

    auto& transfer = it->second;
    transfer.file_name = file_start.file_name;
    transfer.file_size = file_start.file_size;
    transfer.bytes_received = 0;
    transfer.file_crc = 0xFFFFFFFF; // Инициализация CRC32

    auto file_path = transfer.save_path / file_start.file_name;
    transfer.file_stream.open(file_path, std::ios::binary);
    if (!transfer.file_stream) {
        throw ZmqServerException("Failed to open file for writing: " + file_path.string());
    }

    if (config_.debugMode) {
        std::cout << "Starting file transfer: " << file_start.file_name
                  << " (" << file_start.file_size << " bytes)\n";
    }
}

//void ZmqServer::handleFileStart(const FileStart& file_start) {
//    std::lock_guard<std::mutex> lock(transfer_mutex_);
//    auto it = active_transfers_.find(file_start.key);
//    if (it == active_transfers_.end()) {
//        throw ZmqServerException("No active program transfer for client");
//    }
//
//    auto& transfer = it->second;
//    transfer.file_name = file_start.file_name;
//    transfer.file_size = file_start.file_size;
//    transfer.bytes_received = 0;
//    transfer.file_crc = 0xFFFFFFFF; // Инициализируем CRC32
//
//    auto file_path = transfer.save_path / file_start.file_name;
//    transfer.file_stream.open(file_path, std::ios::binary);
//    if (!transfer.file_stream) {
//        throw ZmqServerException("Failed to open file for writing: " + file_path.string());
//    }
//
//    if (config_.debugMode) {
//        std::cout << "Starting file transfer: " << file_start.file_name
//                  << " (" << file_start.file_size << " bytes)" << std::endl;
//    }
//}
//
// ----------------------------------------------------------------------------
void ZmqServer::handleFileChunk(const FileChunk& file_chunk) {
    std::lock_guard<std::mutex> lock(transfer_mutex_);
    auto it = active_transfers_.find(file_chunk.key);
    if (it == active_transfers_.end()) {
        throw ZmqServerException("No active file transfer for client");
    }

    auto& transfer = it->second;
    if (!transfer.file_stream.is_open()) {
        throw ZmqServerException("File not open for writing");
    }

    // Декодируем Base64
    std::string decoded_data = base64_decode(file_chunk.chunk_data);

    // Проверяем размер после декодирования
    if (decoded_data.size() != file_chunk.chunk_size) {
        throw ZmqServerException("Chunk size mismatch after decoding");
    }

    // Записываем декодированные данные
    transfer.file_stream.write(decoded_data.data(), decoded_data.size());
    transfer.bytes_received += decoded_data.size();

    // Обновляем CRC
    transfer.file_crc = calculate_crc32(
            decoded_data.data(),
            decoded_data.size(),
            transfer.file_crc
    );

    if (config_.debugMode) {
        float progress = (transfer.bytes_received * 100.0f) / transfer.file_size;
        std::cout << "Received chunk: " << file_chunk.chunk_size << " bytes (decoded: "
                  << decoded_data.size() << " bytes) for " << transfer.file_name
                  << " (" << std::fixed << std::setprecision(1) << progress << "%)\n";
    }
}

//void ZmqServer::handleFileChunk(const FileChunk& file_chunk) {
//    std::lock_guard<std::mutex> lock(transfer_mutex_);
//    auto it = active_transfers_.find(file_chunk.key);
//    if (it == active_transfers_.end()) {
//        throw ZmqServerException("No active file transfer for client");
//    }
//
//    auto& transfer = it->second;
//    if (!transfer.file_stream.is_open()) {
//        throw ZmqServerException("File not open for writing");
//    }
//
//    // Обновляем контрольную сумму
//    transfer.file_crc = utils::calculate_crc32(
//            file_chunk.chunk_data.data(),
//            file_chunk.chunk_size,
//            transfer.file_crc
//    );
//
//    // Записываем данные в файл
//    transfer.file_stream.write(file_chunk.chunk_data.data(), file_chunk.chunk_size);
//    transfer.bytes_received += file_chunk.chunk_size;
//
//    if (config_.debugMode) {
//        std::cout << "Received chunk: " << file_chunk.chunk_size << " bytes for "
//                  << transfer.file_name << " (" << transfer.bytes_received
//                  << "/" << transfer.file_size << ")" << std::endl;
//    }
//}

// ----------------------------------------------------------------------------
void ZmqServer::handleFileEnd(const FileEnd& file_end) {
    std::lock_guard<std::mutex> lock(transfer_mutex_);
    auto it = active_transfers_.find(file_end.key);
    if (it == active_transfers_.end()) {
        throw ZmqServerException("No active file transfer for client");
    }

    auto& transfer = it->second;
    if (transfer.file_stream.is_open()) {
        transfer.file_stream.close();
    }

    // Финализируем контрольную сумму
    transfer.file_crc ^= 0xFFFFFFFF;

    // Проверяем размер полученного файла
    auto file_path = transfer.save_path / transfer.file_name;
    uint64_t actual_size = std::filesystem::file_size(file_path);

    if (actual_size != transfer.file_size) {
        std::filesystem::remove(file_path);
        throw ZmqServerException("File size mismatch: expected " +
            std::to_string(transfer.file_size) + ", got " + std::to_string(actual_size));
    }

    if (config_.debugMode) {
        std::cout << "File transfer completed: " << transfer.file_name
                  << ", CRC32: 0x" << std::hex << transfer.file_crc << std::dec << std::endl;
    }
}

// ----------------------------------------------------------------------------
void ZmqServer::handleProgEnd(const ProgEnd& prog_end) {
    std::lock_guard<std::mutex> lock(transfer_mutex_);
    auto it = active_transfers_.find(prog_end.key);
    if (it == active_transfers_.end()) {
        throw ZmqServerException("No active program transfer for client");
    }

    // Проверяем контрольную сумму программы
    uint64_t actual_hash = utils::calculate_program_hash(it->second.save_path.string());
    if (actual_hash != it->second.prog_hash) {
        throw ZmqServerException("Program hash mismatch: expected " +
                                 std::to_string(it->second.prog_hash) + ", got " + std::to_string(actual_hash));
    }

    if (config_.debugMode) {
        std::cout << "Program transfer completed: " << it->second.prog_name
                  << ", hash: " << std::hex << actual_hash << std::dec << std::endl;
    }

    active_transfers_.erase(it);
}

// ============================================================================
// --- Helper Methods
// ============================================================================
void ZmqServer::changeState(ServerState new_state) {
    ServerState old_state = state_.exchange(new_state);
    if (old_state != new_state) {
        //// Можно добавить логирование изменения состояния
    }
}

// Отправляет DTO клиенту через очередь (для подписок на теги).
// Используется ТОЛЬКО в processSubscribe и processTagUpdates.
// ----------------------------------------------------------------------------
void ZmqServer::sendDtoToClient(const std::string& client_id, const std::shared_ptr<IDto>& dto) {
    if (state_ != ServerState::RUNNING) {
        return; // Не бросаем исключение, т.к это не критично для подписок
    }
    std::lock_guard<std::mutex> lock(clients_mutex_);
    if (auto it = clients_.find(client_id); it != clients_.end()) {
        it->second->enqueueMessage(dto); // Кладём в очередь, отправит pub_thread_
    }
}

// Отправляет ответ клиенту напрямую через adm_socket_ (без очереди).
// Используется ТОЛЬКО для ответов на запросы (connect, subscribe и т. д.).
// ----------------------------------------------------------------------------
void ZmqServer::sendResponse(const std::string& client_id, const std::shared_ptr<IDto>& dto) {
    if (state_ != ServerState::RUNNING || !adm_socket_) {
        throw ZmqServerException("Server is not running or socket not initialized");
    }

    try {
        // 1. Формируем сообщение (ID клиента + JSON)
        zmq::multipart_t msg;
        msg.addstr(client_id);          // Идентификатор клиента (ROUTER требует этого)
        msg.addstr(dto->toJSON());      // Сериализованный JSON

        // 2. Отправляем (блокирующий вызов с таймаутом)
        if (!msg.send(*adm_socket_, 0/* zmq::send_flags::dontwait) */)) {  // или zmq::send_flags::none
            throw zmq::error_t(EAGAIN);
        }

        if (config_.debugMode) {
            std::cout << "Sent response to " << client_id << " [" << msg.size() << " bytes]\n";
        }

    } catch (const zmq::error_t& e) {
        if (e.num() != ETERM) { // Игнорируем ошибки завершения
            std::cerr << "Failed to send response to " << client_id << ": " << e.what() << "\n";
            throw ZmqServerException("ZMQ send error: " + std::string(e.what()));
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to send response to " << client_id << ": " << e.what() << "\n";
        throw ZmqServerException("Response send error: " + std::string(e.what()));
    }
}

// ============================================================================
template<typename T>
void ZmqServer::broadcast(const T &dto) {
    static_assert(std::is_base_of_v<IDto, T>, "T must inherit from IDto");

    if (state_ != ServerState::RUNNING) {
        throw ZmqServerException("Server is not running");
    }

    std::lock_guard<std::mutex> lock(clients_mutex_);
    for (const auto& [client_id, client] : clients_) {
        try {
            // Создаем копию DTO с новым ключом
            auto clientDto = std::make_shared<T>(dto);
            clientDto->setKey(client_id);
            client->enqueueMessage(clientDto);
        } catch (const std::exception& e) {
            std::cerr << "Failed to create DTO for client " << client_id
                      << ": " << e.what() << std::endl;
        }
    }
}

// ============================================================================
