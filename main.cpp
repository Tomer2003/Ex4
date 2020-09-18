#include "server.hpp"


int main(){
    client_operations::ClientHandleTester clientHandle;
    server_side::ParallelServer server(8086, clientHandle);
    server.open();





    return 0;
}