#ifndef IND1_SOLVER_H
#define IND1_SOLVER_H

#include <functional>
#include <chrono>
#include <iostream>
#include <memory>

#include "IntegrationMethod/IIntegrateMethod.h"

class Solver {
private:
    std::unique_ptr<IIntegrateMethod> _method;
public:
    double integrate(std::function<double(double)>&, double, double);

    explicit Solver(std::unique_ptr<IIntegrateMethod>&& method);
    ~Solver() = default;
};


#endif //IND1_SOLVER_H
