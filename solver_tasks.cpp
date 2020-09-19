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

    MatrixGraphPath::MatrixGraphPath(const matrix::Matrix& matrixGraph, const PointNode& initialNode, const PointNode& goalNdoe) noexcept : m_matrixGraph(matrixGraph), m_initialNode(initialNode), m_goalNode(goalNdoe){};

    State<PointNode> MatrixGraphPath::getInitialState() const{
        return State<PointNode>(m_initialNode, m_matrixGraph(m_initialNode.getRow(), m_initialNode.getColumn()));
    }

    bool MatrixGraphPath::isGoalState(const State<PointNode>& state) const{
        return state.getNode() == m_goalNode;
    }

    std::vector<State<PointNode>> MatrixGraphPath::getAllPossibleStates(const State<PointNode>& state) const{
        std::vector<State<PointNode>> possibleStates;

        if(state.getNode().getRow() + 1 <= m_matrixGraph.matrixGetWidth() - 1){
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow() + 1, state.getNode().getColumn()),
             m_matrixGraph(state.getNode().getRow() + 1, state.getNode().getColumn())));
        }

        if(state.getNode().getRow() - 1 >= 0) {
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow() - 1, state.getNode().getColumn()),
            m_matrixGraph(state.getNode().getRow() - 1, state.getNode().getColumn())));
        }

        if(state.getNode().getColumn() + 1 <= m_matrixGraph.matrixGetHeight() - 1){
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow(), state.getNode().getColumn() + 1),
             m_matrixGraph(state.getNode().getRow(), state.getNode().getColumn() + 1)));
        }

        if(state.getNode().getColumn() - 1 >= 0){
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow(), state.getNode().getColumn() - 1),
            m_matrixGraph(state.getNode().getRow(), state.getNode().getColumn() - 1)));
        }

        return possibleStates;
    }
}