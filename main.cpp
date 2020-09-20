#include "server.hpp"

int main(){
    /*client_operations::GraphPathHandler clientHandle;
    server_side::ParallelServer server(8086, clientHandle);
    server.open();
*/
    matrix::Matrix matrix(2, 2);
    matrix = matrix::Matrix::getMatrixFromFile("../matrix/matrix2.txt");
   
    solver_tasks::MatrixGraphPath BFSsearchable(matrix, solver_tasks::PointNode(0, 0), solver_tasks::PointNode(2, 2));
    solver_tasks::MatrixGraphPath DFSsearchable(matrix, solver_tasks::PointNode(0, 0), solver_tasks::PointNode(2, 2));
    solver_tasks::BreadthFirstSearch<solver_tasks::PointNode> BFSsearcher;
    solver_tasks::DepthFirstSearch<solver_tasks::PointNode> DFSsearcher;
    solver_tasks::Solution<solver_tasks::PointNode> BFSsolution = BFSsearcher.search(BFSsearchable);
    solver_tasks::Solution<solver_tasks::PointNode> DFSsolution = DFSsearcher.search(DFSsearchable);
    std::cout << BFSsolution.getSolution() << std::endl;
    std::cout << DFSsolution.getSolution() << std::endl;
    




    return 0;
}