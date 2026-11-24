#include "dispatch_queue.h"

DispatchQueue::DispatchQueue() {
    front = nullptr;
    rear = nullptr;
}

DispatchQueue::~DispatchQueue() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    rear = nullptr;
}

void DispatchQueue::enqueue(int id) {
    Node* newNode = new Node(id);

    if (front == nullptr) {
        front = newNode;
        rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

void DispatchQueue::enqueueFront(int id) {
    Node* newNode = new Node(id);

    if (front == nullptr) {
        front = newNode;
        rear = newNode;
    }
    else {
        newNode->next = front;
        front = newNode;
    }
}

bool DispatchQueue::dequeue(int &id) {
    if (front == nullptr) {
        return false;
    }

    Node* temp = front;
    id = temp->trackingID;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    return true;
}

bool DispatchQueue::peek(int &id) const {
    if (front == nullptr) {
        return false;
    }

    id = front->trackingID;
    return true;
}

bool DispatchQueue::remove(int id) {
    Node* temp = front;
    Node* previous = nullptr;

    while (temp != nullptr) {
        if (temp->trackingID == id) {
            if (previous == nullptr) {
                front = temp->next;
            }
            else {
                previous->next = temp->next;
            }

            if (temp == rear) {
                rear = previous;
            }

            delete temp;
            return true;
        }

        previous = temp;
        temp = temp->next;
    }

    return false;
}

bool DispatchQueue::isEmpty() const {
    return front == nullptr;
}

void DispatchQueue::display() const {
    if (front == nullptr) {
        cout << endl << "Dispatch queue is empty." << endl;
        return;
    }

    Node* temp = front;

    cout << endl << "PARCEL DISPATCH QUEUE" << endl;

    while (temp != nullptr) {
        cout << "Tracking ID: " << temp->trackingID << endl;
        temp = temp->next;
    }
}