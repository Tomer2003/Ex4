#include "server.hpp"

int main(){
    /*client_operations::GraphPathHandler clientHandle;
    server_side::ParallelServer server(8086, clientHandle);
    server.open();
*/
    matrix::Matrix matrix(2, 2);
    matrix = matrix::Matrix::getMatrixFromFile("../matrix/matrix2.txt");
   
    solver_tasks::MatrixGraphPath searchable(matrix, solver_tasks::PointNode(0, 0), solver_tasks::PointNode(2, 2));
    solver_tasks::BreadthFirstSearch<solver_tasks::PointNode> searcher;
    solver_tasks::Solution<solver_tasks::PointNode> solution = searcher.search(searchable);
    std::cout << solution.getSolution() << std::endl;
    




    return 0;
}