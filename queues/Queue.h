#ifndef QUEUE_H
#define QUEUE_H
#include <list>
#include <iostream>

using namespace std;
namespace cop4530 {
template<typename T>
class Queue
{
public:
    Queue();
    ~Queue();
    Queue(const Queue &rhs);
    Queue(Queue &&rhs);
    Queue& operator=(const Queue &rhs);
    Queue& operator=(Queue &&rhs);
    T& back();
    const T& back() const;
    bool empty() const;
    T& front();
    const T& front() const;
    void pop();
    void push(const T& val);
    void push(T&& val);
    int size() const;


private:
    list<T> queueList;
};

#include "Queue.hpp"
}
#endif
