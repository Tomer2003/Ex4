#include <iostream>

namespace client_operations{
    class ClientHandler{
    public:
        virtual void handleClient(const std::istream inputStream, const std::ostream outputSream) const = 0;

    };

    class ClientHandleTester : public ClientHandler{
    public:
        virtual void handleClient(const std::istream inputStream, const std::ostream outputSream) const;   
    };

};