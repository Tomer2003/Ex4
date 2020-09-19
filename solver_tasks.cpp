#include "solver_tasks.hpp"


namespace solver_tasks{
    Solver::Solver(const Problem& problem, const Solution& solution) noexcept : m_solution(solution), m_problem(problem){};

    const Result& Solver::solve() const{
        return m_problem.solve(m_solution);
    }















}