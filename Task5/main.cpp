#include <iostream>
#include <omp.h>
#include <vector>

int main(){
    std::vector<float> a = {1.5, 5, 12., 5., 6., 7., 78.};
    std::vector<float> b = {20.5, 6, 15., 10., 8., 6., 120.};

    size_t n = a.size();
    float dot_product = 0.0f;

    #pragma omp parallel default(none) shared(a, b, n, dot_product)
    {
        #pragma omp for reduction(+:dot_product)
        for(int i = 0; i < n; i++)
        {
            dot_product += (a[i] * b[i]);
        }
    }

    float real_dot_product = 0.0f;

    for(int i = 0;i < n;i++){
        real_dot_product += a[i] * b[i];
    }

    std::cout << dot_product << " " << real_dot_product;
}
