#include "server.hpp"
int main(int argc, char** argv){
    if(argc > 3 || argc < 1){
        throw exceptions::MainArgumentsNumException();
    }
    if(!client_operations::GraphPathHandler::isInteger(std::string(argv[1]))){
        throw exceptions::PortMainArgumentException();
    }
    if(argc == 3 && !client_operations::GraphPathHandler::equalsCaseSensetive(std::string(argv[2]), "parallel")){
        throw exceptions::ServerTypeMainArgumentException();
    }
    client_operations::GraphPathHandler clientHandle;
    server_side::ParallelServer server(std::stoi(std::string(argv[1])), clientHandle);
    server.open();




    return 0;
}