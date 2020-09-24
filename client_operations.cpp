#include "client_operations.hpp"
#define BYTES_TO_READ_PER_STREAM 10240
#define MAX_SECONDS_WAITE_FOR_CLIENT_RESPONSE 5
namespace client_operations{

     bool GraphPathHandler::equalsCaseSensetive(const std::string& a, const std::string& b){
       if(a.size() != b.size()){
         return false;
       }
        return std::equal(a.begin(), a.end(), b.begin(),[] (const char& a, const char& b){return (std::tolower(a) == std::tolower(b));});
     }

    solver_tasks::Solution<solver_tasks::PointNode> GraphPathHandler::getFactorAlgorithmSolution(solver_tasks::MatrixGraphPath& searchable, const std::string& algorithm){
      if(equalsCaseSensetive(algorithm, "A*")){
        solver_tasks::AStar<solver_tasks::PointNode> ASTARsearcher;
        return ASTARsearcher.search(searchable);
      }
      if(equalsCaseSensetive(algorithm, "BFS")){
        solver_tasks::BreadthFirstSearch<solver_tasks::PointNode> BFSsearcher;
        return BFSsearcher.search(searchable);
      }
      if(equalsCaseSensetive(algorithm, "DFS")){
        solver_tasks::DepthFirstSearch<solver_tasks::PointNode> DFSsearcher;
        return DFSsearcher.search(searchable);
      }
      throw exceptions::AlgorithmDoesNotExistException();
    }

    void GraphPathHandler::replaceAll(std::string& str, const std::string& from, const std::string& to) {
            if(from.empty())
                return;
            size_t start_pos = 0;
            while((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length(); 
            }
      }

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

    bool GraphPathHandler::isInteger(const std::string& string){
      return string.find_first_not_of("0123456789") == std::string::npos;
    }

    unsigned int GraphPathHandler::getIndexOccurences(std::string string, const char ch, const int occurrence) {
      int index = 0;
      for (int i = 0; i < occurrence; i++) {
        index += string.find(ch) + 1;
        string.erase(0, string.find(ch) + 1);
      }
      return index - 1;
    }

    solver_tasks::PointNode GraphPathHandler::getPointOfPointString(std::string& string, const exceptions::Exception exception){
      if(string.find(",") == std::string::npos){
        throw exception;
      }
      auto row = string.substr(0, string.find(","));
      auto column = string.substr(string.find(",") + 1, string.size() - string.find(",") - 1);
      if(!isInteger(row) || !isInteger(column)){
        throw exception;
      }
      return solver_tasks::PointNode(std::stoi(row), std::stoi(column), 0, 0);
    }

    void GraphPathHandler::handleException(int clientFileDescriptor, const exceptions::Exception& exceptoin) const{
      std::string errorMessage = "Version: 1.0\r\nstatus: " + std::to_string(exceptoin.getStatus()) + "\r\nresponse-length: 0\r\n\r\n";
      write(clientFileDescriptor, (void*)errorMessage.data(), static_cast<unsigned int>(errorMessage.size()));
      close(clientFileDescriptor);
    }
    

    void GraphPathHandler::stopConnection(std::atomic<bool>& clientResponse, std::atomic<bool>& responseMoreThanAvailable, const int clientFileDscriptor) const{
      int miliseconds = 0;
      int a = clientFileDscriptor;
      a++;
      while (!clientResponse && miliseconds < MAX_SECONDS_WAITE_FOR_CLIENT_RESPONSE * 1000)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        miliseconds += 5;
      }
    

      if(miliseconds >= MAX_SECONDS_WAITE_FOR_CLIENT_RESPONSE * 1000 && !clientResponse){
        responseMoreThanAvailable = true;
        handleException(clientFileDscriptor, exceptions::ServerWaitedToClientResponseException());
      }
    }

