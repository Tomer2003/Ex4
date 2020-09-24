#pragma once

#include "matrix/ClassMatrix.hpp"
#include "exceptions.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>


namespace solver_tasks{

template <class Node> class State{
private:    
    Node m_node;
    double m_cost;
    bool m_visited;
    State<Node>* m_ptrCameFrom;
    double m_distanceToGoalState;

public:
    /**
     * @brief Construct a new State object.
     * 
     * @param node - node of state.
     * @param cost - cost of state.
     */
    State(const Node& node, const double cost) noexcept : m_node(node), m_cost(cost), m_visited(false), m_ptrCameFrom(nullptr), m_distanceToGoalState(0){};

    /**
     * @brief The function return node.
     * 
     * @return Node - node of state.
     */
    Node getNode() const{
        return m_node;
    }

    bool hasPreviousState() const{
        return m_ptrCameFrom != nullptr;
    }

    /**
     * @brief The function return if state visited.
     * 
     * @return true - state visites.
     * @return false - state does not visites.
     */
    bool getVisited() const{
        return m_visited;
    }

    /**
     * @brief The function return the previous state that came from.
     * 
     * @return State<Node> - previous state that came from.
     */
    State<Node> getCameFromState() const{
        return *m_ptrCameFrom;
    }

    /**
     * @brief The function comapre cost between two states
     * 
     * @param ptrState1 - pointer to first state
     * @param ptrState2 - pointer to second state
     * @return true - first cost state bigger than secind cost state
     * @return false - first cost state smaller than secind cost state
     */
    static bool compareCost(State<Node>* ptrState1, State<Node>* ptrState2){
        return (ptrState1->getCost() < ptrState2->getCost());
    }

   /**
     * @brief The function comapre cost between two states
     * 
     * @param state - state to compare
     * @return true - first cost state bigger than secind cost state
     * @return false - first cost state smaller than secind cost state
     */
  /*  bool operator<(const State<Node>& state) const{
        return state.m_cost < m_cost;
    }
*/
    /**
     * @brief The function set distance to goal state from current state
     * 
     * @return unsigned double - distance to goal state from current state
     */
    void setDistanceToGoalState(double distanceToGoalState){
        m_distanceToGoalState = distanceToGoalState;
    }

    /**
     * @brief The function return distance to goal state from current state
     * 
     * @return unsigned double - distance to goal state from current state
     */
    double getDistanceToGoalState() const{
        return m_distanceToGoalState;
    }

    /**
     * @brief The function retun cost of state.
     * 
     * @return unsigned double - cost of state.
     */
    double getCost() const{
        return m_cost;
    }

    /**
     * @brief The function set visited value.
     * 
     * @param visited - new visited value.
     */
    void setVisited(const bool& visited){
        m_visited = visited;
    }

    /**
     * @brief The function set previous state that came from.
     * 
     * @param state - previous state that came from.
     */
    void setPrevState(const State<Node>& state){
        m_ptrCameFrom = (State<Node>*)(&state);
    }

    /**
     * @brief The function return the step to do to reach to another state(if its only one step).
     * 
     * @param state - step to reach.
     * @return std::string - Up/Down/Right/Left.
     */
    std::string operator>>(const State<Node>& state) const{
        return m_node >> state.getNode();
    }


};

class PointNode{
private:
    unsigned int m_row;
    unsigned int m_column;
    double m_xCoordinate;
    double m_yCoordinate;


public:
    /**
     * @brief Construct a new Point Node object
     * 
     * @param row - row of matrix point. 
     * @param column - column of matrix point.
     */
    PointNode(const unsigned int row, const unsigned int column, const double yCoordinate, const double xCoordinate) noexcept;

    /**
     * @brief The function checks if two points are equal.
     * 
     * @param pointNode - check if equal.
     * @return true - equal.
     * @return false - not equal.
     */
    bool operator==(const PointNode& pointNode) const;

     /**
     * @brief The function return the step to do to reach to another state(if its only one step).
     * 
     * @param pointNode - matrix point to reach.
     * @return std::string - Up/Down/Right/Left.
     */
    std::string operator>>(const PointNode& pointNode) const;

    /**
     * @brief The function return the row of point.
     * 
     * @return unsigned int - row of point.
     */
    unsigned int getRow() const;

    /**
     * @brief The function return column of point.
     * 
     * @return unsigned int - column of point.
     */
    unsigned int getColumn() const;

    /**
     * @brief The function return y coordinate
     * 
     * @return unsigned double - y coordinate
     */
    double getYCoordinate() const;

    /**
     * @brief The function return x coordinate
     * 
     * @return unsigned double - x coordinate
     */
    double getXCoordinate() const;

    /**
     * @brief The function set x coordinate 
     * 
     * @param xCoordinate - x coordinate 
     */
    void setXCoordinate(const double xCoordinate);

