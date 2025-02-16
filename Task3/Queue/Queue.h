//
// Created by Олег on 13.02.2025.
//
#ifndef TASK3_QUEUE_H
#define TASK3_QUEUE_H

#include <vector>
#include <algorithm>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <type_traits>

template <typename, typename = void>
struct has_less_operator : std::false_type {};

template <typename T>
struct has_less_operator<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type {};

template <typename T>
inline constexpr bool has_less_operator_v = has_less_operator<T>::value;

template <class T>
class Queue {
private:
    std::vector<T> _queue;
    std::shared_mutex _structureMutex;
    std::condition_variable _isQueueEmpty;

public:
    Queue() = default;
    explicit Queue(std::vector<T>&);
    ~Queue() = default;

    void push(T);
    T top() const;
    void pop();

    void output(std::ostream& out);

    template <class U = T>
    std::enable_if_t<has_less_operator_v<U>, T> min_elem() const;

    template <class U = T>
    std::enable_if_t<has_less_operator_v<U>, T> max_elem() const;
};

#include "Queue.tpp"

#endif //TASK3_QUEUE_H
