#include <iostream>
#include <unistd.h>
namespace client_operations{
    class ClientHandler{
    public:
       

        virtual void handleClient(const int clientFielDescriptor, const int serverFielDescriptor) const = 0;

    };

    class ClientHandleTester : public ClientHandler{
    public:
        

        void handleClient(const int clientFielDescriptor, const int serverFielDescriptor) const;   
    };

};