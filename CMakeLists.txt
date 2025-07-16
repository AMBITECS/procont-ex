cmake_minimum_required(VERSION 3.25)
project(PROCONT-EX VERSION 1.0.1 DESCRIPTION "Procont execution environment" LANGUAGES CXX)

string( TOLOWER ${PROJECT_NAME}  proj )      # proj = project name in lowercase
set( PROJECT_SO_VERSION          "1"  )
set( CMAKE_CXX_STANDARD          17   )
set( CMAKE_CXX_STANDARD_REQUIRED True )

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} BEGIN")

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

#--------------------------------------------------------------
# Настройка путей проекта
#--------------------------------------------------------------
set( PROJ_DIR     ${CMAKE_CURRENT_SOURCE_DIR} ) # PROJ project
set( CMAKE_DIR    ${PROJ_DIR}/.cmake          ) # PROJ cmake
set( PROJ_INS_DIR ${PROJ_DIR}/.deploy         ) # PROJ install (local)
set( PROJ_ETC_DIR ${PROJ_DIR}/etc             ) # PROJ configs
set( PROJ_SRC_DIR ${PROJ_DIR}/src             ) # PROJ sources
set( PROJ_INC_DIR ${PROJ_DIR}/include         ) # PROJ includes
set( PROJ_SUB_DIR ${PROJ_DIR}/utils           ) # PROJ submodule

#--------------------------------------------------------------
# Настройка путей к библиотекам и модулям
#--------------------------------------------------------------
set( CMAKE_MODULE_PATH ${CMAKE_DIR} ${CMAKE_DIR}/find)

# Унификация единых каталогов для инсталляции (вместо lib|lib64 -> lib)
set( CMAKE_INSTALL_LIBDIR "lib" CACHE STRING "Library installation directory" FORCE )
set( CMAKE_INSTALL_PREFIX ${PROJ_INS_DIR} CACHE PATH "Installation directory" FORCE )

# Устанавливаем единый каталог для инсталляции
set( PROJ_LIB_DIR ${PROJ_INS_DIR}/${CMAKE_INSTALL_LIBDIR} ) # PROJ libraries
if(NOT EXISTS "${PROJ_LIB_DIR}")
    file(MAKE_DIRECTORY "${PROJ_LIB_DIR}")
endif()

# Устанавливаем единые каталоги для сборки модулей
set(LIBRARY_OUTPUT_PATH     ${PROJ_INS_DIR}/${CMAKE_INSTALL_LIBDIR})
set(EXECUTABLE_OUTPUT_PATH  ${PROJ_INS_DIR}/bin)

include_directories ( ${PROJ_INS_DIR}/include )
link_directories    ( ${PROJ_LIB_DIR} )

#--------------------------------------------------------------
# Пути к основным библиотекам (синонимы) - CANopen, modbus и т.п.
#--------------------------------------------------------------
set(PLC_MAIN_LIB_DIR    ${PROJ_INS_DIR}/${CMAKE_INSTALL_LIBDIR})
set(DRIVER_FACTORY_DIR  ${PROJ_INS_DIR}/${CMAKE_INSTALL_LIBDIR})