    /**
     * @brief The function set y coordinate
     * 
     * @param yCoordinate - y coordinate 
     */
    void setYCoordinate(const double yCoordinate);
};


template <class Node> class Searchable{
private:
    std::vector<State<PointNode>> m_states;

public:
    /**
     * @brief The function return initial state
     * 
     * @return State<Node> - initial state
     */
    virtual State<Node>& getInitialState() = 0;

    /**
     * @brief The function return goal state
     * 
     * @return State<Node> - goal state 
     */
    virtual State<Node>& getGoalState() = 0;

    /**
     * @brief The function return all possible states to reach from current state
     * 
     * @param state - current state
     * @return std::vector<State<Node>> - vector of all possible states to reach from current state
     */
    virtual std::vector<State<Node>*> getAllPossibleStates(const State<Node>& state) = 0;

    /**
     * @brief The function return states. 
     * 
     * @return std::vector<State<Ndoe>> - states of problem.
     */
    std::vector<State<Node>>& getStatesVector(){
        return m_states;
    } 

};

class MatrixGraphPath : public Searchable<PointNode>{
private:
    matrix::Matrix m_matrixGraph;
    PointNode m_initialNode;
    PointNode m_goalNode;

public:
    /**
     * @brief Construct a new Matrix Graph Path object
     * 
     * @param matrixGraph - matrix of graph
     * @param initialNode - initial node
     * @param goalNdoe - goal node
     */
    MatrixGraphPath(const matrix::Matrix& matrixGraph, const PointNode& initialNode, const PointNode& goalNdoe);

    /**
     * @brief The function return initial state
     * 
     * @return State<Node> - initial state
     */
    virtual State<PointNode>& getInitialState();


    /**
     * @brief The function return goal state
     * 
     * @return State<Node> - goal state 
     */
    virtual State<PointNode>& getGoalState();


    /**
     * @brief The function return all possible states to reach from current state
     * 
     * @param state - current state
     * @return std::vector<State<Node>> - vector of all possible states to reach from current state
     */
    virtual std::vector<State<PointNode>*> getAllPossibleStates(const State<PointNode>& state);

    /**
     * @brief The function set all states of matrix to m_states vector
     * 
     */
    void setStatesOfMatrix();

    /**
     * @brief The function set distance for all states to goal state
     * 
     */
    void setDistanceForStatesToGoalState();

    /**
     * @brief The function return state according row and column of matrix
     * 
     * @param row - row
     * @param column - column
     * @return State<PointNode>& - state 
     */
    State<PointNode>& getState(const unsigned int row, const unsigned int column);
    
    /**
     * @brief The function return x coordinate of leffetr node in matrix
     * 
     * @param row - row 
     * @param column - column 
     * @return double - x coordinate
     */
    double getXCoordinateOfLeffterNode(const unsigned int row, const unsigned int column);

