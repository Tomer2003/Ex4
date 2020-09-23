#include "client_operations.hpp"
#define BYTES_TO_READ_PER_STREAM 10240
#define MAX_WAITE_FOR_CLIENT_RESPONSE 5 
namespace client_operations{

    bool GraphPathHandler::equalsCaseSensetive(const std::string& a, const std::string& b){
        return std::equal(a.begin(), a.end(), b.begin(),[](char a, char b) {return tolower(a) == tolower(b);});
    }

    solver_tasks::Solution<solver_tasks::PointNode> GraphPathHandler::getFactorAlgorithmSolution(solver_tasks::MatrixGraphPath& searchable, const std::string& algorithm){
      if(algorithm == "A*"){
        solver_tasks::AStar<solver_tasks::PointNode> ASTARsearcher;
        return ASTARsearcher.search(searchable);
      }
      if(algorithm == "BFS"){
        solver_tasks::BreadthFirstSearch<solver_tasks::PointNode> BFSsearcher;
        return BFSsearcher.search(searchable);
      }
      solver_tasks::DepthFirstSearch<solver_tasks::PointNode> DFSsearcher;
      return DFSsearcher.search(searchable);
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

    void GraphPathHandler::handleException(int clientFileDescriptor, exceptions::Exception& exceptoin) const{
      std::string errorMessage = "Version: 1.0\r\nstatus: " + std::to_string(exceptoin.getStatus()) + "\r\nresponse-length: 0\r\n\r\n";
      write(clientFileDescriptor, (void*)errorMessage.data(), static_cast<unsigned int>(errorMessage.size()));
      close(clientFileDescriptor);
    }


    void GraphPathHandler::stopConnection(std::atomic<bool>& clientResponse, const int clientFielDescriptor) const{
      std::this_thread::sleep_for(std::chrono::seconds(MAX_WAITE_FOR_CLIENT_RESPONSE));

      if(!clientResponse.load()){
        close(clientFielDescriptor);
        throw exceptions::ServerWaitedToClientResponseException();
      }
    }

    std::string GraphPathHandler::defineProblemMessageHandler(const int clientFielDescriptor, const int serverFileDescriptor) const{
      std::string operationDefineMessage(BYTES_TO_READ_PER_STREAM, '\0');
      //std::atomic<bool> clientResponse(false);
     
     // std::thread stopConnectionThread(&GraphPathHandler::stopConnection, this, std::ref(clientResponse), clientFielDescriptor);
      exceptions::serverErrorCheck(read(clientFielDescriptor, (void*)operationDefineMessage.data(), BYTES_TO_READ_PER_STREAM), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
      for(unsigned int i = 0; i < operationDefineMessage.size(); i++){
        printf("%d ", operationDefineMessage.data()[i]);
      }
      //clientResponse.store(true);
      std::cout << operationDefineMessage << std::endl;
      getMessageWithoutMultipleSpaces(operationDefineMessage);
      auto operation = operationDefineMessage.substr(0, operationDefineMessage.find(" "));
      operationDefineMessage.erase(0, operationDefineMessage.find(" ") + 1);
      auto problem = operationDefineMessage.substr(0, operationDefineMessage.find(" "));
      operationDefineMessage.erase(0, operationDefineMessage.find(" ") + 1);
      auto algorithm = operationDefineMessage.substr(0, operationDefineMessage.find("\r\n"));
      operationDefineMessage.erase(0, operationDefineMessage.find("\r\n"));
      

      if(operationDefineMessage.substr(0, 4) != "\r\n\r\n" || !equalsCaseSensetive(operation, "solve") || !equalsCaseSensetive(problem, "find-graph-path")
      || (!equalsCaseSensetive(algorithm, "A*") && !equalsCaseSensetive(algorithm, "BFS") && !equalsCaseSensetive(algorithm, "DFS"))){
        throw exceptions::DefenitionProblemMessageException();
        
      }

      std::string succesMessage = "Version: 1.0\r\nstatus: 0\r\nresponse-length: 0\r\n\r\n";
      
      exceptions::serverErrorCheck(write(clientFielDescriptor, (void*)(succesMessage.data()), static_cast<unsigned int>(succesMessage.size())), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
  
      //stopConnectionThread.join();
      return algorithm;
    }

    void GraphPathHandler::dataProblemHandler(const int clientFielDescriptor, const int serverFileDescriptor, const std::string& algorithm) {
      std::string operationDataMessage(BYTES_TO_READ_PER_STREAM, '\0');
      //std::atomic<bool> clientResponse(false);

     // std::thread stopConnectionThread(&GraphPathHandler::stopConnection, this, std::ref(clientResponse), clientFielDescriptor);
      exceptions::serverErrorCheck(read(clientFielDescriptor, (void*)operationDataMessage.data(), BYTES_TO_READ_PER_STREAM), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
     // clientResponse.store(true);
      
      for(unsigned int i = 0; i < operationDataMessage.size(); i++){
        printf("%d ", operationDataMessage.data()[i]);
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
      
      matrix::Matrix matrix(std::stoi(height), std::stoi(width));

      std::string matrixString = operationDataMessage.substr(0, getIndexOccurences(operationDataMessage, '\n', std::stoi(height)));
      replaceAll(matrixString, "b", "-1");
      matrix = matrix::Matrix::getMatrixFromString(matrixString);

      operationDataMessage.erase(0, getIndexOccurences(operationDataMessage, '\n', std::stoi(height)) + 1);

      auto matrixEnter = operationDataMessage.substr(0, operationDataMessage.find('\n'));
      operationDataMessage.erase(0, operationDataMessage.find('\n') + 1);
      if(matrixDefenitionSizes.find(",") == std::string::npos){
        exceptions::MatrixEnterPointException();
      }
      auto rowCoordinateEnter = matrixEnter.substr(0, matrixEnter.find(","));
      auto columnCoordinateEnter = matrixEnter.substr(matrixEnter.find(",") + 1, matrixEnter.size());
      if(!isInteger(width) || !isInteger(height)){
        exceptions::MatrixEnterPointException();
      }
      auto enterMatrixPoint = solver_tasks::PointNode(std::stoi(rowCoordinateEnter), std::stoi(columnCoordinateEnter), 0, 0);

      auto matrixExit = operationDataMessage.substr(0, operationDataMessage.find('\n'));
      operationDataMessage.erase(0, operationDataMessage.find('\n') + 1);
      if(matrixDefenitionSizes.find(",") == std::string::npos){
        exceptions::MatrixExitPointException();
      }
      auto rowCoordinateExit = matrixExit.substr(0, matrixExit.find(","));
      auto columnCoordinateExit = matrixExit.substr(matrixExit.find(",") + 1, matrixExit.size());
      if(!isInteger(width) || !isInteger(height)){
        exceptions::MatrixExitPointException();
      }
      auto exitMatrixPoint = solver_tasks::PointNode(std::stoi(rowCoordinateExit), std::stoi(columnCoordinateExit), 0, 0);

      solver_tasks::MatrixGraphPath searchable(matrix, enterMatrixPoint, exitMatrixPoint);

      solver_tasks::Solution<solver_tasks::PointNode> solution = getFactorAlgorithmSolution(searchable, algorithm);

      std::string solutionMessage = "Version: 1.0\r\nstatus: 0\r\nresponse-length: " + std::to_string(solution.getSolution().size()) + "\r\n" + solution.getSolution() + "\r\n\r\n";

      exceptions::serverErrorCheck(write(clientFielDescriptor, (void*)solutionMessage.data(), static_cast<unsigned int>(solutionMessage.size())), STATUS_SERVER_WRITE_READ_EXCEPTION, serverFileDescriptor);
    }

    void GraphPathHandler::handleClient(const int clientFielDescriptor, const int serverFileDescriptor) {
      try{
        std::string algorithm = defineProblemMessageHandler(clientFielDescriptor, serverFileDescriptor);
        dataProblemHandler(clientFielDescriptor, serverFileDescriptor, algorithm);
        close(clientFielDescriptor);
      } catch (exceptions::Exception& exception){
        handleException(clientFielDescriptor, exception);
      }

    }





}