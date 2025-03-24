//-----------------------------------------------------------------------------
// Copyright 2020 Ambitecs
//-----------------------------------------------------------------------------
#include <cstdio>
#include <cerrno>
#include <netdb.h>
#include <cstring>
#include <cstdlib>

#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#include "ladder.h"

#define MAX_INPUT 16
#define MAX_OUTPUT 16
#define MAX_MODBUS 100
#define NET_BUFFER_SIZE 10000

//-----------------------------------------------------------------------------
// Verify if all errors were cleared on a socket
//-----------------------------------------------------------------------------
int getSO_ERROR(int fd) {
   int err = 1;
   socklen_t len = sizeof(err);
   if (getsockopt(fd, SOL_SOCKET, SO_ERROR, (char *)&err, &len)==-1) {
       perror("getSO_ERROR");
   }
    // set errno to the socket SO_ERROR
   if (err) errno = err;
   return err;
}

//-----------------------------------------------------------------------------
// Properly close a socket
//-----------------------------------------------------------------------------
void closeSocket(int fd) {
   if (fd >= 0) {
      // (1) first clear any errors, which can cause close to fail
      getSO_ERROR(fd);
       // (2) secondly, terminate the 'reliable' delivery
      if (shutdown(fd, SHUT_RDWR) < 0) {
          // SGI causes EINVAL
          if (errno != ENOTCONN && errno != EINVAL) perror("shutdown");
      }
      // (3) finally call close()
      if (close(fd) < 0) perror("close");
   }
}

//-----------------------------------------------------------------------------
// Set or Reset the O_NONBLOCK flag from sockets
//-----------------------------------------------------------------------------
bool SetSocketBlockingEnabled(int fd, bool blocking) {
   if (fd < 0) return false;
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags == -1) return false;
   flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0);
}

//-----------------------------------------------------------------------------
// Create the socket and bind it.
// Returns the file descriptor for the socket created.
//-----------------------------------------------------------------------------
int createSocket(int port) {
    char log_msg[1000];
    struct sockaddr_in server_addr{};

    // Create TCP Socket
    int socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if (socket_fd<0) {
        sprintf(log_msg, "Server: error creating stream socket => %s\n", strerror(errno));
        log(log_msg);
        return -1;
    }
    
    // Set SO_REUSEADDR
    int enable = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
    }
    SetSocketBlockingEnabled(socket_fd, false);

    // Initialize Server Struct
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind socket
    if (bind(socket_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        sprintf(log_msg, "Server: error binding socket => %s\n", strerror(errno));
        log(log_msg);
        return -1;
    }
    
    // We accept max 5 pending connections
    listen(socket_fd,5);

    sprintf(log_msg, "Server: Listening on port %d\n", port);
    log(log_msg);
    return socket_fd;
}

//-----------------------------------------------------------------------------
// Blocking call. Wait here for the client to connect.
// Returns the file descriptor to communicate with the client.
//-----------------------------------------------------------------------------
int waitForClient(int socket_fd, int protocol_type) {

    bool *run_server = nullptr;
    switch (protocol_type) { //NOLINT
        case MODBUS_PROTOCOL:   run_server = &run_modbus;   break;
        //case DNP3_PROTOCOL:   run_server = &run_dnp3;     break;
        //case ENIP_PROTOCOL:   run_server = &run_enip;     break;
        default:;
    }

    char log_msg[1000];
    sprintf(log_msg, "Server: waiting for new client...\n");
    log(log_msg);

    int client_fd;
    struct sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    while (run_server!= nullptr && *run_server) {
        //non-blocking call
        client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd > 0)
        {
            SetSocketBlockingEnabled(client_fd, true);
            break;
        }
        sleepms(100);
    }

    return client_fd;
}

//-----------------------------------------------------------------------------
// Blocking call. Holds here until something is received from the client.
// Once the message is received, it is stored on the buffer and the function
// returns the number of bytes received.
//-----------------------------------------------------------------------------
long listenToClient(int client_fd, unsigned char *buffer) {
    bzero(buffer, NET_BUFFER_SIZE);
    return read(client_fd, buffer, NET_BUFFER_SIZE);
}

