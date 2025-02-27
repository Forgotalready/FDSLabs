#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>

using namespace std;

const int N = 500;

void generateMatrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void multiplyMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int num_threads, const string& schedule_type, int chunk_size) {
    double start_time = omp_get_wtime();

#pragma omp parallel for default(none) shared(chunk_size, N, A, B, C) collapse(2) schedule(dynamic, chunk_size) num_threads(num_threads)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end_time = omp_get_wtime();
    cout << "Threads: " << num_threads << ", Schedule: " << schedule_type
         << ", Chunk size: " << chunk_size
         << ", Time: " << end_time - start_time << "s" << endl;
}

int main() {
    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N, 0));

    generateMatrix(A);
    generateMatrix(B);

    vector<int> thread_counts = {1, 2, 4, 8};
    vector<string> schedules = {"static", "dynamic", "guided"};
    vector<int> chunk_sizes = {1, 10, 50};

    for (int threads : thread_counts) {
        for (const string &sched : schedules) {
            for (int chunk : chunk_sizes) {
                multiplyMatrices(A, B, C, threads, sched, chunk);
            }
        }
    }

    return 0;
}
