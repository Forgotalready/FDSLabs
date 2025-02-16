#include "Queue.h"

template <class T>
Queue<T>::Queue(std::vector<T>& elems)
        : _queue(elems) {}

template <class T>
void Queue<T>::push(T elem) {
    std::unique_lock lock(_structureMutex);
    _queue.push_back(elem);
    _isQueueEmpty.notify_one();
    lock.unlock();
}

template <class T>
T Queue<T>::top() const {
    std::shared_lock lock(_structureMutex);
    T topElem = _queue[0];
    lock.unlock();
    return topElem;
}

template <class T>
void Queue<T>::pop() {
    std::unique_lock lock(_structureMutex);
    _isQueueEmpty.wait(lock, [this] { return !_queue.empty(); });
    _queue.erase(_queue.begin());
    lock.unlock();
}

template <class T>
template <class U>
std::enable_if_t<has_less_operator_v<U>, T> Queue<T>::min_elem() const {
    std::shared_lock lock(_structureMutex);
    T min_element = *std::min_element(_queue.begin(), _queue.end());
    lock.unlock();
    return min_element;
}

template <class T>
template <class U>
std::enable_if_t<has_less_operator_v<U>, T> Queue<T>::max_elem() const {
    std::shared_lock lock(_structureMutex);
    T max_element = *std::max_element(_queue.begin(), _queue.end());
    lock.unlock();
    return max_element;
}

template <class T>
void Queue<T>::output(std::ostream& out) {
    std::shared_lock lock(_structureMutex);
    for (const T& x : _queue) {
        out << x << " ";
    }
    lock.unlock();
}
