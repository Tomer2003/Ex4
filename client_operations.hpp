#include "solver_tasks.hpp"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <mutex>
#include <thread>

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

        /**
         * @brief The function stop client connection if the server waits more than 5 seconds to client message
         * 
         * @param ptrClientSendMessage - if client send message(pointer)
         * @param clientFielDescriptor - client file descriptor
         * @param stopConnection - if should stop connection(waits more than 5 seconds)
         * @param mutex - mutex 
         */
        void stopConnection(bool* ptrClientSendMessage, const int clientFielDescriptor, bool* stopConnection, std::mutex* mutex) const;

        void aaa();

        static void getMessageWithoutMultipleSpaces(std::string& string);
    };

}