#--------------------------------------------------------------
# Определение платформы и архитектуры
#--------------------------------------------------------------
if(CMAKE_SYSTEM_PROCESSOR MATCHES "armv7")
    set(LIB_ARCH "linux-armhf")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64") # "aarch64|arm64"
    set(LIB_ARCH "linux-arm64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(LIB_ARCH "linux-aarch64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(LIB_ARCH "linux-x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i[3-6]86")
    set(LIB_ARCH "linux-x86")
elseif(WIN32)
    set(LIB_ARCH "win64")
else()
    set(LIB_ARCH "unknown-linux")
endif()

message(STATUS "Target platform: ${LIB_ARCH}")

##--------------------------------------------------------------
## Настройка RPATH (только для Linux)
##--------------------------------------------------------------
if(LINUX)
    # 1. Базовый относительный RPATH (через $ORIGIN)
    set(CMAKE_INSTALL_RPATH "\$ORIGIN:\$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

    # 2. Включаем использование RPATH при сборке
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    #set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

    # 3. Отключаем новые dtags (для совместимости)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--disable-new-dtags")
    #set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--disable-new-dtags")

    message(STATUS "RPATH настроен на: ${CMAKE_INSTALL_RPATH}")
endif()

##--------------------------------------------------------------
## === НОВОЕ: Опция для сборки в Docker ===
##--------------------------------------------------------------
#option(BUILD_IN_DOCKER "Building inside Docker container" OFF)
#
##--------------------------------------------------------------
## === НОВОЕ: Явное определение инструментов кросс-компиляции
##--------------------------------------------------------------
#if(DEFINED ENV{CROSS_TRIPLE})
#    set(CMAKE_C_COMPILER $ENV{CC})
#    set(CMAKE_CXX_COMPILER $ENV{CXX})
#    set(CMAKE_AR $ENV{AR})
#    set(CMAKE_RANLIB $ENV{RANLIB})
#    set(CMAKE_STRIP $ENV{STRIP})
#endif()

##--------------------------------------------------------------
## === НОВОЕ: Оптимизация для Docker-сборки
##--------------------------------------------------------------
#if(BUILD_IN_DOCKER)
#    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
#    set(CMAKE_BUILD_PARALLEL_LEVEL "$ENV{NPROC}")
#endif()

#--------------------------------------------------------------
# ==== CMake symbols ===
#--------------------------------------------------------------
message(STATUS "C++   COMPILER  : ${CMAKE_CXX_COMPILER}!")
message(STATUS "CMake GENERATOR : ${CMAKE_GENERATOR}")
message(STATUS "CMake BUILD_TYPE: ${CMAKE_BUILD_TYPE}\n")

message(STATUS "CMake prefix  path: \"${CMAKE_PREFIX_PATH}\"")
message(STATUS "CMake project path: \"${CMAKE_SOURCE_DIR}\"")
message(STATUS "CMake install path: \"${CMAKE_INSTALL_PREFIX}\"\n")

message("== PROJ_DIR:         ${PROJ_DIR}")
message("== CMAKE_DIR:        ${CMAKE_DIR}")
message("== PROJ_INS_DIR:     ${PROJ_INS_DIR}")
message("== PROJ_SUB_DIR:     ${PROJ_SUB_DIR}")
message("== CMAKE_BINARY_DIR: ${PROJ_SUB_DIR}")

#--------------------------------------------------------------
# Используемые стандартные библиотеки
#--------------------------------------------------------------
include(${CMAKE_DIR}/find_tools.cmake)
include(${CMAKE_DIR}/build_tools.cmake)

#--------------------------------------------------------------
# Подключаемые модули
#--------------------------------------------------------------
include(FetchContent)
include(ExternalProject)

#--------------------------------------------------------------
# (-1-) Сборка OpenSSL
#--------------------------------------------------------------
# Опция для выбора способа получения OpenSSL
option(BUILD_OPENSSL_FROM_SOURCE "Build OpenSSL from source instead of using system package" OFF)

# 1. Настройка путей установки
set(OPENSSL_ROOT_DIR    ${PROJ_SUB_DIR}/openssl)
set(OPENSSL_INSTALL_DIR ${PROJ_INS_DIR})
set(OPENSSL_LIB_DIR     ${CMAKE_INSTALL_LIBDIR})  # Используем единый каталог lib
set(MAKE_DIRECTORY      ${OPENSSL_INSTALL_DIR})

#--------------------------------------------------------------
# === НОВОЕ: Улучшенные опции сборки OpenSSL ===
#--------------------------------------------------------------
# 2. Опции сборки OpenSSL
set(OPENSSL_OPTIONS
        no-shared           # Статическая сборка (.a)
        no-module           # Отключение динамических модулей
        no-legacy           # Отключение устаревших алгоритмов
        no-autoload-config  # Отключение авто-подгрузки конфигурации
        -fPIC               # Позиционно-независимый код
        #-static             # ← Полностью статическая сборка
        #enable-fips         # ← Если нужен FIPS
        #enable-legacy       # ← Включаем legacy-провайдер
)
message(STATUS "OpenSSL options: ${OPENSSL_OPTIONS}")

# 3. Определение целевой платформы
set(OPENSSL_TARGET ${LIB_ARCH})

if(BUILD_OPENSSL_FROM_SOURCE)
    # 4. Проверка исходного кода
    if(NOT EXISTS "${OPENSSL_ROOT_DIR}/Configure")
        message(FATAL_ERROR "OpenSSL sources missing in ${OPENSSL_ROOT_DIR}")
    endif()

    # 5. Настройка ExternalProject
    ExternalProject_Add(
            openssl_external
            SOURCE_DIR    ${OPENSSL_ROOT_DIR}
            PREFIX        "${CMAKE_BINARY_DIR}/openssl_build"
            CONFIGURE_COMMAND
                ${OPENSSL_ROOT_DIR}/Configure
                ${OPENSSL_TARGET}
                --prefix=${OPENSSL_INSTALL_DIR}
                --libdir=${OPENSSL_LIB_DIR}       # Явное указание каталога (lib)
                --openssldir=${OPENSSL_INSTALL_DIR}/ssl
                ${OPENSSL_OPTIONS}
            BUILD_COMMAND     $(MAKE) -j${CMAKE_BUILD_PARALLEL_LEVEL}
            INSTALL_COMMAND   $(MAKE) install_sw
            BUILD_IN_SOURCE   TRUE  # Сборка в исходниках
            BUILD_BYPRODUCTS
                "${OPENSSL_INSTALL_DIR}/${OPENSSL_LIB_DIR}/libssl.so"
                "${OPENSSL_INSTALL_DIR}/${OPENSSL_LIB_DIR}/libcrypto.so"
    )

    # 6. Импортированные цели
    add_library(OpenSSL::Crypto SHARED IMPORTED)
    add_library(OpenSSL::SSL SHARED IMPORTED)

    # 7. Настройка свойств библиотек
    # Для Crypto
    set_target_properties(OpenSSL::Crypto PROPERTIES
            IMPORTED_LOCATION "${OPENSSL_INSTALL_DIR}/${OPENSSL_LIB_DIR}/libcrypto.so"
            INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INSTALL_DIR}/include"
    )
    # Для SSL
    set_target_properties(OpenSSL::SSL PROPERTIES
            IMPORTED_LOCATION "${OPENSSL_INSTALL_DIR}/${OPENSSL_LIB_DIR}/libssl.so"
            INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INSTALL_DIR}/include"
            INTERFACE_LINK_LIBRARIES OpenSSL::Crypto
    )

    # 8. Управление зависимостями
    add_dependencies(OpenSSL::Crypto openssl_external)
    add_dependencies(OpenSSL::SSL openssl_external)

    # 9. Создаем псевдо-цель для удобства
    add_custom_target(openssl_all DEPENDS OpenSSL::SSL OpenSSL::Crypto)
