#include "client_operations.hpp"
#include <sys/socket.h>
#include <thread>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <mutex>
#define BACK_LOGS_NUM 100
#define THREAD_POOL_SIZE 20

namespace server_side{
    class Server{
    private:
        const unsigned int m_port;
        const client_operations::ClientHandler &m_clientHandler;
        int m_fileDescriptor;

    public:
        /**
         * @brief Construct a new Server object
         * 
         * @param port - port to listen.
         * @param clientHandler - deal with type of message.
         */
        Server(const unsigned int port, const client_operations::ClientHandler &clientHandler) noexcept;

        /**
         * @brief The function open the server and listen for clients.
         * 
         */
        virtual void open() = 0;

        /**
         * @brief The function close the server.
         * 
         */
        virtual void stop() const = 0;

        /**
         * @brief The function check errors and throw appopriate exception if should.
         * 
         * @param returnValue - return value of function.
         * @param socketFileDescriptor - file descriptor of sock.
         */
        void errorCheck(const int returnValue) const;

       /**
        * @brief The function create a file descriptor of tcp socket with appopriate parameters.
        * 
        * @return sockaddr_in - struct of socket information.
        */
        sockaddr_in createFileDescriptor();

        /**
         * @brief The function set new value to file descriptor.
         * 
         * @param fileDescriptor -  new value of file descriptor.
         */
        void setFileDescriptor(const int fileDescriptor);

        /**
         * @brief The function return file descriptor.
         * 
         * @return int - file descriptor.
         */
        int getFileDescriptor() const;

        /**
         * @brief The function return client handler.
         * 
         * @return const client_operations::ClientHandler& - client handler. 
         */
        const client_operations::ClientHandler& getClientHandler() const;
    };


    class ParallelServer : public Server {
    private:
        std::vector<std::thread> m_threadPoolVector;
        std::vector<int> m_clients;
    public:
        /**
         * @brief Construct a new Serial Server object
         * 
         * @param port - port to listen.
         * @param clientHandler - deal with type of message.
         */
        ParallelServer(const unsigned int port, const client_operations::ClientHandler &clientHandler) noexcept;

        /**
         * @brief The function open the server and listen for clients.
         * 
         */
        void open();

        /**
         * @brief The function close the server.
         * 
         */
        void stop() const;

       /**
        * @brief The function accept clients and handle with them.
        * 
        * @param addres - struct of socket information.
        */
        void acceptClients(sockaddr_in addres);

        void handleClientConnection();
    };
}