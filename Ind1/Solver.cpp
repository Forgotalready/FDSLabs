#include "Solver.h"

double Solver::integrate(std::function<double(double)>& func, double a, double b) {
    auto start = std::chrono::high_resolution_clock::now();

    double result = _method->integrate(func, a, b);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Integration took " << duration.count() << " seconds." << std::endl; // Вывод времени

    return result;
}

Solver::Solver(std::unique_ptr<IIntegrateMethod>&& method)
    : _method(std::move(method)) {}