else()
    # Вариант с системным OpenSSL (если он нужен)
    #    find_package(OpenSSL REQUIRED)
    #    if(NOT OpenSSL_FOUND)
    #        message(FATAL_ERROR "System OpenSSL not found, consider enabling BUILD_OPENSSL_FROM_SOURCE")
    #    endif()
    #    message(STATUS "Using system OpenSSL: ${OPENSSL_VERSION}")

    # Фиктивная цель
    add_custom_target(openssl_all)
    message(STATUS "Using system OpenSSL (ensure it's installed)")
endif()

# Создаем интерфейсную библиотеку для OpenSSL (если нужно)
#add_library(openssl_interface INTERFACE)
#target_link_libraries(openssl_interface INTERFACE OpenSSL::SSL OpenSSL::Crypto)

# 10. Включение заголовочных файлов
include_directories(${OPENSSL_INCLUDE_DIR})

# 11. Дополнительные проверки (опционально)
if(BUILD_OPENSSL_FROM_SOURCE AND TARGET openssl_external)
    add_custom_command(TARGET openssl_external POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "OpenSSL built to: ${OPENSSL_INSTALL_DIR}"
    )
endif()

#--------------------------------------------------------------
# (-2-) Сборка ZeroMQ (с унификацией путей библиотек)
#--------------------------------------------------------------
set(ZMQ_ROOT_DIR    ${PROJ_SUB_DIR}/libzmq)
set(ZMQ_INSTALL_DIR ${PROJ_INS_DIR})

