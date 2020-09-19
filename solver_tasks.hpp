#include <string>

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
    State(const Node& node, const unsigned int cost) noexcept : m_node(node), m_visited(false), m_cost(cost){};

    bool equals(const State<Node>& state) const{
        return m_node == state.m_node;
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
};


}