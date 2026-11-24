
#ifndef PARCEL_H
#define PARCEL_H

#include <iostream>
#include <string>
#include <vector>
#include "customer.h"
#include "dispatch_queue.h"
#include "bst.h"
using namespace std;

class HashTable;
class UndoStack;

class Parcel {
private:
    int trackingID;
    int senderID;
    int receiverID;
    double weight;
    string status;

public:
    Parcel(int t, int s, int r, double w) {
        trackingID = t;
        senderID = s;
        receiverID = r;
        weight = w;
        status = "BOOKED";
    }

    int getTrackingID() const {
        return trackingID;
    }

    int getSenderID() const {
        return senderID;
    }

    int getReceiverID() const {
        return receiverID;
    }

    double getWeight() const {
        return weight;
    }

    string getStatus() const {
        return status;
    }

    void setStatus(string s) {
        status = s;
    }
};

class ParcelManager {
private:
    BST* bst;

    struct Node {
        Parcel data;
        Node* next;

        Node(const Parcel& p) : data(p), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int nextTrackingID;

    UndoStack* undoStack;
    DispatchQueue* dispatchQueue;
    HashTable* hashTable;

    void insertParcel(const Parcel& p);
    bool removeParcel(int id, Parcel& removed);
    bool findParcel(int id, Parcel& found) const;

    void copyParcels(vector<Parcel>& parcels) const;
    void merge(vector<Parcel>& parcels, int left, int mid, int right);
    void mergeSort(vector<Parcel>& parcels, int left, int right);

public:
    ParcelManager();
    ~ParcelManager();

    ParcelManager(const ParcelManager&) = delete;
    ParcelManager& operator=(const ParcelManager&) = delete;

    void bookParcel(Customerman& cm);
    void displayParcels();
    void searchParcel();
    void updateParcelStatus();
    void cancelParcel(Customerman& cm);
    void undoLastOperation(Customerman& cm);

    void displayDispatchQueue();
    void dispatchNextParcel();
    void warehouseManagement();

    void displayHashTable();
    void displayBST();

    void displayParcelsSorted();
    void binarySearchParcel();
};

#endif
