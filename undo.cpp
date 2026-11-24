
#include "undo.h"

UndoStack::UndoStack() {
    top = nullptr;
}

UndoStack::~UndoStack() {
    while (top != nullptr) {
        UndoNode* temp = top;
        top = top->next;
        delete temp;
    }
}

void UndoStack::push(int operation, Parcel parcel, string oldStatus) {
    UndoNode* newNode = new UndoNode(operation, parcel, oldStatus);

    newNode->next = top;
    top = newNode;
}

bool UndoStack::pop(UndoNode &result) {
    if (top == nullptr) {
        return false;
    }

    result.operation = top->operation;
    result.parcel = top->parcel;
    result.oldStatus = top->oldStatus;

    UndoNode* temp = top;
    top = top->next;

    delete temp;

    return true;
}

bool UndoStack::isEmpty() const {
    return top == nullptr;
}
