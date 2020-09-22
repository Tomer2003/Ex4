#include "exceptions.hpp"
namespace exceptions{
    void serverErrorCheck(const int returnValue, int const status){
        if(returnValue < 0){
           switch (status)
           {
            case STATUS_SERVER_WRITE_READ_EXCEPTION:
                throw  ServerReadWriteException();
                
            case STATUS_SERVER_BIND_EXCEPTION:
                throw ServerBindException();

            case STATUS_SERVER_LISTEN_EXCEPRION:
                throw ServerListenException();

            case STATUS_SERVER_OPEN_SOCKET_EXCEPTION:
                throw ServerOpenSocketException();

            case STATUS_SERVER_ACCEPT_EXCEPTION:
                throw ServerAcceptException();           
           }
        }
    }

    Exception::Exception(unsigned int status) noexcept : m_status(status){}

    unsigned int Exception::getStatus() const{
        return m_status;
    }

    MatrixPathNotFound::MatrixPathNotFound() noexcept : Exception(STATUS_NOT_FOUND_PATH){}

    DefenitionProblemMessageException::DefenitionProblemMessageException() noexcept : Exception(STATUS_DEFENITION_PROBLEM_MESSAGE_EXCEPTION){}

    ServerReadWriteException::ServerReadWriteException() noexcept : Exception(STATUS_SERVER_WRITE_READ_EXCEPTION){}

    ServerBindException::ServerBindException() noexcept : Exception(STATUS_SERVER_BIND_EXCEPTION){}

    ServerListenException::ServerListenException() noexcept : Exception(STATUS_SERVER_LISTEN_EXCEPRION){}

    ServerOpenSocketException::ServerOpenSocketException() noexcept : Exception(STATUS_SERVER_OPEN_SOCKET_EXCEPTION){}

    ServerAcceptException::ServerAcceptException() noexcept : Exception(STATUS_SERVER_ACCEPT_EXCEPTION){}
}




