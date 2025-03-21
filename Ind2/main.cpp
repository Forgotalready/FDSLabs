#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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
        int thread_nonce = omp_get_thread_num() * 1000;
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
                        std::cout << "Hash: " << hash << "\n";
                    }
                }
                break;
            }
            thread_nonce++;
            #pragma omp flush(found)
        }
    }
    return result_nonce;
}

int main() {
    std::string text = "Hello, world!";
    int difficulty = 6;

    int nonce = PoW(text, difficulty);

    std::string data = text + std::to_string(nonce);
    std::string hash = hash_data(data);

    std::cout << is_valid_hash(hash, difficulty);
}
