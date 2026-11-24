
#ifndef UNDO_H
#define UNDO_H

#include <iostream>
#include <string>
#include "parcel.h"
using namespace std;

struct UndoNode {
    int operation;
    Parcel parcel;
    string oldStatus;
    UndoNode* next;

    UndoNode(int op, Parcel p, string status) : operation(op), parcel(p), oldStatus(status) {
        next = nullptr;
    }
};

class UndoStack {
private:
    UndoNode* top;

public:
    UndoStack();
    ~UndoStack();

    UndoStack(const UndoStack&) = delete;
    UndoStack& operator=(const UndoStack&) = delete;

    void push(int operation, Parcel parcel, string oldStatus = "");
    bool pop(UndoNode &result);
    bool isEmpty() const;
};

#endif