# Проверка наличия исходников
if(NOT EXISTS "${ZMQ_ROOT_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "libzmq sources not found in ${ZMQ_ROOT_DIR}")
endif()

# Настройки сборки с явным указанием каталога библиотек
set(ZMQ_BUILD_OPTIONS
        -DZMQ_BUILD_TESTS=OFF                           # Отключение тестов
        -DWITH_TLS=${BUILD_OPENSSL_FROM_SOURCE}         # TLS только с OpenSSL
        -DZMQ_TLS_ENGINE=openssl                        # Использовать OpenSSL для TLS
        -DBUILD_SHARED=ON                               # Сборка shared-библиотеки
        -DBUILD_STATIC=OFF                              # Отключение статической сборки
        -DENABLE_DRAFTS=OFF                             # Отключение draft API
        -DWITH_PERF_TOOL=OFF                            # Отключение perf-инструментов
        -DWITH_LIBSODIUM=OFF                            # Отключение libsodium
        -DCMAKE_INSTALL_PREFIX=${ZMQ_INSTALL_DIR}       # Каталог установки
        -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}  # Единый каталог для библиотек
        -DWITH_LIBDIR_SUFFIX=OFF                        # Запрет автоматических суффиксов
)
message(STATUS "ZeroMQ build options: ${ZMQ_BUILD_OPTIONS}")

# Дополнительные опции при сборке OpenSSL из исходников
if(BUILD_OPENSSL_FROM_SOURCE)
    list(APPEND ZMQ_BUILD_OPTIONS
            -DOPENSSL_ROOT_DIR=${OPENSSL_INSTALL_DIR}
            -DOPENSSL_USE_STATIC_LIBS=ON
    )
endif()

# Добавление подпроекта с кастомными настройками
set(ZMQ_BUILD_TESTS OFF CACHE BOOL "Disable ZMQ tests" FORCE)
add_subdirectory(${ZMQ_ROOT_DIR})

# Проверка создания target
if(NOT TARGET libzmq)
    message(FATAL_ERROR "libzmq target not created!")
endif()

# Настройка выходного каталога для библиотек
set_target_properties(libzmq PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)

# Зависимости от openssl (если нужно)
if(TARGET openssl_all)
    add_dependencies(libzmq openssl_all)
endif()

# Кастомная команда установки
add_custom_target(install_libzmq
        COMMAND ${CMAKE_COMMAND}
        --install ${CMAKE_BINARY_DIR}/utils/libzmq
        --prefix ${ZMQ_INSTALL_DIR}
        --libdir ${CMAKE_INSTALL_LIBDIR}  # Явное указание каталога
        --config $<CONFIG>
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS libzmq
        COMMENT "Installing libzmq to ${ZMQ_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}"
        VERBATIM
)

# Добавление путей для заголовочных файлов
include_directories(${ZMQ_ROOT_DIR}/include)

#--------------------------------------------------------------
# (3) Настройка и установка cppzmq (с унификацией путей библиотек)
#--------------------------------------------------------------
set(CPPZMQ_ROOT_DIR    ${PROJ_SUB_DIR}/cppzmq)
set(CPPZMQ_INSTALL_DIR ${PROJ_INS_DIR})

