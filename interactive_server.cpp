//-----------------------------------------------------------------------------
// Copyright 2018 Ambitecs
//-----------------------------------------------------------------------------

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <pthread.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <ctime>

#include "ladder.h"
#define BUFFER_SIZE 1024

//Global Variables
//__attribute__((unused))
bool ethercat_configured = false;
char ethercat_conf_file[BUFFER_SIZE];

time_t start_time;
time_t end_time;

int  command_index = 0;
bool processing_command = false;
unsigned char server_command[1024];

// Thread procedure arguments
char arg_str[128]{};
uint16_t pstorage_polling = 10;
//uint16_t modbus_port = 502;
//uint16_t dnp3_port = 20000;
//uint16_t enip_port = 44818;

// Global Threads
bool run_pstorage   = false;    // persistent storage
bool run_modbus     = false;    // modbus
bool run_can_master = false;    // can_master
//bool run_dnp3 = false;
//bool run_enip = false;

pthread_t pstorage_thread;
pthread_t modbus_thread;
pthread_t can_master_thread;
//pthread_t dnp3_thread;
//pthread_t enip_thread;

////-----------------------------------------------------------------------------
//// Configure Ethercat (not used)
////-----------------------------------------------------------------------------
//int configureEthercat() {
//    return 1;
//}

//-----------------------------------------------------------------------------
// Start the Modbus Thread
//-----------------------------------------------------------------------------
void *modbusThread(void *arg) {
    startServer(arg_str, MODBUS_PROTOCOL);
    return nullptr;
}

//-----------------------------------------------------------------------------
// Start the CAN Master Thread
//-----------------------------------------------------------------------------
void *can_masterThread(void *arg) {
    while (run_can_master) {
        sleep(1);
    }
    return nullptr;
}

////-----------------------------------------------------------------------------
//// Start the DNP3 Thread
////-----------------------------------------------------------------------------
//void *dnp3Thread(void *arg)
//{
//    dnp3StartServer(dnp3_port);
//}

////-----------------------------------------------------------------------------
//// Start the Enip Thread
////-----------------------------------------------------------------------------
//void *enipThread(void *arg)
//{
//    startServer(enip_port, ENIP_PROTOCOL);
//}
//

//-----------------------------------------------------------------------------
// Start the Persistent Storage Thread
//-----------------------------------------------------------------------------
void *pstorageThread(void *arg) {
    startPstorage();
    return nullptr;
}

//-----------------------------------------------------------------------------
// Read the argument from a command function
//-----------------------------------------------------------------------------
int readCommandArgument(const char *command) {
    int i = 0, j = 0;
    char argument[1024];
    
    while (command[i] != '(' && command[i] != '\0') i++;
    if (command[i] == '(') i++;
    while (command[i] != ')' && command[i] != '\0')
    {
        argument[j++] = command[i++];
        argument[j] = '\0';
    }
    return atoi(argument);
}
//-----------------------------------------------------------------------------
// Read string argument from a command function
//-----------------------------------------------------------------------------
char *readCommandArgumentStr(const char *command) {
    int i = 0, j = 0;
    static char argument[1024];
//    unsigned char *argument;
//    argument = (unsigned char *)malloc(1024 * sizeof(unsigned char));
    
    while (command[i] != '(' && command[i] != '\0') i++;
    if (command[i] == '(') i++;
    while (command[i] != ')' && command[i] != '\0') {
        argument[j++] = command[i++];
        argument[j] = '\0';
    }
    return argument;
}

