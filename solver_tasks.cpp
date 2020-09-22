#include "solver_tasks.hpp"
#define NO_PASSAGE_NODE -1

namespace solver_tasks{
    PointNode::PointNode(const unsigned int row, const unsigned int column, const  double yCoordinate, const  double xCoordinate) noexcept : m_row(row), m_column(column), m_xCoordinate(xCoordinate), m_yCoordinate(yCoordinate){}

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

    double PointNode::getYCoordinate() const{
        return m_yCoordinate;
    }

    double PointNode::getXCoordinate() const{
        return m_xCoordinate;
    }

    void PointNode::setXCoordinate(const double xCoordinate){
        m_xCoordinate = xCoordinate;
    }

    void PointNode::setYCoordinate(const double yCoordinate){
        m_yCoordinate = yCoordinate;
    }

    MatrixGraphPath::MatrixGraphPath(const matrix::Matrix& matrixGraph, const PointNode& initialNode, const PointNode& goalNdoe) noexcept : m_matrixGraph(matrixGraph), m_initialNode(initialNode), m_goalNode(goalNdoe){
        setStatesOfMatrix();
        setDistanceForStatesToGoalState();
    }

    State<PointNode>& MatrixGraphPath::getInitialState(){
        for(State<PointNode>& state : getStatesVector()){
            if(state.getNode() == m_initialNode){
                return state;
            }
        }
        //throw exception(no initial state)
        std::cout << "error!a" << std::endl;
        exit(1);
    }

     State<PointNode>& MatrixGraphPath::getGoalState(){
          for(State<PointNode>& state : getStatesVector()){
            if(state.getNode() == m_goalNode){
                return state;
            }
        }
        //throw exception(no initial state)
        std::cout << "error!b" << std::endl;
        exit(1);
    }

    State<PointNode>& MatrixGraphPath::getState(const unsigned int row, const unsigned int column){
        for(State<PointNode>& state : getStatesVector()){
            if(state.getNode().getRow() == row && state.getNode().getColumn() == column){
                return state;
            }
        }
        throw NO_PASSAGE_NODE;
    }


    double MatrixGraphPath::getYCoordinateOfUpperNode(const unsigned int row, const unsigned int column){
        bool exception = true;
        double yCoordinateUpperNode;
        unsigned int upper = 1;
        while(exception){
            try{
                if(static_cast<int>(row - upper) <  0){
                    yCoordinateUpperNode = 0;
                    exception = false;
                } else{
                    yCoordinateUpperNode = getState(row - upper, column).getNode().getYCoordinate();
                    exception = false;
                }
            } catch(int noPassageNode){
                upper++;
            }
        }
        return yCoordinateUpperNode;
    }

    double MatrixGraphPath::getXCoordinateOfLeffterNode(const unsigned int row, const unsigned int column){
        bool exception = true;
        double xCoordinateRightNode;
        unsigned int lefter = 1;
        while(exception){
            try{
                if(static_cast<int>(column - lefter) < 0){
                    xCoordinateRightNode = 0;
                    exception = false;
                } else{
                    State<PointNode>& state = getState(row, column - 1);
                    xCoordinateRightNode = state.getNode().getXCoordinate();
                    exception = false;
                }
            } catch(int noPassageNode){
                lefter++;
            }
        }
        return xCoordinateRightNode;
    }

    void MatrixGraphPath::setStatesOfMatrix(){
        for(unsigned int row = 0; row < m_matrixGraph.matrixGetWidth(); ++row){
            for(unsigned int column = 0; column < m_matrixGraph.matrixGetWidth(); ++column){
                if(m_matrixGraph(row, column) != NO_PASSAGE_NODE){
                    if(column == 0 && row == 0){
                        getStatesVector().push_back(State<PointNode>(PointNode(row, column, 0, 0), m_matrixGraph(row, column)));
                    }
                    else if(column == 0){
                        getStatesVector().push_back(State<PointNode>(PointNode(row, column, m_matrixGraph(row, column) + getYCoordinateOfUpperNode(row, column), 0), m_matrixGraph(row, column)));
                    }
                    else{
                        getStatesVector().push_back(State<PointNode>(PointNode(row, column, getYCoordinateOfUpperNode(row, column), m_matrixGraph(row, column) + getXCoordinateOfLeffterNode(row, column)), m_matrixGraph(row, column)));
                    }
                }
            }
        }
    }

    void MatrixGraphPath::setDistanceForStatesToGoalState(){
        for(State<PointNode>& state : getStatesVector()){
            state.setDistanceToGoalState(std::sqrt(std::pow(state.getNode().getXCoordinate() - getGoalState().getNode().getXCoordinate(), 2) + std::pow(state.getNode().getYCoordinate() - getGoalState().getNode().getYCoordinate(), 2)));
        }
    }

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
        return possibleStates;
    }
}