#ifndef IND1_IINTEGRATEMETHOD_H
#define IND1_IINTEGRATEMETHOD_H

#include <functional>

class IIntegrateMethod {
public:
    virtual double integrate(std::function<double(double)>&, double, double) = 0;
    virtual ~IIntegrateMethod() = default;
};


#endif //IND1_IINTEGRATEMETHOD_H
