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




}