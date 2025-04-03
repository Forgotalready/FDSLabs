#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <random>

#include "omp.h"

std::string to_hex(size_t hash_value) {
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash_value;
    return ss.str();
}

std::string hash_data(const std::string &data) {
    std::hash<std::string> hasher;
    size_t hash_value = hasher(data);
    return to_hex(hash_value);
}

bool is_valid_hash(const std::string &hash, int difficulty) {
    return hash.substr(0, difficulty) == std::string(difficulty, '0');
}

int PoW(const std::string &text, int difficulty) {
    bool found = false;
    int result_nonce = -1;

    #pragma omp parallel default(none) shared(found, result_nonce, difficulty, text, std::cout)
    {
        int thread_nonce = omp_get_thread_num();
        while (!found) {
            std::string data = text + std::to_string(thread_nonce);
            std::string hash = hash_data(data);

            if (is_valid_hash(hash, difficulty)) {
                #pragma omp critical
                {
                    if (!found) {
                        found = true;
                        result_nonce = thread_nonce;
                        std::cout << "Thread " << omp_get_thread_num() << " find nonce: " << result_nonce << "\n";
                        std::cout << "Hash: " << hash << std::endl;
                    }
                }
                break;
            }
            thread_nonce += omp_get_num_threads();
            #pragma omp flush(found)
        }
    }
    return result_nonce;
}

std::string random_string(std::size_t length)
{
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

int main() {
    std::string text = random_string(10);
    int difficulty = 7;
    std::cout << "Start solving PoW" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    int nonce = PoW(text, difficulty);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "PoW took " << duration.count() << " seconds." << std::endl;

    std::string data = text + std::to_string(nonce);
    std::string hash = hash_data(data);
    std::cout << is_valid_hash(hash, difficulty);
}
