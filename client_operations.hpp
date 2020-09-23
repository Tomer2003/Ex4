#pragma once

#include "solver_tasks.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <mutex>
#include <atomic>
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
        virtual void handleClient(const int clientFielDescriptor, const int serverFileDescriptor) = 0;

        /**
         * @brief The function send error message to client and close the socket.
         * 
         * @param clientFileDescriptor - client file descriptor.
         * @param exceptoin - exception.
         */
        virtual void handleException(int clientFileDescriptor, const exceptions::Exception& exceptoin) const = 0; 
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
        void handleClient(const int clientFielDescriptor, const int serverFileDescriptor);   

        /**
         * @brief The function handle with define problem part in the grapth path handler protocol
         * 
         * @param clientFielDescriptor - client file descriptor
         * @param serverFileDescriptor - server file descriptor
        */
        std::string defineProblemMessageHandler(const int clientFielDescriptor, const int serverFileDescriptor) const;

         /**
         * @brief The function handle with problem part in the grapth path handler protocol
         * 
         * @param clientFielDescriptor - client file descriptor
         * @param serverFileDescriptor - server file descriptor
         */
        void dataProblemHandler(const int clientFielDescriptor, const int serverFileDescriptor, const std::string& algorithm) ;

        /**
         * @brief The function send error message to client and close the socket.
         * 
         * @param clientFileDescriptor - client file descriptor.
         * @param exceptoin - exception.
         */
        virtual void handleException(int clientFileDescriptor, const exceptions::Exception& exceptoin) const;

        /**
         * @brief The function stop client connection if the server waits more than 5 seconds to client message
         * 
         * @param serverFileDscriptor - server file descriptor
         * @param clientResponse - if the client response
         * @param responseMoreThanAvailable - if response take more than available time
         */
        void stopConnection(std::atomic<bool>& clientResponse, std::atomic<bool>& responseMoreThanAvailable, const int clientFileDscriptor) const;

        /**
         * @brief The function return message without multiply spaces or tabs
         * 
         * @param string - string to remove multiply spaces or tabs
         */
        static void getMessageWithoutMultipleSpaces(std::string& string);

        /**
         * @brief The function check if the string is integer
         * 
         * @param string - string
         * @return true - the string is integer
         * @return false - the string is not integer
         */
        static bool isInteger(const std::string& string);

        /**
         * @brief The function return index of spesific occurence of char
         * 
         * @param string - string
         * @param ch - char
         * @param occurrence - occurrence
         * @return unsigned int - index
         */
        static unsigned int getIndexOccurences(std::string string, const char ch, const int occurrence);
        
        /**
         * @brief The function replace part of string to another string
         * 
         * @param str - string
         * @param from - part to replace
         * @param to - replacing part
         */
        static void replaceAll(std::string& str, const std::string& from, const std::string& to);

        /**
         * @brief The functoin return solution of spesific algorithm
         * 
         * @param searchable - searchable object
         * @param algorithm - algorithm
         * @return solver_tasks::Solution<solver_tasks::PointNode>& 
         */
        solver_tasks::Solution<solver_tasks::PointNode> getFactorAlgorithmSolution(solver_tasks::MatrixGraphPath& searchable, const std::string& algorithm);
    
         /**
         * @brief The function checks if two string are equal in case sensetive
         * 
         * @param string1 - string1
         * @param string2 - string2
         * @return true - equals
         * @return false - not equals
         */
        static bool equalsCaseSensetive(const std::string& string1, const std::string& string2);
    };

}