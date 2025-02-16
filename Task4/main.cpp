#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex barrier_mutex;
std::condition_variable barrier_cv;
int waiting_threads = 0;
const int NUM_THREADS = 3;

void barrier_sync(){
    std::unique_lock<std::mutex> lock(barrier_mutex);
    waiting_threads++;
    if(waiting_threads == NUM_THREADS){
        waiting_threads = 0;
        barrier_cv.notify_all();
    }else{
        std::cout << "Thread " << std::this_thread::get_id() << " wait\n";
        barrier_cv.wait(lock);
    }
    std::cout <<  "Thread " << std::this_thread::get_id() << " continue\n";
}

int main() {
    std::thread thread1([](){barrier_sync();});
    std::thread thread2([](){barrier_sync();});
    std::thread thread3([](){barrier_sync();});

    thread1.join();
    thread2.join();
    thread3.join();
}
