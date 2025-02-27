#include <iostream>
#include <thread>
#include <vector>
#include <random>

float generate_random_value(){
    return (float) rand() / rand();
}

void fill_array(std::vector<int>& arr, int start, int end){
    for(int i = start;i < end;i++){
        arr[i] = generate_random_value();
    }
}

int main() {
    int k = 20;
    int n = 60000;

    int chunk_size = n / k;
    int remainder = n % k;

    std::vector<int> generated_array(n);
    std::vector<std::thread> threads;

    auto startTime = std::chrono::high_resolution_clock::now();

    for(int i = 0, start = 0;i < k;i++){
        int end = start + chunk_size;
        if(i < remainder){
            end++;
        }
        threads.emplace_back([start, end, &generated_array](){ fill_array(generated_array, start, end);});
        start = end;
    }
    for(std::thread& tr : threads){
        tr.join();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    //for(const int& x : generated_array){
    //    std::cout << x << " ";
    //}
}
