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
namespace exceptions{
    void serverErrorCheck(const int returnValue, int const status);

    class Exception{
        private:
            unsigned int m_status;
        public:
            Exception(unsigned int status) noexcept;

            unsigned int getStatus() const;
    };

    class MatrixPathNotFound : public Exception{
        public:
            MatrixPathNotFound() noexcept;
    };

    class ServerReadWriteException : public Exception{
        public:
            ServerReadWriteException() noexcept;
    };

    class ServerBindException : public Exception{
        public:
            ServerBindException() noexcept;
    };

    class ServerListenException : public Exception{
        public:
            ServerListenException() noexcept;
    };

    class ServerOpenSocketException : public Exception{
        public:
            ServerOpenSocketException() noexcept;
    };

    class ServerAcceptException : public Exception{
        public:
            ServerAcceptException() noexcept;
    };

    class DefenitionProblemMessageException : public Exception{
        public:
            DefenitionProblemMessageException() noexcept;
    };

    class MatrixSizesException : public Exception{
        public:
            MatrixSizesException() noexcept;
    };

    class MatrixEnterPointException : public Exception{
        public:
            MatrixEnterPointException() noexcept;
    };

    class MatrixExitPointException : public Exception{
        public:
            MatrixExitPointException() noexcept;
    };
}