    std::string GraphPathHandler::defineProblemMessageHandler(const int clientFielDescriptor, const int serverFileDescriptor) const{
      std::string operationDefineMessage(BYTES_TO_READ_PER_STREAM, '\0');

      std::atomic<bool> clientResponse(false);
      std::atomic<bool> responseMoreThanAvailable(false);
      std::thread stopConnectionThread(&GraphPathHandler::stopConnection, this, std::ref(clientResponse), std::ref(responseMoreThanAvailable), clientFielDescriptor);
      exceptions::serverErrorCheck(read(clientFielDescriptor, (void*)operationDefineMessage.data(), BYTES_TO_READ_PER_STREAM), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
      clientResponse.store(true);
      stopConnectionThread.join();
      if(responseMoreThanAvailable){
        return "exit";
      }

      if(operationDefineMessage.find("\r") == std::string::npos){
        throw exceptions::DefenitionProblemMessageException();
      }
      operationDefineMessage =  operationDefineMessage.substr(0, operationDefineMessage.find("\r")) + " " + operationDefineMessage.substr(operationDefineMessage.find("\r"), operationDefineMessage.size() + 1);
      getMessageWithoutMultipleSpaces(operationDefineMessage);
      auto operation = operationDefineMessage.substr(0, operationDefineMessage.find(" "));
      operationDefineMessage.erase(0, operationDefineMessage.find(" ") + 1);
      auto problem = operationDefineMessage.substr(0, operationDefineMessage.find(" "));
      operationDefineMessage.erase(0, operationDefineMessage.find(" ") + 1);
      auto algorithm = operationDefineMessage.substr(0, operationDefineMessage.find(" "));
      operationDefineMessage.erase(0, operationDefineMessage.find("\r\n"));
      
      if(algorithm.size() == 0){
        algorithm = "A*";
      }
     
      if(operationDefineMessage.substr(0, 4) != "\r\n\r\n" || !equalsCaseSensetive(operation, "solve") || !equalsCaseSensetive(problem, "find-graph-path")
      || (!equalsCaseSensetive(algorithm, "A*") && !equalsCaseSensetive(algorithm, "BFS") && !equalsCaseSensetive(algorithm, "DFS"))){
        throw exceptions::DefenitionProblemMessageException();
      }

      std::string succesMessage = "Version: 1.0\r\nstatus: 0\r\nresponse-length: 0\r\n\r\n";
      exceptions::serverErrorCheck(write(clientFielDescriptor, (void*)(succesMessage.data()), static_cast<unsigned int>(succesMessage.size())), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
      return algorithm;
    }

    void GraphPathHandler::dataProblemHandler(const int clientFielDescriptor, const int serverFileDescriptor, const std::string& algorithm) {
      std::string operationDataMessage(BYTES_TO_READ_PER_STREAM, '\0');

      std::atomic<bool> clientResponse(false);
      std::atomic<bool> responseMoreThanAvailable(false);
      std::thread stopConnectionThread(&GraphPathHandler::stopConnection, this, std::ref(clientResponse), std::ref(responseMoreThanAvailable), clientFielDescriptor);
      exceptions::serverErrorCheck(read(clientFielDescriptor, (void*)operationDataMessage.data(), BYTES_TO_READ_PER_STREAM), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
      clientResponse.store(true);
      stopConnectionThread.join();
      if(responseMoreThanAvailable){
        throw exceptions::ServerWaitedToClientResponseException();
      }

      operationDataMessage.erase(std::remove(operationDataMessage.begin(), operationDataMessage.end(), ' '), operationDataMessage.end());
      auto matrixDefenitionSizes = operationDataMessage.substr(0, operationDataMessage.find('\n'));
      operationDataMessage.erase(0, operationDataMessage.find('\n') + 1);
      if(matrixDefenitionSizes.find(",") == std::string::npos){
        exceptions::MatrixSizesException();
      }
      auto height = matrixDefenitionSizes.substr(0, matrixDefenitionSizes.find(","));
      auto width = matrixDefenitionSizes.substr(matrixDefenitionSizes.find(",") + 1, matrixDefenitionSizes.size());
      if(!isInteger(width) || !isInteger(height)){
        exceptions::MatrixSizesException();
      }
      
      std::string matrixString = operationDataMessage.substr(0, getIndexOccurences(operationDataMessage, '\n', std::stoi(height)));
       if(matrixString.find("-") != std::string::npos){
        throw exceptions::MatrixNegativeNumberException();
      }
      replaceAll(matrixString, "b", "-1");

      matrix::Matrix matrix = matrix::Matrix::getMatrixFromString(matrixString);
      if(std::stoi(height) != static_cast<int>(matrix.matrixGetHeight()) || std::stoi(width) != static_cast<int>(matrix.matrixGetWidth())){
        throw exceptions::MatrixSizesException();
      }
      operationDataMessage.erase(0, getIndexOccurences(operationDataMessage, '\n', std::stoi(height)) + 1);

      auto matrixEnterString = operationDataMessage.substr(0, operationDataMessage.find('\r'));
      operationDataMessage.erase(0, operationDataMessage.find('\n') + 1);
      auto enterMatrixPoint = getPointOfPointString(matrixEnterString, exceptions::MatrixEnterPointException());

      auto matrixExitString = operationDataMessage.substr(0, operationDataMessage.find('\r'));
      operationDataMessage.erase(0, operationDataMessage.find('\n') + 1);
      auto exitMatrixPoint = getPointOfPointString(matrixExitString, exceptions::MatrixExitPointException());
     
      std::string solutionMessage;
      if(exitMatrixPoint == enterMatrixPoint){
        std::string solutionPath = "0," + algorithm;
        solutionMessage = "Version: 1.0\r\nstatus: 0\r\nresponse-length: " + std::to_string(solutionPath.size()) + "\r\n" + solutionPath + "\r\n\r\n";
      } else {
        solver_tasks::MatrixGraphPath searchable(matrix, enterMatrixPoint, exitMatrixPoint);

        solver_tasks::Solution<solver_tasks::PointNode> solution = getFactorAlgorithmSolution(searchable, algorithm);

        solutionMessage = "Version: 1.0\r\nstatus: 0\r\nresponse-length: " + std::to_string(solution.getSolution().size()) + "\r\n" + solution.getSolution() + "\r\n\r\n";
      }
      
      exceptions::serverErrorCheck(write(clientFielDescriptor, (void*)solutionMessage.data(), static_cast<unsigned int>(solutionMessage.size())), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
    }

    void GraphPathHandler::handleClient(const int clientFielDescriptor, const int serverFileDescriptor) {
      try{
        std::string algorithm = defineProblemMessageHandler(clientFielDescriptor, serverFileDescriptor);
        if(algorithm != "exit"){
          dataProblemHandler(clientFielDescriptor, serverFileDescriptor, algorithm);
          close(clientFielDescriptor);
        }
      } catch (exceptions::Exception& exception){
        handleException(clientFielDescriptor, exception);
      }
    }
}