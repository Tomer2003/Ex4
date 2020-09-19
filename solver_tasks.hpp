#include "matrix/ClassMatrix.hpp"
#include <string>
#include <vector>
namespace solver_tasks{

class Solution{ 
public:


};

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

   /**
     * @brief Construct a new Solver object.
     * 
     * @param problem - problem object.
     * @param solution - way to solve the problem object.
     */
    Solver(const Problem& problem, const Solution& solution) noexcept;

    /**
     * @brief The function solve the problem with he solution.
     * 
     * @return Result - the result of the solution of the problem.
     */
    const Result& solve() const;
};


template <class Node> class State{
private:    
    const Node m_node;
    const unsigned int m_cost;
    bool m_visited;
    State<Node>* m_ptrCameFrom;

public:
    State(const Node& node, const unsigned int cost) noexcept : m_node(node), m_visited(false), m_cost(cost), m_ptrCameFrom(nullptr){};

    Node getNode() const{
        return m_node;
    }

    void setVisited(const bool& visited){
        m_visited = visited;
    }

    void setPrevNode(const State<Node>& state){
        m_ptrCameFrom = &state;
    }
};

class PointNode{
private:
    unsigned int m_row;
    unsigned int m_column;

public:
    PointNode(const unsigned int row, const unsigned int column) noexcept;

    bool operator==(const PointNode& pointNode) const;

    unsigned int getRow() const{
        return m_row;
    }

    unsigned int getColumn() const{
        return m_column;
    }
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
     * @brief The function checks if state is goal state 
     * 
     * @param state - state to check if goal state
     * @return true - its goal state
     * @return false - its not goal state
     */
    virtual bool isGoalState(const State<Node>& state) const = 0;

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
     * @brief The function checks if state is goal state 
     * 
     * @param state - state to check if goal state
     * @return true - its goal state
     * @return false - its not goal state
     */
    virtual bool isGoalState(const State<PointNode>& state) const;


    /**
     * @brief The function return all possible states to reach from current state
     * 
     * @param state - current state
     * @return std::vector<State<Node>> - vector of all possible states to reach from current state
     */
    virtual std::vector<State<PointNode>> getAllPossibleStates(const State<PointNode>& state) const;
};


}