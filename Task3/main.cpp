#include <iostream>
#include "Queue/Queue.h"

int main() {
    Queue<int> queue;
    queue.push(10);
    queue.push(20);
    queue.output(std::cout);
}
