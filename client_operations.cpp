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

    bool isInteger(const std::string& string){
      return string.find_first_not_of("0123456789") == std::string::npos;
    }

    void GraphPathHandler::handleException(int clientFileDescriptor, exceptions::Exception& exceptoin) const{
      std::string errorMessage = "Version: 1.0\r\nstatus: " + std::to_string(exceptoin.getStatus()) + "\r\nresponse-length: 0\r\n\r\n";
      write(clientFileDescriptor, (void*)errorMessage.data(), static_cast<unsigned int>(errorMessage.size()));
      close(clientFileDescriptor);
    }

    void GraphPathHandler::defineProblemMessageHandler(const int clientFielDescriptor, const int serverFileDescriptor) const{
      int a = serverFileDescriptor;
      a++;//delete
      std::string operationDefineMessage(BYTES_TO_READ_PER_STREAM, '\0');
      exceptions::serverErrorCheck(read(clientFielDescriptor, (void*)operationDefineMessage.data(), BYTES_TO_READ_PER_STREAM), STATUS_SERVER_WRITE_READ_EXCEPTION);
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
      
      if(operationDefineMessage.substr(0, 4) != "\r\n\r\n" || operation != "solve" || problem != "find-graph-path"
      || (algorithm != "A*" && algorithm != "BFS" && algorithm != "DFS")){
        throw exceptions::DefenitionProblemMessageException();
        
      }

      std::string succesMessage = "Version: 1.0\r\nstatus: 0\r\nresponse-length: 0\r\n\r\n";
      exceptions::serverErrorCheck(write(clientFielDescriptor, (void*)(succesMessage.data()), static_cast<unsigned int>(succesMessage.size())), STATUS_SERVER_WRITE_READ_EXCEPTION);
    
    }

    void GraphPathHandler::dataProblemHandler(const int clientFielDescriptor, const int serverFileDescriptor) const{
      int a = serverFileDescriptor;
      a++;//delete
      std::string operationDataMessage(BYTES_TO_READ_PER_STREAM, '\0');
      exceptions::serverErrorCheck(read(clientFielDescriptor, (void*)operationDataMessage.data(), BYTES_TO_READ_PER_STREAM), STATUS_SERVER_WRITE_READ_EXCEPTION);
      operationDataMessage.erase(std::remove(operationDataMessage.begin(), operationDataMessage.end(), ' '), operationDataMessage.end());
      auto matrixDefenitionSizes = operationDataMessage.substr(0, operationDataMessage.find('\n'));
      matrixDefenitionSizes.erase(0, matrixDefenitionSizes.find('\n') + 1);
      if(matrixDefenitionSizes.find(",") == std::string::npos){
        //trow exception!
      }
      auto height = matrixDefenitionSizes.substr(0, matrixDefenitionSizes.find(","));
      auto width = matrixDefenitionSizes.substr(matrixDefenitionSizes.find(",") + 1, matrixDefenitionSizes.size());
      if(!isInteger(width) || !isInteger(height)){
        //throw exception!
      }
      matrix::Matrix matrix(std::stoi(height), std::stoi(width));


    }

    void GraphPathHandler::handleClient(const int clientFielDescriptor, const int serverFileDescriptor) const{
      try{
        defineProblemMessageHandler(clientFielDescriptor, serverFileDescriptor);
        close(clientFielDescriptor);
      } catch (exceptions::Exception& exception){
        handleException(clientFielDescriptor, exception);
      }

    }





}