#ifndef IND1_SOLVER_H
#define IND1_SOLVER_H

#include <functional>
#include <chrono>
#include <iostream>
#include "IntegrationMethod/IIntegrateMethod.h"

class Solver {
private:
    IIntegrateMethod* _method;
public:
    double integrate(std::function<double(double)>&, double, double);

    explicit Solver(IIntegrateMethod* method);
    ~Solver() = default;
};


#endif //IND1_SOLVER_H
