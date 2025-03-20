#include "RectangleIntegrationNoParralel.h"

double RectangleIntegrationNoParralel::integrate(std::function<double(double)> &func, double a, double b) {
    double h = 0.01;
    double sum = 0.0;

    int step_amount = static_cast<int>(std::round((b - a) / h));

    for (int i = 0; i < step_amount; i++) {
        double point = a + i * h;
        sum += func(point) * h;
    }

    double last_point = a + step_amount * h;
    double remainder = b - last_point;

    if (std::abs(remainder) > 1e-6) {
        sum += func(last_point) * remainder;
    }

    return sum;
}
