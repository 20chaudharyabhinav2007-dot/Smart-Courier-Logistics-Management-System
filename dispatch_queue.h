#ifndef DISPATCH_QUEUE_H
#define DISPATCH_QUEUE_H

#include <iostream>
using namespace std;

class DispatchQueue {
private:
    struct Node {
        int trackingID;
        Node* next;

        Node(int id) {
            trackingID = id;
            next = nullptr;
        }
    };

    Node* front;
    Node* rear;

public:
    DispatchQueue();
    ~DispatchQueue();

    DispatchQueue(const DispatchQueue&) = delete;
    DispatchQueue& operator=(const DispatchQueue&) = delete;

    void enqueue(int id);
    void enqueueFront(int id);
    bool dequeue(int &id);
    bool peek(int &id) const;
    bool remove(int id);
    bool isEmpty() const;
    void display() const;
};

#endif