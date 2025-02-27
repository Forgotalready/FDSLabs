#include <iostream>
#include <thread>
#include <mutex>

void count_down(int n)
{
    std::cout << "Count down thread id: " << std::this_thread::get_id() << std::endl;
    for(int i = n;i >= 0;i--)
    {
        std::cout << i << " ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\n";
}

int main()
{
    int n = 20;
    std::cout << "Main Thread id: " << std::this_thread::get_id() << std::endl;
    std::thread countDownThread([&n](){ count_down(n);});
    countDownThread.join();
    return 0;
}
