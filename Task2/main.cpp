#include<iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <random>

std::mutex consoleMutex;

void generate_float_vector(int n){
    std::vector<float> values(n);
    for(int i = 0;i < n; i++){
        values[i] = (float) rand() / rand();
    }

    consoleMutex.lock();
    std::cout << "Thread " << std::this_thread::get_id() << " result:\n";
    for(const float& x : values){
        std::cout << x << " ";
    }
    std::cout << "\n";
    consoleMutex.unlock();
}

int main() {
    int k = 20;
    int n = 5;

    std::vector<std::thread> threads;
    for(int i = 0;i < k;i++){
        threads.emplace_back([&n](){ generate_float_vector(n); } );
    }

    for(int i = 0;i < k;i++){
        threads[i].join();
    }
}
