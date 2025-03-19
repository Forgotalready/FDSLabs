#include <iostream>
#include <functional>
#include "Solver.h"
#include "IntegrationMethod/RectangleIntegration.h"

int main() {
    IIntegrateMethod* method = new RectangleIntegration();
    Solver solver(method);

    std::function<double(double)> func = [](double x){return x;};
    std::cout << solver.integrate(func, 0, 10);
    delete method;
}
