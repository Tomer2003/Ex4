#include "server.hpp"


int main(){
    client_operations::GraphPathHandler clientHandle;
    server_side::ParallelServer server(8086, clientHandle);
    server.open();





    return 0;
}