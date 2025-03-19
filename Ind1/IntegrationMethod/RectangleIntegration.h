#ifndef IND1_RECTANGLEINTEGRATION_H
#define IND1_RECTANGLEINTEGRATION_H

#include "omp.h"
#include "IIntegrateMethod.h"

class RectangleIntegration : public IIntegrateMethod {
public:
    double integrate(std::function<double(double)>&, double, double) override;
};

#endif //IND1_RECTANGLEINTEGRATION_H
