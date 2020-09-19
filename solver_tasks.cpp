#include "solver_tasks.hpp"


namespace solver_tasks{
    /*Solver::Solver(const Problem& problem, const Solution& solution) noexcept : m_solution(solution), m_problem(problem){};

    const Result& Solver::solve() const{
        return m_problem.solve(m_solution);
    }


    MatrixPathState::MatrixPathState(const unsigned int row, const unsigned int column) noexcept : m_row(row), m_column(column){};


    bool MatrixPathState::equals(const MatrixPathState& matrixPathState) const{
        return m_row == matrixPathState.m_row && m_column == matrixPathState.m_column;
    }
*/
    PointNode::PointNode(const unsigned int row, const unsigned int column) noexcept : m_row(row), m_column(column){};

    bool PointNode::operator==(const PointNode& pointNode) const{
        return m_row == pointNode.m_row && m_column == pointNode.m_column;
    }

}