    /**
     * @brief The function return y coordinate of upper node int matrix
     * 
     * @param row - row
     * @param column - column
     * @return double - y coordinate
     */
    double getYCoordinateOfUpperNode(const unsigned int row, const unsigned int column);
};

template <class Node> class Solution{ 
private:
    std::vector<State<Node>> m_solutionPathStates;  
    std::string m_algorithm;  
public:
    /**
     * @brief Construct a new Solution object.
     * 
     * @param solutionPathStates - vector of states to solution path.
     * @param algorithm - algorithm name.
     */
    Solution(const std::vector<State<Node>>& solutionPathStates, const std::string& algorithm) : m_solutionPathStates(solutionPathStates), m_algorithm(algorithm){};

    /**
     * @brief The function check if solution graph path is exist.
     * 
     * @return true - solution graph path is exist.
     * @return false - solution graph path is not exist.
     */
    bool isSolutionExist() const{
        return !m_solutionPathStates.empty();
    }

    /**
     * @brief The function return solution path graph.
     * 
     * @return std::string - solution path graph.
     */
    std::string getSolution() const{
        std::string solution;
        
        if(m_solutionPathStates.empty()){
            throw exceptions::MatrixPathNotFound();
        }

        double cost = 0;
        for(State<Node> state : m_solutionPathStates){
            cost += state.getCost();
        }

        solution += std::to_string(cost) + "," + m_algorithm;
    
        for(int element = 0; element < (int)m_solutionPathStates.size() - 1; ++element){
           solution += "," + (m_solutionPathStates.at(element) >> m_solutionPathStates.at(element + 1));
        }

        return solution;
    }
};


template <class Node> class Searcher{
    /**
     * @brief The function search the solution in searchable and return it.
     * 
     * @param searchable - object for search.
     * @return Solution - solution of searching.
     */
    virtual Solution<Node> search(Searchable<Node>& searchable) = 0;
};

template <class Node> class BreadthFirstSearch : public Searcher<Node>{
public:
    /**
     * @brief The function search the solution in searchable and return it.
     * 
     * @param searchable - object for search.
     * @return Solution - solution of searching.
     */
    virtual Solution<Node> search(Searchable<Node>& searchable){
        std::queue<State<Node>> statesQueue;
        State<Node> initialState = searchable.getInitialState();
        initialState.setVisited(true);
        statesQueue.push(initialState);

        while(!statesQueue.empty()){
            State<Node>& currentState = statesQueue.front();
            statesQueue.pop();
            for(State<Node>* state : searchable.getAllPossibleStates(currentState)){
                if(!state->getVisited()){
                    state->setVisited(true);
                    state->setPrevState(currentState);
                    statesQueue.push(*state);
                }
            }
        }
       
        std::vector<State<Node>> solutionPathStates;
        State<Node> state = searchable.getGoalState();
        for(; state.hasPreviousState(); state = state.getCameFromState()){
            solutionPathStates.push_back(state);    
        }
        solutionPathStates.push_back(state);
        
        std::reverse(solutionPathStates.begin(), solutionPathStates.end());

        if(!(solutionPathStates.at(0).getNode() == searchable.getInitialState().getNode())){
            solutionPathStates.clear();
        }

        return Solution<Node>(solutionPathStates, "BFS");
    }
};

template <class Node> class DepthFirstSearch : public Searcher<Node>{
private:
    /**
     * @brief The function initilize states of matrix.
     * 
     * @param currentState - starting state.
     * @param searchable -  object for search.
     */
    void dfs(State<Node>& currentState, Searchable<Node>& searchable){
        if(!currentState.getVisited()){
            currentState.setVisited(true);
            for(State<Node>* state : searchable.getAllPossibleStates(currentState)){
                if(!state->hasPreviousState()){
                    state->setPrevState(currentState);
                }
                dfs(*state, searchable);
            }
        }
    }
public:
    /**
     * @brief The function search the solution in searchable and return it.
     * 
     * @param searchable - object for search.
     * @return Solution - solution of searching.
     */
    virtual Solution<Node> search(Searchable<Node>& searchable){
        State<Node>& initialState = searchable.getInitialState();
    
       dfs(initialState, searchable);
       
        std::vector<State<Node>> solutionPathStates;
        State<Node> state = searchable.getGoalState();
        for(; state.hasPreviousState() && !(state.getNode() == initialState.getNode()); state = state.getCameFromState()){
            solutionPathStates.push_back(state);    
        }
        solutionPathStates.push_back(state);
        
        std::reverse(solutionPathStates.begin(), solutionPathStates.end());

        if(!(solutionPathStates.at(0).getNode() == searchable.getInitialState().getNode())){
            solutionPathStates.clear();
        }

        return Solution<Node>(solutionPathStates, "DFS");
       
    }
};

template <class Node> class AStar : public Searcher<Node>{
public:
    /**
     * @brief The function search the solution in searchable and return it.
     * 
     * @param searchable - object for search.
     * @return Solution - solution of searching.
     */
    virtual Solution<Node> search(Searchable<Node>& searchable){
        std::map<double, State<Node>&> statesPriorityMap;
        std::map<State<Node>*, double> statesDistMap;
        State<Node>& initialState = searchable.getInitialState();   

        statesPriorityMap.insert(std::pair<double, State<Node>&>(initialState.getDistanceToGoalState() + initialState.getCost(), initialState));
        statesDistMap.insert(std::pair<State<Node>*, double>(&initialState, initialState.getCost()));
        while(!statesPriorityMap.empty()){
            State<Node>& currentState = statesPriorityMap.begin()->second;
            statesPriorityMap.erase(statesPriorityMap.begin()->first);
            for(State<Node>* state : searchable.getAllPossibleStates(currentState)){
                if(!state->getVisited()){
                    if(statesDistMap.find(state) != statesDistMap.end()){
                        if(statesDistMap[&currentState] + state->getCost() + state->getDistanceToGoalState() < statesDistMap[state] + state->getDistanceToGoalState()){
                            statesDistMap[state] = statesDistMap[&currentState] + state->getCost();
                            state->setPrevState(currentState);
                        }
                    } else{
                        statesDistMap.insert(std::pair<State<Node>*, double>(state, statesDistMap[&currentState] + state->getCost()));
                        state->setPrevState(currentState);
                        statesPriorityMap.insert(std::pair<double, State<Node>&>(statesDistMap[state] + state->getDistanceToGoalState(), *state));    
                    }
                }
            }
            currentState.setVisited(true);
        }
      
        std::vector<State<Node>> solutionPathStates;
        State<Node> state = searchable.getGoalState();
        for(; state.hasPreviousState(); state = state.getCameFromState()){
            solutionPathStates.push_back(state);    
        }
        solutionPathStates.push_back(state);
        
        std::reverse(solutionPathStates.begin(), solutionPathStates.end());

        if(!(solutionPathStates.at(0).getNode() == searchable.getInitialState().getNode())){
            solutionPathStates.clear();
        }

        return Solution<Node>(solutionPathStates, "A*");
       
    }
};

}