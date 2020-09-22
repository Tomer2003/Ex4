#include "server.hpp"

std::mutex clients_vector_mutex;

namespace server_side{

    Server::Server(const unsigned int port, client_operations::ClientHandler &clientHandler) noexcept : m_port(port), m_clientHandler(clientHandler), m_fileDescriptor(0) {    }

    void Server::setFileDescriptor(const int fileDescriptor){
        this->m_fileDescriptor = fileDescriptor;
    }

    int Server::getFileDescriptor() const{
        return m_fileDescriptor;
    }

    client_operations::ClientHandler& Server::getClientHandler() {
        return m_clientHandler;
    }

    sockaddr_in Server::createFileDescriptor(){
        int fileDescriptor;
        exceptions::serverErrorCheck(fileDescriptor = socket(AF_INET, SOCK_STREAM, 0), STATUS_SERVER_OPEN_SOCKET_EXCEPTION, m_fileDescriptor);
        setFileDescriptor(fileDescriptor);

       sockaddr_in address;
       address.sin_family = AF_INET;
       address.sin_port = htons(m_port);
       address.sin_addr.s_addr = INADDR_ANY;

       exceptions::serverErrorCheck(bind(fileDescriptor, reinterpret_cast<sockaddr*>(&address), sizeof(sockaddr)), STATUS_SERVER_BIND_EXCEPTION, getFileDescriptor());

       exceptions::serverErrorCheck(listen(fileDescriptor, BACK_LOGS_NUM), STATUS_SERVER_LISTEN_EXCEPRION, getFileDescriptor());

       return address;
    }

    ParallelServer::ParallelServer(const unsigned int port,  client_operations::ClientHandler &clientHandler) noexcept : Server(port, clientHandler) {
        for(int i = 0; i < THREAD_POOL_SIZE; ++i){
            std::thread thread(&ParallelServer::handleClientConnection, this);
            m_threadPoolVector.push_back(std::move(thread));
        }
    }

    void ParallelServer::acceptClients(sockaddr_in address){
        auto addressLen = sizeof(address);
        while(true){
            int socketNum;
            exceptions::serverErrorCheck(socketNum = accept(getFileDescriptor(), reinterpret_cast<sockaddr*>(&address), (socklen_t*)&addressLen), STATUS_SERVER_ACCEPT_EXCEPTION, getFileDescriptor());
            clients_vector_mutex.lock();
            m_clients.push_back(socketNum);
            clients_vector_mutex.unlock();
        }

    }

    void ParallelServer::handleClientConnection(){
        int client;
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