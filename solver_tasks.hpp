#include "matrix/ClassMatrix.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
namespace solver_tasks{

/*
class Result{

};

class Problem {
public:
    virtual const Result& solve(const Solution& solution) const = 0;
};


class Solver{
private:
    const Solution& m_solution;
    const Problem& m_problem;

public:

   
     * @brief Construct a new Solver object.
     * 
     * @param problem - problem object.
     * @param solution - way to solve the problem object.
     */
   /* Solver(const Problem& problem, const Solution& solution) noexcept;

    
     * @brief The function solve the problem with he solution.
     * 
     * @return Result - the result of the solution of the problem.
     */
  /*  const Result& solve() const;
};
*/

template <class Node> class State{
private:    
    Node m_node;
    unsigned int m_cost;
    bool m_visited;
    State<Node>* m_ptrCameFrom;

public:
    /**
     * @brief Construct a new State object.
     * 
     * @param node - node of state.
     * @param cost - cost of state.
     */
    State(const Node& node, const unsigned int cost) noexcept : m_node(node), m_cost(cost), m_visited(false), m_ptrCameFrom(nullptr){};

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
/*
    State<Node>& operator=(State<Node>&& other){
         if(this != &other){  
            this->m_cost = other.m_cost;
            this->m_node = other.m_node;
            this->m_ptrCameFrom = other.m_ptrCameFrom;
            this->m_visited = other.m_visited;
            other.m_ptrCameFrom = nullptr;
            other.m_node = nullptr;
        }
        return *this;
    }
*/
    /**
     * @brief The function retun cost of state.
     * 
     * @return unsigned int - cost of state.
     */
    unsigned int getCost() const{
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

public:
    /**
     * @brief Construct a new Point Node object
     * 
     * @param row - row of matrix point. 
     * @param column - column of matrix point.
     */
    PointNode(const unsigned int row, const unsigned int column) noexcept;

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
};


template <class Node> class Searchable{
public:
    /**
     * @brief The function return initial state
     * 
     * @return State<Node> - initial state
     */
    virtual State<Node> getInitialState() const = 0;

    /**
     * @brief The function return goal state
     * 
     * @return State<Node> - goal state 
     */
    virtual State<Node> getGoalState() const = 0;

    /**
     * @brief The function return all possible states to reach from current state
     * 
     * @param state - current state
     * @return std::vector<State<Node>> - vector of all possible states to reach from current state
     */
    virtual std::vector<State<Node>> getAllPossibleStates(const State<Node>& state) const = 0;
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
    MatrixGraphPath(const matrix::Matrix& matrixGraph, const PointNode& initialNode, const PointNode& goalNdoe) noexcept;

    /**
     * @brief The function return initial state
     * 
     * @return State<Node> - initial state
     */
    virtual State<PointNode> getInitialState() const;


    /**
     * @brief The function return goal state
     * 
     * @return State<Node> - goal state 
     */
    virtual State<PointNode> getGoalState() const;


    /**
     * @brief The function return all possible states to reach from current state
     * 
     * @param state - current state
     * @return std::vector<State<Node>> - vector of all possible states to reach from current state
     */
    virtual std::vector<State<PointNode>> getAllPossibleStates(const State<PointNode>& state) const;
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
    Solution(const std::vector<State<Node>>& solutionPathStates, std::string algorithm){
        m_solutionPathStates = solutionPathStates;
        m_algorithm = algorithm;
    }

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

        unsigned int cost = 0;
        for(State<Node> state : m_solutionPathStates){
            cost += state.getCost();
        }

        solution += std::to_string(cost) + "," + m_algorithm;

       for(int element = 0; element < m_solutionPathStates.size() - 1; ++element){
           solution += "," + m_solutionPathStates.at(element) >> m_solutionPathStates.at(element + 1);
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
    virtual Solution<Node> search(const Searchable<Node>& searchable) const = 0;
};

template <class Node> class BreadthFirstSearch : public Searcher<Node>{
public:
    /**
     * @brief The function search the solution in searchable and return it.
     * 
     * @param searchable - object for search.
     * @return Solution - solution of searching.
     */
    virtual Solution<Node> search(const Searchable<Node>& searchable) const{
        std::queue<State<Node>> statesQueue;
        statesQueue.push(searchable.getInitialState());
        searchable.getInitialState().setVisited(true);

        while(!statesQueue.empty()){
            State<Node> currentState = statesQueue.front();
            statesQueue.pop();
            std::cout << "a" << std::endl;
            for(State<Node> state : searchable.getAllPossibleStates(currentState)){
                if(!state.getVisited()){
                    statesQueue.push(state);
                    state.setVisited(true);
                    state.setPrevState(currentState);
                }
            }
        }
        
        std::vector<State<Node>> solutionPathStates;
        for(State<Node> state = searchable.getGoalState(); state.hasPreviousState(); state = state.getCameFromState()){
            solutionPathStates.push_back(state);    
        }
        

        std::reverse(solutionPathStates.begin(), solutionPathStates.end());

        if(!(solutionPathStates.at(0).getNode() == searchable.getInitialState().getNode())){
            solutionPathStates.clear();
        }

        return Solution<Node>(solutionPathStates, "BFS");
    }
};


}