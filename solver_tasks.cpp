#include "solver_tasks.hpp"
#define NO_PASSAGE_NODE -1

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
    PointNode::PointNode(const unsigned int row, const unsigned int column) noexcept : m_row(row), m_column(column){}

    bool PointNode::operator==(const PointNode& pointNode) const{
        return m_row == pointNode.m_row && m_column == pointNode.m_column;
    }

    std::string PointNode::operator>>(const PointNode& pointNode) const{
        if(m_row == pointNode.getRow() && m_column + 1 == pointNode.getColumn()){
            return "Right";
        }
        if(m_row == pointNode.getRow() && m_column - 1 == pointNode.getColumn()){
            return "Left";
        }
        if(m_row + 1 == pointNode.getRow() && m_column == pointNode.getColumn()){
            return "Down";
        }
        if(m_row - 1 == pointNode.getRow() && m_column == pointNode.getColumn()){
            return "Up";
        }
        return "Error: can not reach with one direction";
    }

    unsigned int PointNode::getRow() const{
        return m_row;
    }

    unsigned int PointNode::getColumn() const{
        return m_column;
    }

    MatrixGraphPath::MatrixGraphPath(const matrix::Matrix& matrixGraph, const PointNode& initialNode, const PointNode& goalNdoe) noexcept : m_matrixGraph(matrixGraph), m_initialNode(initialNode), m_goalNode(goalNdoe){
        setStatesOfMatrix();
    }

    State<PointNode>& MatrixGraphPath::getInitialState(){
        for(State<PointNode>& state : getStatesVector()){
            if(state.getNode() == m_initialNode){
                return state;
            }
        }
        //throw exception(no initial state)
        std::cout << "error!" << std::endl;
        exit(1);
    }

     State<PointNode>& MatrixGraphPath::getGoalState(){
          for(State<PointNode>& state : getStatesVector()){
            if(state.getNode() == m_goalNode){
                return state;
            }
        }
        //throw exception(no initial state)
        std::cout << "error!" << std::endl;
        exit(1);
    }

    void MatrixGraphPath::setStatesOfMatrix(){
        for(unsigned int row = 0; row < m_matrixGraph.matrixGetWidth(); ++row){
            for(unsigned int column = 0; column < m_matrixGraph.matrixGetWidth(); ++column){
                if(m_matrixGraph(row, column) != NO_PASSAGE_NODE){
                    getStatesVector().push_back(State<PointNode>(PointNode(row, column), m_matrixGraph(row, column)));
                }
            }
        }
    }

   /* template <class Node> bool compareCost(State<Node> state1, State<Node> state2){
        return (state1.getCost() < state2.getCost());
    }*/

    std::vector<State<PointNode>*> MatrixGraphPath::getAllPossibleStates(const State<PointNode>& state){
        std::vector<State<PointNode>*> possibleStates;
        for(State<PointNode>& matrixState : getStatesVector()){
            if((state.getNode().getRow() + 1 == matrixState.getNode().getRow() && state.getNode().getColumn() == matrixState.getNode().getColumn())
            || (state.getNode().getRow() - 1 == matrixState.getNode().getRow() && state.getNode().getColumn() == matrixState.getNode().getColumn())
            || (state.getNode().getRow() == matrixState.getNode().getRow() && state.getNode().getColumn() + 1 == matrixState.getNode().getColumn())
            || (state.getNode().getRow() == matrixState.getNode().getRow() && state.getNode().getColumn() - 1 == matrixState.getNode().getColumn())){
                possibleStates.push_back(&matrixState);
            }
        }

        std::sort(possibleStates.begin(), possibleStates.end(), State<PointNode>::compareCost);

       // std::sort(possibleStates.begin(), possibleStates.end(), compareCost<PointNode>);
/*
        if(state.getNode().getRow() + 1 <= m_matrixGraph.matrixGetWidth() - 1 && m_matrixGraph(state.getNode().getRow() + 1, state.getNode().getColumn()) != NO_PASSAGE_NODE){
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow() + 1, state.getNode().getColumn()),
            m_matrixGraph(state.getNode().getRow() + 1, state.getNode().getColumn())));
            getStatesVector().push_back(possibleStates.front());
        }

        if(state.getNode().getRow()  >= 1 && m_matrixGraph(state.getNode().getRow() - 1, state.getNode().getColumn()) != NO_PASSAGE_NODE) {
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow() - 1, state.getNode().getColumn()),
            m_matrixGraph(state.getNode().getRow() - 1, state.getNode().getColumn())));
            getStatesVector().push_back(possibleStates.front());
        }

        if(state.getNode().getColumn() + 1 <= m_matrixGraph.matrixGetHeight() - 1 && m_matrixGraph(state.getNode().getRow(), state.getNode().getColumn() + 1) != NO_PASSAGE_NODE){
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow(), state.getNode().getColumn() + 1),
            m_matrixGraph(state.getNode().getRow(), state.getNode().getColumn() + 1)));
            getStatesVector().push_back(possibleStates.front());
        }

        if(state.getNode().getColumn()  >= 1 && m_matrixGraph(state.getNode().getRow(), state.getNode().getColumn() - 1) != NO_PASSAGE_NODE){
            possibleStates.push_back(State<PointNode>(PointNode(state.getNode().getRow(), state.getNode().getColumn() - 1),
            m_matrixGraph(state.getNode().getRow(), state.getNode().getColumn() - 1)));
            getStatesVector().push_back(possibleStates.front());
        }
*/
        return possibleStates;
    }
}