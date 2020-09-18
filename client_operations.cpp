#include "client_operations.hpp"

namespace client_operations{

  

    void ClientHandleTester::handleClient(const int clientFielDescriptor, const int serverFielDescriptor) const{
      std::string b(1024, '\0');
      read(clientFielDescriptor, (void*)(b.data()), 1024);
      std::cout << b;
    }






}