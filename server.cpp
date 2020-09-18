#include "server.hpp"

std::mutex clients_vector_mutex;

namespace server_side{

    Server::Server(const unsigned int port, const client_operations::ClientHandler &clientHandler) noexcept : m_port(port), m_clientHandler(clientHandler), m_fileDescriptor(0) {    }

    void Server::errorCheck(const int returnValue) const {
        if(returnValue < 0){
            //throw exceptoins
            std::cout << "error!" << std::endl;
            close(m_fileDescriptor);
            exit(1);
        }
    }

    void Server::setFileDescriptor(const int fileDescriptor){
        this->m_fileDescriptor = fileDescriptor;
    }

    int Server::getFileDescriptor() const{
        return m_fileDescriptor;
    }

    const client_operations::ClientHandler& Server::getClientHandler() const{
        return m_clientHandler;
    }

    sockaddr_in Server::createFileDescriptor(){
        int fileDescriptor;
        errorCheck(fileDescriptor = socket(AF_INET, SOCK_STREAM, 0));
        setFileDescriptor(fileDescriptor);

       sockaddr_in address;
       address.sin_family = AF_INET;
       address.sin_port = htons(m_port);
       address.sin_addr.s_addr = INADDR_ANY;

       errorCheck(bind(fileDescriptor, reinterpret_cast<sockaddr*>(&address), sizeof(sockaddr)));

       errorCheck(listen(fileDescriptor, BACK_LOGS_NUM));

       return address;
    }

    ParallelServer::ParallelServer(const unsigned int port, const client_operations::ClientHandler &clientHandler) noexcept : Server(port, clientHandler) {
        for(int i = 0; i < THREAD_POOL_SIZE; ++i){
            std::thread thread(&ParallelServer::handleClientConnection, this);
            m_threadPoolVector.push_back(std::move(thread));
        }
    }

    void ParallelServer::acceptClients(sockaddr_in address){
        auto addressLen = sizeof(address);
        std::cout << "waits for accepts: " << std::endl;
        while(true){
            int socketNum;
            errorCheck(socketNum = accept(getFileDescriptor(), reinterpret_cast<sockaddr*>(&address), (socklen_t*)&addressLen));
            std::cout << "accept!" << std::endl;
            clients_vector_mutex.lock();
            m_clients.push_back(socketNum);
            clients_vector_mutex.unlock();
        }

    }

    void ParallelServer::handleClientConnection(){
        int client;
        std::cout << "waits fo handle connections:" << std::endl;
        while(true){
            clients_vector_mutex.lock();
            if(!m_clients.empty()){
                client = m_clients[0];
                m_clients.erase(m_clients.begin());
                clients_vector_mutex.unlock();
                getClientHandler().handleClient(client, getFileDescriptor());
            }
            else{
                clients_vector_mutex.unlock();
            }
        }
    }

    void ParallelServer::open(){
        sockaddr_in address = createFileDescriptor();
        acceptClients(address);
    }

    void ParallelServer::stop() const{

    }
}