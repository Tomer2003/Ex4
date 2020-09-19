#include "solver_tasks.hpp"
#include <iostream>
#include <algorithm>
#include <unistd.h>
namespace client_operations{
    class ClientHandler{
    public:
       

        virtual void handleClient(const int clientFielDescriptor) const = 0;

    };

    class GraphPathHandler : public ClientHandler{
    private:

    public:

        void handleClient(const int clientFielDescriptor) const;   

      /*  static solver_tasks::Solution algorithmFactory(const std::string& algorithm){
            if(algorithm == "DFS"){

            }
            if(algorithm == "BestFS"){

            }
            if(algorithm == "A*"){

            }
            if(algorithm == ""){

            }
            //throw exception!
            return ;
        }*/

        static void getMessageWithoutMultipleSpaces(std::string& string);
    };

}