#include "exceptions.hpp"
namespace exceptions{
    void serverErrorCheck(const int returnValue, int const status, const int serverFileDescriptor){
        if(returnValue < 0){
            close(serverFileDescriptor);
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

    MatrixSizesException::MatrixSizesException() noexcept : Exception(STATUS_MATRIX_SIZES_EXCEPTION){}

    MatrixEnterPointException::MatrixEnterPointException() noexcept : Exception(STATUS_MATRIX_ENTER_POINT_EXCEPTION){}

    MatrixExitPointException::MatrixExitPointException() noexcept : Exception(STATUS_MATRIX_EXIT_POINT_EXCEPTION){}

    ServerWaitedToClientResponseException::ServerWaitedToClientResponseException() noexcept : Exception(STATUS_SERVER_WAITED_TO_CLIENT_RESPONSE_EXCEPTION){}

    InitialStateNotExistException::InitialStateNotExistException() noexcept : Exception(STATUS_INITIAL_STATE_NOT_EXIST_ERROR){}

    GoalStateNotExistException::GoalStateNotExistException() noexcept : Exception(STATUS_GOAL_STATE_NOT_EXIST_ERROR){}

    MatrixNegativeNumberException::MatrixNegativeNumberException() noexcept : Exception(STATUS_NEGATIVE_NUM_IN_MATRIX_EXCEPTION){}

    AlgorithmDoesNotExistException::AlgorithmDoesNotExistException() noexcept : Exception(STATUS_ALGORITHM_DOES_NOT_EXIST_EXCEPTION){}
}




