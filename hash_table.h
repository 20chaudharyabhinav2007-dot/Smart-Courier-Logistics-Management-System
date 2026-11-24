#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class Parcel;

class HashTable {
private:
    static const int SIZE = 101;

    struct Node {
        int trackingID;
        Parcel* parcel;
        Node* next;

        Node(int id, Parcel* p) {
            trackingID = id;
            parcel = p;
            next = nullptr;
        }
    };

    Node* table[SIZE];

    int hashFunction(int id) const;

public:
    HashTable();
    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void insert(int id, Parcel* parcel);
    Parcel* search(int id) const;
    bool remove(int id);
    void display() const;
};

#endif