# Проверка наличия исходников
if(NOT EXISTS "${CPPZMQ_ROOT_DIR}/CMakeLists.txt")
    message(FATAL_ERROR "cppzmq sources not found in ${CPPZMQ_ROOT_DIR}")
endif()

# Настройки сборки
#set(CPPZMQ_BUILD_TESTS OFF)     # Отключение тестов
#set(CPPZMQ_BUILD_EXAMPLES OFF)  # Отключение примеров
set(CPPZMQ_BUILD_OPTIONS
        -DCPPZMQ_BUILD_TESTS=OFF    # Отключение тестов
        -DCPPZMQ_BUILD_EXAMPLES=OFF # Отключение примеров
        -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}  # Единый каталог библиотек
)

# Добавление подпроекта с кастомными настройками
set(CPPZMQ_BUILD_TESTS    OFF CACHE BOOL "Disable CppZMQ tests"    FORCE)
set(CPPZMQ_BUILD_EXAMPLES OFF CACHE BOOL "Disable CppZMQ examples" FORCE)

add_subdirectory(${CPPZMQ_ROOT_DIR})

# Проверка создания target
if(NOT TARGET cppzmq)
    message(FATAL_ERROR "cppzmq target not created!")
endif()

# Установка зависимостей
if(TARGET cppzmq AND TARGET libzmq)
    add_dependencies(cppzmq libzmq)
    # Для header-only может не требоваться, но оставляем для совместимости
endif()

# Кастомная команда установки
add_custom_target(install_cppzmq
        COMMAND ${CMAKE_COMMAND}
        --install ${CMAKE_BINARY_DIR}/utils/cppzmq
        --prefix ${CPPZMQ_INSTALL_DIR}
        --libdir ${CMAKE_INSTALL_LIBDIR}  # Явное указание каталога
        --config $<CONFIG>
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS cppzmq
        COMMENT "Installing cppzmq to ${CPPZMQ_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}"
        VERBATIM
)

# Добавление путей для заголовочных файлов
include_directories(${CPPZMQ_ROOT_DIR})

#--------------------------------------------------------------
# 4. Driver Factory Library
#--------------------------------------------------------------
add_library(driver_factory SHARED ${PROJ_SRC_DIR}/service/driver_factory.cpp)

# Настройка свойств библиотеки
set_target_properties(driver_factory PROPERTIES
        VERSION 1.0.1
        SOVERSION 1
        OUTPUT_NAME "driver_factory"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "\$ORIGIN"
        LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
        ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
)

# Настройки компиляции
target_compile_features     (driver_factory PUBLIC cxx_std_17)
target_include_directories  (driver_factory PUBLIC ${PROJ_INC_DIR} )

# Экспорт символов
target_compile_definitions(driver_factory PRIVATE
        $<$<NOT:$<BOOL:${WIN32}>>:DRIVER_API_VISIBILITY>
)