//-----------------------------------------------------------------------------
// Process client's request
//-----------------------------------------------------------------------------
void processMessage(unsigned char *buffer, long bufferSize, int client_fd, int protocol_type) {
    int messageSize = 0;
    switch (protocol_type) // NOLINT
    {
        case MODBUS_PROTOCOL:
            messageSize = processModbusMessage(buffer, bufferSize);
            write(client_fd, buffer, messageSize);
            break;

        //// DNP3 OFF
//        case DNP3_PROTOCOL:
//            break;

        //// ENIP OFF (-!-)
//        case ENIP_PROTOCOL:
//            messageSize = processEnipMessage(buffer, bufferSize);
//            write(client_fd, buffer, messageSize);
//            break;

        default:;
    }
}

//-----------------------------------------------------------------------------
// Thread to handle requests for each connected client
//-----------------------------------------------------------------------------
void *handleConnections(void *arguments) {
    int *args = (int *) arguments;
    int client_fd     = args[0];
    int protocol_type = args[1];

    char log_msg[1000];
    sprintf(log_msg, "Server: Thread created for client ID: %d\n", client_fd);
    log(log_msg);

    bool *run_server = nullptr;
    switch (protocol_type) { //NOLINT
        case MODBUS_PROTOCOL:   run_server = &run_modbus;   break;
        //case DNP3_PROTOCOL:     run_server = &run_dnp3;     break;
        //case ENIP_PROTOCOL:     run_server = &run_enip;     break;
        default:;
    }

    while (run_server != nullptr && *run_server)
    {
        // Чтение запроса
        long messageSize = 0;
        unsigned char buffer[NET_BUFFER_SIZE];
        messageSize = listenToClient(client_fd, buffer);
        if (messageSize <= 0 || messageSize > NET_BUFFER_SIZE) {
            // something has gone wrong or the client has closed connection
            if (messageSize == 0) {
                sprintf(log_msg,"Modbus Server: client ID: %d has closed the connection\n", client_fd);
                log(log_msg);
            } else {
                sprintf(log_msg,
                        "Modbus Server: Something is wrong with the client ID: %d message Size : %i\n",
                        client_fd, (int)messageSize);
                log(log_msg);
            }
            break;
        }

        // Обработка запроса клиента
        processMessage(buffer, messageSize, client_fd, protocol_type);
    }

    //printf("Debug: Closing client socket and calling pthread_exit in server.cpp\n");
    close(client_fd);
    sprintf(log_msg, "Terminating Modbus connections thread\r\n");
    log(log_msg);

    pthread_exit(nullptr);
}

//-----------------------------------------------------------------------------
// Function to start the server.
// It receives the port number as argument and creates an infinite loop
// to listen and parse the messages sent by the clients
//-----------------------------------------------------------------------------
void startServer(uint16_t port, int protocol_type)
{
    char log_msg[1000];
    int socket_fd, client_fd;

    socket_fd = createSocket(port);
    if (socket_fd == -1) exit(1);

    bool *run_server = nullptr;
    switch (protocol_type) { //NOLINT
        case MODBUS_PROTOCOL:   run_server = &run_modbus;   break;
        //case DNP3_PROTOCOL:     run_server = &run_dnp3;     break;
        //case ENIP_PROTOCOL:     run_server = &run_enip;     break;
        default:;
    }

    while (run_server != nullptr && *run_server)
    {
        // Ждёт подключения клиента (block until a client connects) ...
        client_fd = waitForClient(socket_fd, protocol_type);

        if (client_fd < 0) {
            sprintf(log_msg, "Server: Error accepting client!\n");
            log(log_msg);
        }
        else
        {
            sprintf(log_msg,
                    "Server: Client accepted!\nCreating thread for the new client ID: %d...\n", client_fd);
            log(log_msg);

            int arguments[2];
            arguments[0] = client_fd;
            arguments[1] = protocol_type;
            pthread_t thread;

            int ret = pthread_create
                    (
                    &thread,
                    nullptr,
                    handleConnections,
                    (void*)arguments
                    );

            if (ret==0) {
                // if SUCCEEDED - detach thread (ZOMBIE)
                pthread_detach(thread);
            }
        }
    }

    close(socket_fd);
    close(client_fd);
    sprintf(log_msg, "Terminating Server thread\r\n");
    log(log_msg);
}

//-----------------------------------------------------------------------------
