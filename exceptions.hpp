#pragma once
#include <iostream>
#include <unistd.h>
#include <errno.h>
#define STATUS_NOT_FOUND_PATH 1
#define STATUS_DEFENITION_PROBLEM_MESSAGE_EXCEPTION 2
#define STATUS_SERVER_WRITE_READ_EXCEPTION 3
#define STATUS_SERVER_BIND_EXCEPTION 4
#define STATUS_SERVER_LISTEN_EXCEPRION 5
#define STATUS_SERVER_OPEN_SOCKET_EXCEPTION 6
#define STATUS_SERVER_ACCEPT_EXCEPTION 7
#define STATUS_MATRIX_SIZES_EXCEPTION 8
#define STATUS_MATRIX_ENTER_POINT_EXCEPTION 9
#define STATUS_MATRIX_EXIT_POINT_EXCEPTION 10
#define STATUS_SERVER_WAITED_TO_CLIENT_RESPONSE_EXCEPTION 11
#define STATUS_INITIAL_STATE_NOT_EXIST_ERROR 12
#define STATUS_GOAL_STATE_NOT_EXIST_ERROR 13
#define STATUS_NEGATIVE_NUM_IN_MATRIX_EXCEPTION 14
#define STATUS_ALGORITHM_DOES_NOT_EXIST_EXCEPTION 15
#define STATUS_MATRIX_NOT_MATCH_TO_SIZE_EXCEPTION 16

namespace exceptions{
    /**
     * @brief The function throw error according status exception
     * 
     * @param returnValue - return value of posix function libary
     * @param status - status of exception
     * @param serverFileDescriptor - server file descriptor
     */
    void serverErrorCheck(const int returnValue, int const status, const int serverFileDescriptor);

    class Exception{
        private:
            unsigned int m_status;
        public:
            /**
             * @brief Construct a new Exception object
             * 
             * @param status - status exception
             */
            Exception(unsigned int status) noexcept;

            unsigned int getStatus() const;
    };

    class MatrixPathNotFound : public Exception{
        public:
            /**
             * @brief Construct a new Matrix Path Not Found object
             * 
             */
            MatrixPathNotFound() noexcept;
    };

    class ServerReadWriteException : public Exception{
        public:
            /**
             * @brief Construct a new Server Read Write Exception object
             * 
             */
            ServerReadWriteException() noexcept;
    };

    class ServerBindException : public Exception{
        public:
            /**
             * @brief Construct a new Server Bind Exception object
             * 
             */
            ServerBindException() noexcept;
    };

    class ServerListenException : public Exception{
        public:
            /**
             * @brief Construct a new Server Listen Exception object
             * 
             */
            ServerListenException() noexcept;
    };

    class ServerOpenSocketException : public Exception{
        public: 
            /**
             * @brief Construct a new Server Open Socket Exception object
             * 
             */
            ServerOpenSocketException() noexcept;
    };

    class ServerAcceptException : public Exception{
        public:
            /**
             * @brief Construct a new Server Accept Exception object
             * 
             */
            ServerAcceptException() noexcept;
    };

    class DefenitionProblemMessageException : public Exception{
        public:
            /**
             * @brief Construct a new Defenition Problem Message Exception object
             * 
             */
            DefenitionProblemMessageException() noexcept;
    };

    class MatrixSizesException : public Exception{
        public:
            /**
             * @brief Construct a new Matrix Sizes Exception object
             * 
             */
            MatrixSizesException() noexcept;
    };

    class MatrixEnterPointException : public Exception{
        public:
            /**
             * @brief Construct a new Matrix Enter Point Exception object
             * 
             */
            MatrixEnterPointException() noexcept;
    };

    class MatrixExitPointException : public Exception{
        public:
            /**
             * @brief Construct a new Matrix Exit Point Exception object
             * 
             */
            MatrixExitPointException() noexcept;
    };
    
    class ServerWaitedToClientResponseException : public Exception{
        public:
            /**
             * @brief Construct a new Server Waited To Client Response Exception object
             * 
             */
            ServerWaitedToClientResponseException() noexcept;
    };

    class MainArgumentsNumException{
        public:
            /**
             * @brief Construct a new Main Arguments Num Exception object
             * 
             */
            MainArgumentsNumException() noexcept{};
    };

    class PortMainArgumentException{
        public:
            /**
             * @brief Construct a new Port Main Argument Exception object
             * 
             */
            PortMainArgumentException() noexcept{};
    };

    class ServerTypeMainArgumentException{
        public:
            /**
             * @brief Construct a new Server Type Main Argument Exception object
             * 
             */
            ServerTypeMainArgumentException() noexcept{};
    };

    class InitialStateNotExistException : public Exception{
        public:
            /**
             * @brief Construct a new Initial State Not Exist Exception object
             * 
             */
            InitialStateNotExistException() noexcept;
    };

    class GoalStateNotExistException : public Exception{
        public:
            /**
             * @brief Construct a new Goal State Not Exist Exception object
             * 
             */
            GoalStateNotExistException() noexcept;
    };

    class MatrixNegativeNumberException : public Exception{
        public:
            /**
             * @brief Construct a new Goal State Not Exist Exception object
             * 
             */
            MatrixNegativeNumberException() noexcept;
    };

    class AlgorithmDoesNotExistException : public Exception{
        public:
           /**
            * @brief Construct a new Algorithm Does Not Exist Exception object
            * 
            */
            AlgorithmDoesNotExistException() noexcept;
    };

    class MatrixNotMatchToSizeException : public Exception{
        public:
           /**
            * @brief Construct a new Algorithm Does Not Exist Exception object
            * 
            */
            MatrixNotMatchToSizeException() noexcept;
    };
}