# Установка библиотеки
install(TARGETS driver_factory
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Платформо-специфичные настройки
if(UNIX AND NOT APPLE)
    target_compile_options  (driver_factory PRIVATE -fPIC -Wall -Wextra)
    target_link_options     (driver_factory PRIVATE -Wl,--no-undefined -Wl,--as-needed )
endif()

#--------------------------------------------------------------
# Основные подпроекты (с унификацией путей библиотек)
#--------------------------------------------------------------
# Для каждого подпроекта добавляем передачу CMAKE_INSTALL_LIBDIR
#add_subdirectory(${PROJ_SUB_DIR}/json)              # --- JSON (header-only)
#add_subdirectory(${PROJ_SRC_DIR}/factory)           # --- driver factory

# библиотеки драйверов
# Убедитесь, что в каждом подпроекте есть:
# install(TARGETS ... LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# автоподгружаемые модули (плагины)
add_subdirectory(${PROJ_SUB_DIR}/libmodbus)         # --- modbus (пока в разработке)
#add_subdirectory(${PROJ_SUB_DIR}/CANopen)           # --- CANopen
#add_subdirectory(${PROJ_SUB_DIR}/EtherCAT)          # --- EtherCAT

# Копирование конфигов в директорию сборки
configure_file(${PROJ_DIR}/modules_config.json ${PROJ_ETC_DIR}/modules_config.json  COPYONLY)
configure_file(${PROJ_DIR}/zmq.properties      ${PROJ_ETC_DIR}/zmq.properties       COPYONLY)

# =============================================================
# Главный исполняемый модуль (обновленные настройки)
# =============================================================
#--------------------------------------------------------------
# Проверка наличия необходимых компонентов
#--------------------------------------------------------------
# driver_factory
find_library(DRIVER_FACTORY_LIB driver_factory PATHS ${PROJ_LIB_DIR} NO_DEFAULT_PATH REQUIRED)

# json
# 1. Проверяем наличие заголовков JSON в .deploy/include
find_path(JSON_INCLUDE_DIR NAMES nlohmann/json.hpp PATHS ${PROJ_INC_DIR} NO_DEFAULT_PATH REQUIRED)

# 2. Создаем интерфейсную цель для JSON (header-only)
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${JSON_INCLUDE_DIR})

# 3. Для совместимости с кодом, ожидающим подпроект json
add_library(json ALIAS nlohmann_json)

