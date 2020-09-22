#pragma once

#include "solver_tasks.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <chrono> 

namespace client_operations{
    class ClientHandler{
    public:
       
        /**
         * @brief The function handle with client in spesific protocol
         * 
         * @param clientFielDescriptor - client file descriptor
         * @param serverFileDescriptor - server file descriptor
         */
        virtual void handleClient(const int clientFielDescriptor, const int serverFileDescriptor) const = 0;

        /**
         * @brief The function send error message to client and close the socket.
         * 
         * @param clientFileDescriptor - client file descriptor.
         * @param exceptoin - exception.
         */
        virtual void handleException(int clientFileDescriptor, exceptions::Exception& exceptoin) const = 0; 
    };

    class GraphPathHandler : public ClientHandler{
    private:

    public:

        
        /**
         * @brief The function handle with client to find path in grapth
         * 
         * @param clientFielDescriptor - client file descriptor
         * @param serverFileDescriptor - server file descriptor
         */
        void handleClient(const int clientFielDescriptor, const int serverFileDescriptor) const;   

        /**
         * @brief The function handle with define problem part in the grapth path handler protocol
         * 
         * @param clientFielDescriptor - client file descriptor
         * @param serverFileDescriptor - server file descriptor
         * @return true - the definition succeed
         * @return false - the definition failed
         */
        void defineProblemMessageHandler(const int clientFielDescriptor, const int serverFileDescriptor) const;

        /**
         * @brief The function send error message to client and close the socket.
         * 
         * @param clientFileDescriptor - client file descriptor.
         * @param exceptoin - exception.
         */
        virtual void handleException(int clientFileDescriptor, exceptions::Exception& exceptoin) const;

        /**
         * @brief The function stop client connection if the server waits more than 5 seconds to client message
         * 
         * @param ptrClientSendMessage - if client send message(pointer)
         * @param clientFielDescriptor - client file descriptor
         * @param stopConnection - if should stop connection(waits more than 5 seconds)
         * @param mutex - mutex 
         */
        void stopConnection(bool* ptrClientSendMessage, const int clientFielDescriptor, bool* stopConnection, std::mutex* mutex) const;

        /**
         * @brief The function return message without multiply spaces or tabs
         * 
         * @param string - string to remove multiply spaces or tabs
         */
        static void getMessageWithoutMultipleSpaces(std::string& string);
    };

}