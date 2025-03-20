#ifndef RECTANGLEINTEGRATIONNOPARRALEL_H
#define RECTANGLEINTEGRATIONNOPARRALEL_H

#include "IIntegrateMethod.h"
#include <cmath>

class RectangleIntegrationNoParralel : public IIntegrateMethod {
public:
    double integrate(std::function<double(double)> &, double, double) override;
    ~RectangleIntegrationNoParralel() override = default ;
};

#endif //RECTANGLEINTEGRATIONNOPARRALEL_H