#--------------------------------------------------------------
# Сборка исполняемого модуля
#--------------------------------------------------------------
build_target(${proj} EXE
        OPTS
            -g -O0 -w -fPIC
        PRPS
            CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
        INCS
            ${PROJ_INC_DIR}
            ${PROJ_INC_DIR}/sd
            ${PROJ_INC_DIR}/zmq
            ${PROJ_INC_DIR}/iec
            ${PROJ_SRC_DIR}/main
            ${PROJ_SRC_DIR}/service/zmq
        SRCS
            :MASK ${PROJ_SRC_DIR}/main/*.cpp
            :MASK ${PROJ_SRC_DIR}/service/*.cpp
            :MASK ${PROJ_SRC_DIR}/service/zmq/*.cpp
        LNKS
            json
            driver_factory
            libzmq
            cppzmq
            modbus

            #nlohmann_json
            #plc_main
            #can_master
            #ec_master
)

#--------------------------------------------------------------
# Настройка RPATH только для относительных путей
#--------------------------------------------------------------
set_target_properties(${proj} PROPERTIES
        INSTALL_RPATH "\$ORIGIN:\$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
        BUILD_WITH_INSTALL_RPATH TRUE
)

#--------------------------------------------------------------
# Поиск и линковка с plc_main
#--------------------------------------------------------------
find_library(PLC_MAIN_LIB plc_main PATHS ${PROJ_LIB_DIR} NO_DEFAULT_PATH REQUIRED )
target_link_libraries(${proj} PRIVATE ${PLC_MAIN_LIB})

##--------------------------------------------------------------
## Флаги безопасности (обновленные)
##--------------------------------------------------------------
#if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#    target_compile_options(${proj} PRIVATE
#            -D_GNU_SOURCE
#            -Wall -Wextra -Wpedantic
#            -fstack-protector-strong
#            -Wl,-z,now
#            -fstack-clash-protection
#            -fcf-protection=full
#            -D_FORTIFY_SOURCE=2
#    )
#    target_link_options(${proj} PRIVATE
#            -Wl,--as-needed
#            -Wl,--no-undefined
#            -Wl,-z,relro,-z,now
#    )
#endif()

#--------------------------------------------------------------
# Systemd integration - Устанавливаем связь с библиотекой systemd
#--------------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD libsystemd)

if(SYSTEMD_FOUND AND LINUX)
    message(STATUS "Systemd development files found")
    target_compile_definitions(${proj} PRIVATE HAVE_SYSTEMD=1)
    target_include_directories(${proj} PRIVATE ${SYSTEMD_INCLUDE_DIRS})
    target_link_libraries(${proj} PRIVATE ${SYSTEMD_LIBRARIES})
else()
    message(WARNING "Systemd development files not found - sd_notify will be disabled")
    #target_compile_definitions(${proj} PRIVATE NO_SYSTEMD=1)
endif()

#--------------------------------------------------------------
# Установка компонентов
#--------------------------------------------------------------
install(TARGETS ${proj}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Установка конфигов
install(DIRECTORY
        DESTINATION "${PROJ_INS_DIR}/etc"
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

install(FILES
        ${PROJ_DIR}/modules_config.json
        ${PROJ_DIR}/zmq.properties
        DESTINATION "${PROJ_INS_DIR}/etc"
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

# Сообщение для логирования
message(STATUS "Service configs will be in: ${PROJ_INS_DIR}/etc")

#--------------------------------------------------------------
# Systemd service installation
#--------------------------------------------------------------
if(UNIX AND NOT APPLE)
    # 1. Генерация файла окружения
    configure_file(
            ${PROJ_DIR}/procont-environment.in
            ${CMAKE_BINARY_DIR}/procont-environment
            @ONLY
    )

    # Установка
    install(FILES
            ${CMAKE_BINARY_DIR}/procont-environment
            DESTINATION "${PROJ_INS_DIR}/etc"
            PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ
    )

    # 2. Configure service file (from template)
    set(SERVICE_USER "master")  # Или другое значение
    configure_file(
            ${PROJ_DIR}/${PROJECT_NAME}.service.in
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service
            @ONLY
    )

    # Установка сервиса (локально)
    set(SYSTEMD_LOCAL_DIR "${PROJ_INS_DIR}/systemd")
    file(MAKE_DIRECTORY "${SYSTEMD_LOCAL_DIR}")
    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.service
            DESTINATION "${SYSTEMD_LOCAL_DIR}"
            PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    )

    # 3. Install startup script локально
    install(PROGRAMS
            ${PROJ_DIR}/${PROJECT_NAME}-startup.sh
            DESTINATION "${PROJ_INS_DIR}/bin"
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE
    )

    # 4. Генерация скрипта для установки сервиса
    file(GENERATE
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/install_service.sh"
            CONTENT
            "#!/bin/bash
sudo cp \"${SYSTEMD_LOCAL_DIR}/${PROJECT_NAME}.service\" /lib/systemd/system/
sudo systemctl daemon-reload
echo \"Service installed. Run manually:\"
echo \"  sudo systemctl enable ${PROJECT_NAME}.service\"
echo \"  sudo systemctl start ${PROJECT_NAME}.service\""
    )

    # Устанавливаем скрипт в /bin
    install(PROGRAMS
            "${CMAKE_CURRENT_BINARY_DIR}/install_service.sh"
            DESTINATION "${PROJ_INS_DIR}/bin"
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    )

    message(STATUS "Systemd service will be installed locally to: ${SYSTEMD_LOCAL_DIR}")
    message(STATUS "Use ${PROJ_INS_DIR}/bin/install_service.sh for system installation")
endif()

##--------------------------------------------------------------
## Target для отладки (с дополнительной информацией)
##--------------------------------------------------------------
#add_custom_target(debug_env
#        COMMAND ${CMAKE_COMMAND} -E echo "=== Build Environment ==="
#        COMMAND ${CMAKE_COMMAND} -E echo "Compiler: ${CMAKE_CXX_COMPILER}"
#        COMMAND ${CMAKE_COMMAND} -E echo "Target arch: ${LIB_ARCH}"
#        COMMAND ${CMAKE_COMMAND} -E echo "Library dir: ${CMAKE_INSTALL_LIBDIR}"
#        COMMAND ${CMAKE_COMMAND} -E echo "OpenSSL path: ${OPENSSL_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}"
#        COMMAND ${CMAKE_COMMAND} -E echo "Install prefix: ${CMAKE_INSTALL_PREFIX}"
#        VERBATIM
#)

MESSAGE("------------------- PROJECT: ${PROJECT_NAME} END")
