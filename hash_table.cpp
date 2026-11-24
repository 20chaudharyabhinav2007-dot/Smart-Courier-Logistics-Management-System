#include <iostream>
#include "hash_table.h"
#include "parcel.h"
using namespace std;

HashTable::HashTable() {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < SIZE; i++) {
        Node* temp = table[i];

        while (temp != nullptr) {
            Node* current = temp;
            temp = temp->next;
            delete current;
        }
    }
}

int HashTable::hashFunction(int id) const {
    return id % SIZE;
}

void HashTable::insert(int id, Parcel* parcel) {
    int index = hashFunction(id);

    Node* temp = table[index];

    while (temp != nullptr) {
        if (temp->trackingID == id) {
            temp->parcel = parcel;
            return;
        }

        temp = temp->next;
    }

    Node* newNode = new Node(id, parcel);
    newNode->next = table[index];
    table[index] = newNode;
}

Parcel* HashTable::search(int id) const {
    int index = hashFunction(id);

    Node* temp = table[index];

    while (temp != nullptr) {
        if (temp->trackingID == id) {
            return temp->parcel;
        }

        temp = temp->next;
    }

    return nullptr;
}

bool HashTable::remove(int id) {
    int index = hashFunction(id);

    Node* temp = table[index];
    Node* previous = nullptr;

    while (temp != nullptr) {
        if (temp->trackingID == id) {
            if (previous == nullptr) {
                table[index] = temp->next;
            }
            else {
                previous->next = temp->next;
            }

            delete temp;
            return true;
        }

        previous = temp;
        temp = temp->next;
    }

    return false;
}

void HashTable::display() const {
    cout << endl << "HASH TABLE" << endl;

    for (int i = 0; i < SIZE; i++) {
        if (table[i] != nullptr) {
            cout << "Bucket " << i << ": ";

            Node* temp = table[i];

            while (temp != nullptr) {
                cout << temp->trackingID;

                if (temp->next != nullptr) {
                    cout << " -> ";
                }

                temp = temp->next;
            }

            cout << endl;
        }
    }
}