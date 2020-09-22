#include "client_operations.hpp"
#define BYTES_TO_READ_PER_STREAM 10240
namespace client_operations{

    
  /*  void GraphPathHandler::stopConnection(bool* ptrClientSendMessage, const int clientFielDescriptor, bool* stopConnection, std::mutex* mutex) const{
      std::this_thread::sleep_for(std::chrono::seconds(5));
      mutex->lock();
      if(!*ptrClientSendMessage){
        close(clientFielDescriptor);
        *stopConnection = true;
      }
      mutex->unlock();
    }
*/
    void GraphPathHandler::getMessageWithoutMultipleSpaces(std::string& string){
      std::replace(string.begin(), string.end(), '\t', ' ');
    	std::string::iterator new_end =
		  std::unique(string.begin(), string.end(), [=](char lhs, char rhs) { return (lhs ==  rhs) && (lhs == ' '); }
	    );
	    string.erase(new_end, string.end());
      if(string.at(0) == ' '){
        string.erase(0, 1);
      }
    }
    
    void GraphPathHandler::handleClient(const int clientFielDescriptor, const int serverFileDescriptor) const{
      std::string operationDefineMessage(BYTES_TO_READ_PER_STREAM, '\0');
      exceptions::serverErrorCheck(read(clientFielDescriptor, (void*)operationDefineMessage.data(), BYTES_TO_READ_PER_STREAM), serverFileDescriptor);
    /*  //check if the server waits more than 5 seconds to client message
      bool clientSendMessage = false;
      bool stopClientConnection = false;
      std::mutex mutex;
      std::thread thread(&GraphPathHandler::stopConnection, this, &clientSendMessage, clientFielDescriptor, &stopClientConnection, &mutex);
      read(clientFielDescriptor, (void*)operationDefineMessage.data(), BYTES_TO_READ_PER_STREAM);
      mutex.lock();
      clientSendMessage = true;
      //shoud to awake here the sleeper thread
      //thread.join();
      if(stopClientConnection){
        return;
      }
      mutex.unlock();
*/

      getMessageWithoutMultipleSpaces(operationDefineMessage);
      auto operation = operationDefineMessage.substr(0, operationDefineMessage.find(" "));
      operationDefineMessage.erase(0, operationDefineMessage.find(" ") + 1);
      auto problem = operationDefineMessage.substr(0, operationDefineMessage.find(" "));
      operationDefineMessage.erase(0, operationDefineMessage.find(" ") + 1);
      auto algorithm = operationDefineMessage.substr(0, operationDefineMessage.find("\r\n"));
      operationDefineMessage.erase(0, operationDefineMessage.find("\r\n"));
      
      if(operationDefineMessage.substr(0, 4) != "\r\n\r\n" || operation != "solve" || problem != "find-graph-path"){
        close(clientFielDescriptor);
        std::cout << "error!: " << operation << " " << problem << " " << algorithm << std::endl;
        //throw exception!
      }

      std::cout << operation << " " << problem << " " << algorithm << std::endl;      
      close(clientFielDescriptor);
      

    }





}