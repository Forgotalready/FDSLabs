#include <iostream>
#include <functional>
#include "Solver.h"
#include "IntegrationMethod/RectangleIntegration.h"
#include "IntegrationMethod/RectangleIntegrationNoParralel.h"

int main() {
    const double a = 0;
    const double b = 1000000;
    std::function func = [](double x){return sin(x);};

    std::unique_ptr<IIntegrateMethod> method = std::make_unique<RectangleIntegration>();
    Solver solver(std::move(method));
    std::cout << solver.integrate(func, a, b) << std::endl;

    std::unique_ptr<IIntegrateMethod> newMethod = std::make_unique<RectangleIntegrationNoParralel>();
    Solver solverNoParralel(std::move(newMethod));
    std::cout << solverNoParralel.integrate(func, a, b) << std::endl;
}
