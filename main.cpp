#include "server.hpp"

int main(){
    /*client_operations::GraphPathHandler clientHandle;
    server_side::ParallelServer server(8086, clientHandle);
    server.open();
*/
    matrix::Matrix matrix(3, 3);
    matrix = matrix::Matrix::getMatrixFromFile("../matrix/matrix2.txt");
    matrix.printMatrix();

    solver_tasks::MatrixGraphPath BFSsearchable(matrix, solver_tasks::PointNode(0, 0, 0, 0), solver_tasks::PointNode(2, 2, 0, 0));
    solver_tasks::MatrixGraphPath DFSsearchable(matrix, solver_tasks::PointNode(0, 0, 0,0 ), solver_tasks::PointNode(2, 2, 0, 0));
    solver_tasks::MatrixGraphPath ASTARsearchable(matrix, solver_tasks::PointNode(0, 0, 0,0), solver_tasks::PointNode(2, 2, 0,0 ));
    solver_tasks::BreadthFirstSearch<solver_tasks::PointNode> BFSsearcher;
    solver_tasks::DepthFirstSearch<solver_tasks::PointNode> DFSsearcher;
    solver_tasks::AStar<solver_tasks::PointNode> ASTARsearcher;
    solver_tasks::Solution<solver_tasks::PointNode> BFSsolution = BFSsearcher.search(BFSsearchable);
    solver_tasks::Solution<solver_tasks::PointNode> DFSsolution = DFSsearcher.search(DFSsearchable);
    solver_tasks::Solution<solver_tasks::PointNode> ASTARsolution = ASTARsearcher.search(ASTARsearchable);
    std::cout << BFSsolution.getSolution() << std::endl;
    std::cout << DFSsolution.getSolution() << std::endl;
    std::cout << ASTARsolution.getSolution() << std::endl;
    




    return 0;
}