//-----------------------------------------------------------------------------
// Create the socket and bind it.
// Returns the file descriptor for the socket created.
//-----------------------------------------------------------------------------
int createSocket_interactive(int port) {
    char log_msg[1000];
    int socket_fd;
    struct sockaddr_in server_addr{};

    // Create TCP Socket
    socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if (socket_fd<0)
    {
        sprintf(log_msg, "Interactive Server: error creating stream socket => %s\n", strerror(errno));
        log(log_msg);
        return -1;
    }
    
    // Set SO_REUSEADDR
    int enable = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
        
    SetSocketBlockingEnabled(socket_fd, false);
    
    // Initialize Server Struct
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(port);

    // Bind socket
    if (bind(socket_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        sprintf(log_msg, "Interactive Server: error binding socket => %s\n", strerror(errno));
        log(log_msg);
        return -1;
    }

    // We accept max 5 pending connections
    listen(socket_fd,5);

    sprintf(log_msg, "Interactive Server: Listening on port %d\n", port);
    log(log_msg);
    return socket_fd;
}

//-----------------------------------------------------------------------------
// Blocking call. Wait here for the client to connect. Returns the file
// descriptor to communicate with the client.
//-----------------------------------------------------------------------------
int waitForClient_interactive(int socket_fd) {
    printf("Interactive Server: waiting for new client...\n");
    int client_fd;
    struct sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    while (run_openplc) {
        client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len); //non-blocking call
        if (client_fd > 0) {
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
long listenToClient_interactive(int client_fd, unsigned char *buffer) {
    bzero(buffer, 1024);
    return read(client_fd, buffer, 1024);
}

//-----------------------------------------------------------------------------
// Process client's commands for the interactive server
//-----------------------------------------------------------------------------
bool cmdIs (const char *key, const char *proto) { 
    return (strncmp(key, proto, strlen(proto)) == 0); 
}

void processCommand(/*unsigned*/ char *buffer, int client_fd)
{
    char log_msg[1200];
    int count_char = 0;

    // If command in process - returned
    if (processing_command) {
        count_char = sprintf(buffer, "Processing command...\n");
        write(client_fd, buffer, count_char);
        return;
    }

    if (cmdIs(buffer, "start_modbus("))
    {
        processing_command = true;
        {
            //modbus_port = readCommandArgument((buffer));
            strncpy(arg_str, readCommandArgumentStr((buffer)), 127);

            sprintf(log_msg, "Issued start_modbus() command to start on port: %s\n", arg_str);
            log(log_msg);

            if (run_modbus) {
                sprintf(log_msg, "Modbus server already active. Restarting on port: %s\n", arg_str);
                log(log_msg);

                //Stop Modbus server
                run_modbus = false;
                pthread_join(modbus_thread, nullptr);
                sprintf(log_msg, "Modbus server was stopped\n");
                log(log_msg);
            }

            //Start Modbus server
            run_modbus = true;
            pthread_create(
                    &modbus_thread,
                    nullptr,
                    modbusThread,
                    nullptr
                    );
        }
        processing_command = false;
    }

    else if (cmdIs(buffer, "stop_modbus()"))
    {
        processing_command = true;
        {
            sprintf(log_msg, "Issued stop_modbus() command\n");
            log(log_msg);
            if (run_modbus) {
                run_modbus = false;
                pthread_join(modbus_thread, nullptr);
                sprintf(log_msg, "Modbus server was stopped\n");
                log(log_msg);
            }
        }
        processing_command = false;
    }

    else if (cmdIs(buffer, "start_can_master(")) {
        processing_command = true;
        {
            strncpy(arg_str, readCommandArgumentStr((buffer)), 127);

            sprintf(log_msg, "Issued start_can_master() command to start on %s\n", arg_str);
            log(log_msg);

            if (run_can_master) {
                sprintf(log_msg, "CAN Master server already active. Restarting on %s\n", arg_str);
                log(log_msg);

                //Stop CAN Master server
                run_can_master = false;
                pthread_join(can_master_thread, nullptr);
                sprintf(log_msg, "CAN Master server was stopped\n");
                log(log_msg);
            }

            //Start CAN Master server
            run_modbus = true;
            pthread_create(
                    &can_master_thread,
                    nullptr,
                    can_masterThread,
                    nullptr
                    );

        }
        processing_command = false;
    }

    else if (cmdIs(buffer, "stop_can_master()"))
    {
        processing_command = true;
        {
            sprintf(log_msg, "Issued stop_can_master() command\n");
            log(log_msg);

            if (run_can_master) {
                run_can_master = false;
                pthread_join(can_master_thread, nullptr);
                sprintf(log_msg, "CAN Master server was stopped\n");
                log(log_msg);
            }
        }
        processing_command = false;
    }

        //else if (cmdIs(buffer, "start_ethercat("))
    //{
    //    processing_command = true;
    //    {
    //        char *argument;
    //        argument = readCommandArgumentStr(buffer);
    //        strcpy(ethercat_conf_file, argument);
    //        free(argument);
    //        sprintf(log_msg, "Issued start_ethercat() command to start with config: %s\n", ethercat_conf_file);
    //        log(log_msg);
    //
    //        //Configure ethercat (not used)
    //        //ethercat_configured = configureEthercat();
    //
    //    }
    //    processing_command = false;
    //}

    //else if (cmdIs(buffer, "start_dnp3("))
    //{
    //    processing_command = true;
    //    dnp3_port = readCommandArgument(buffer);
    //    sprintf(log_msg, "Issued start_dnp3() command to start on port: %d\n", dnp3_port);
    //    log(log_msg);
    //    if (run_dnp3)
    //    {
    //        sprintf(log_msg, "DNP3 server already active. Restarting on port: %d\n", dnp3_port);
    //        log(log_msg);
    //        //Stop DNP3 server
    //        run_dnp3 = false;
    //        pthread_join(dnp3_thread, nullptr);
    //        sprintf(log_msg, "DNP3 server was stopped\n");
    //        log(log_msg);
    //    }
    //    //Start DNP3 server
    //    run_dnp3 = 1;
    //    pthread_create(&dnp3_thread, nullptr, dnp3Thread, nullptr);
    //    processing_command = false;
    //}

    //else if (cmdIs(buffer, "stop_dnp3()"))
    //{
    //    processing_command = true;
    //    {
    //        sprintf(log_msg, "Issued stop_dnp3() command\n");
    //        log(log_msg);
    //        if (run_dnp3) {
    //            run_dnp3 = false;
    //            pthread_join(dnp3_thread, nullptr);
    //            sprintf(log_msg, "DNP3 server was stopped\n");
    //            log(log_msg);
    //        }
    //    }
    //    processing_command = false;
    //}

    //else if (cmdIs(buffer, "start_enip("))
    //{
    //    processing_command = true;
    //    {
    //        enip_port = readCommandArgument(buffer);
    //        sprintf(log_msg, "Issued start_enip() command to start on port: %d\n", enip_port);
    //        log(log_msg);
    //        if (run_enip) {
    //            sprintf(log_msg, "EtherNet/IP server already active. Restarting on port: %d\n", enip_port);
    //            log(log_msg);
    //            //Stop Enip server
    //            run_enip = false;
    //            pthread_join(enip_thread, nullptr);
    //            sprintf(log_msg, "EtherNet/IP server was stopped\n");
    //            log(log_msg);
    //        }
    //        //Start Enip server
    //        run_enip = true;
    //        pthread_create(&enip_thread, nullptr, enipThread, nullptr);
    //    }
    //    processing_command = false;
    //}

    //else if (cmdIs(buffer, "stop_enip()"))
    //{
    //    processing_command = true;
    //    {
    //        sprintf(log_msg, "Issued stop_enip() command\n");
    //        log(log_msg);
    //        if (run_enip) {
    //            run_enip = false;
    //            pthread_join(enip_thread, nullptr);
    //            sprintf(log_msg, "EtherNet/IP server was stopped\n");
    //            log(log_msg);
    //        }
    //    }
    //    processing_command = false;
    //}

    else if (cmdIs(buffer, "start_pstorage("))
    {
        processing_command = true;
        {
            pstorage_polling = readCommandArgument(buffer);
            sprintf(log_msg, "Issued start_pstorage() command with polling rate of %d seconds\n", pstorage_polling);
            log(log_msg);
            if (run_pstorage) {
                sprintf(log_msg, "Persistent Storage server already active. Changing polling rate to: %d\n",
                        pstorage_polling);
                log(log_msg);
            }
            //Start Enip server
            run_pstorage = true;
            pthread_create(&pstorage_thread, nullptr, pstorageThread, nullptr);
        }
        processing_command = false;
    }

    else if (cmdIs(buffer, "stop_pstorage()"))
    {
        processing_command = true;
        {
            sprintf(log_msg, "Issued stop_pstorage() command\n");
            log(log_msg);
            if (run_pstorage) {
                run_pstorage = false;
                sprintf(log_msg, "Persistent Storage thread was stopped\n");
                log(log_msg);
            }
        }
        processing_command = false;
    }

    else if (cmdIs(buffer, "runtime_logs()"))
    {
        processing_command = true;
        {
            printf("Issued runtime_logs() command\n");
            write(client_fd, log_buffer, log_index);
        }
        processing_command = false;
        return;
    }

    else if (cmdIs(buffer, "exec_time()"))
    {
        processing_command = true;
        {
            time(&end_time);
            count_char = sprintf(buffer, "%llu\n", (unsigned long long) difftime(end_time, start_time));
            write(client_fd, buffer, count_char);
        }
        processing_command = false;
        return;
    }

    else if (cmdIs(buffer, "quit()"))
    {
        processing_command = true;
        {
            sprintf(log_msg, "Issued quit() command\n");
            log(log_msg);

            if (run_modbus) {
                run_modbus = false;
                pthread_join(modbus_thread, nullptr);
                sprintf(log_msg, "Modbus server was stopped\n");
                log(log_msg);
            }

            //if (run_dnp3) {
            //    run_dnp3 = false;
            //    pthread_join(dnp3_thread, nullptr);
            //    sprintf(log_msg, "DNP3 server was stopped\n");
            //    log(log_msg);
            //}

            //if (run_enip) {
            //    run_enip = false;
            //    pthread_join(enip_thread, nullptr);
            //    sprintf(log_msg, "ENIP server was stopped\n");
            //    log(log_msg);
            //}

            run_openplc = false;
        }
        processing_command = false;
    }
    else
    {
        processing_command = true;
        {
            count_char = sprintf(buffer, "Error: unrecognized command\n");
            write(client_fd, buffer, count_char);
            processing_command = false;
        }
        return;
    }
    
    count_char = sprintf(buffer, "OK\n");
    write(client_fd, buffer, count_char);
}

//-----------------------------------------------------------------------------
// Process client's request
//-----------------------------------------------------------------------------
void processMessage_interactive(const unsigned char *buffer, long bufferSize, int client_fd)
{
    for (int i = 0; i < bufferSize; i++) {
        if (buffer[i] == '\r' || buffer[i] == '\n' || buffer[i] == 0x00 || command_index >= 1024) {
            //// PROCESS COMMAND
            processCommand((char*)server_command, client_fd);
            command_index = 0;
            break;
        }
        server_command[command_index] = buffer[i];
        command_index++;
        server_command[command_index] = '\0';
    }
}

//-----------------------------------------------------------------------------
// Thread to handle requests for each connected client
//-----------------------------------------------------------------------------
void *handleConnections_interactive(void *arguments)
{
    int client_fd = *(int *)arguments;
    printf("Interactive Server: Thread created for client ID: %d\n", client_fd);

    while(run_openplc) {
        unsigned char buffer[1024];
        long messageSize = listenToClient_interactive(client_fd, buffer);

        if (messageSize <= 0 || messageSize > 1024) {
            // something has  gone wrong or the client has closed connection
            if (messageSize == 0)
            {
                printf("Interactive Server: client ID: %d has closed the connection\n", client_fd);
            }
            else
            {
                printf("Interactive Server: Something is wrong with the  client ID: %d message Size : %i\n",
                       client_fd, (int)messageSize);
            }
            break;
        }

        processMessage_interactive(buffer, messageSize, client_fd);
    }

    //printf("Debug: Closing client socket and calling pthread_exit in interactive_server.cpp\n");
    closeSocket(client_fd);
    printf("Terminating interactive server connections\r\n");
    pthread_exit(nullptr);

}

//-----------------------------------------------------------------------------
// Function to start the server. It receives the port number as argument and
// creates an infinite loop to listen and parse the messages sent by the
// clients
//-----------------------------------------------------------------------------
void startInteractiveServer(int port)
{
    char log_msg[1000];
    int socket_fd, client_fd;

    socket_fd = createSocket_interactive(port);
    if (socket_fd == -1) exit(1);

    while (run_openplc) {

        // (1) waitForClient - block until a client connects
        client_fd = waitForClient_interactive(socket_fd);
        if (client_fd < 0) {
            sprintf(log_msg, "Interactive Server: Error accepting client!\n");
            log(log_msg);
        }
        else
        {
            printf("Interactive Server: Client accepted! \n"
                   "Creating thread for the new client ID: %d...\n", client_fd);

            pthread_t thread{};
            int arguments[1];
            arguments[0] = client_fd;
            int ret = ret = pthread_create(
                    &thread,
                    nullptr,
                    handleConnections_interactive,
                    arguments);

            if (ret==0) {
                pthread_detach(thread); // ZOMBIE
            }
        }
    }
    
    printf("Shutting down internal threads\n");

    run_pstorage = false;
    run_modbus   = false;
    //run_dnp3     = false;
    //run_enip     = false;

    pthread_join(modbus_thread, nullptr);
    //pthread_join(dnp3_thread, nullptr);
    //pthread_join(enip_thread, nullptr);
    
    printf("Closing socket...\n");
    closeSocket(socket_fd);
    closeSocket(client_fd);
    printf("Terminating interactive server thread\n");
}