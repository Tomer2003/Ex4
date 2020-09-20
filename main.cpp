#include "server.hpp"

int main(){
    /*client_operations::GraphPathHandler clientHandle;
    server_side::ParallelServer server(8086, clientHandle);
    server.open();
*/
    matrix::Matrix matrix(3, 3);
    matrix = matrix::Matrix::getMatrixFromFile("../matrix/matrix2.txt");
    //matrix.printMatrix();

    solver_tasks::MatrixGraphPath searchable(matrix, solver_tasks::PointNode(0, 0), solver_tasks::PointNode(2, 2));
    solver_tasks::BreadthFirstSearch<solver_tasks::PointNode> searcher;
    solver_tasks::Solution<solver_tasks::PointNode> solution = searcher.search(searchable);
    //std::cout << solution.getSolution().size() << std::endl;
    




    return 0;
}