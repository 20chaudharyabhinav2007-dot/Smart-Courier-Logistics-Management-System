
#include <iostream>
#include "parcel.h"
#include "undo.h"
#include "hash_table.h"
using namespace std;

ParcelManager::ParcelManager() {
    head = nullptr;
    tail = nullptr;
    nextTrackingID = 5001;

    undoStack = new UndoStack();
    dispatchQueue = new DispatchQueue();
    hashTable = new HashTable();
    bst = new BST();
}

ParcelManager::~ParcelManager() {
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    delete undoStack;
    delete dispatchQueue;
    delete hashTable;
    delete bst;
}

void ParcelManager::insertParcel(const Parcel& p) {
    Node* newNode = new Node(p);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    hashTable->insert(p.getTrackingID(), &newNode->data);
    bst->insert(p.getTrackingID());
}

bool ParcelManager::removeParcel(int id, Parcel& removed) {
    Node* temp = head;
    Node* previous = nullptr;

    while (temp != nullptr) {
        if (temp->data.getTrackingID() == id) {
            removed = temp->data;

            hashTable->remove(id);
            bst->remove(id);

            if (previous == nullptr) {
                head = temp->next;
            }
            else {
                previous->next = temp->next;
            }

            if (temp == tail) {
                tail = previous;
            }

            delete temp;
            return true;
        }

        previous = temp;
        temp = temp->next;
    }

    return false;
}

bool ParcelManager::findParcel(int id, Parcel& found) const {
    Parcel* p = hashTable->search(id);

    if (p == nullptr) {
        return false;
    }

    found = *p;
    return true;
}

void ParcelManager::bookParcel(Customerman& cm) {
    int senderID, receiverID;
    double weight;

    cout << endl << "Enter sender customer ID: ";
    cin >> senderID;

    Customer* sender = cm.getCustomer(senderID);

    if (sender == nullptr) {
        cout << "Sender customer not found." << endl;
        return;
    }

    cout << "Enter receiver customer ID: ";
    cin >> receiverID;

    Customer* receiver = cm.getCustomer(receiverID);

    if (receiver == nullptr) {
        cout << "Receiver customer not found." << endl;
        return;
    }

    cout << "Enter parcel weight in kg: ";
    cin >> weight;

    if (weight <= 0) {
        cout << "Invalid parcel weight." << endl;
        return;
    }

    Parcel p(nextTrackingID, senderID, receiverID, weight);

    insertParcel(p);
    dispatchQueue->enqueue(nextTrackingID);

    sender->addShipment(nextTrackingID, "SENT");
    receiver->addShipment(nextTrackingID, "RECEIVED");

    undoStack->push(1, p);

    cout << endl << "Parcel booked successfully!" << endl;
    cout << "Tracking ID: " << nextTrackingID << endl;

    nextTrackingID++;
}

void ParcelManager::displayParcels() {
    if (head == nullptr) {
        cout << endl << "No parcels booked." << endl;
        return;
    }

    Node* temp = head;

    cout << endl << "\t\tPARCEL DETAILS" << endl;

    while (temp != nullptr) {
        cout << endl;
        cout << "Tracking ID: " << temp->data.getTrackingID() << endl;
        cout << "Sender ID: " << temp->data.getSenderID() << endl;
        cout << "Receiver ID: " << temp->data.getReceiverID() << endl;
        cout << "Weight: " << temp->data.getWeight() << " kg" << endl;
        cout << "Status: " << temp->data.getStatus() << endl;

        temp = temp->next;
    }
}

void ParcelManager::displayHashTable() {
    hashTable->display();
}

void ParcelManager::displayBST() {
    bst->display();
}

void ParcelManager::searchParcel() {
    int id;

    cout << endl << "Enter tracking ID: ";
    cin >> id;

    Parcel p(0, 0, 0, 0);

    if (!findParcel(id, p)) {
        cout << "Parcel not found." << endl;
        return;
    }

    cout << endl << "Parcel found!" << endl;
    cout << "Tracking ID: " << p.getTrackingID() << endl;
    cout << "Sender ID: " << p.getSenderID() << endl;
    cout << "Receiver ID: " << p.getReceiverID() << endl;
    cout << "Weight: " << p.getWeight() << " kg" << endl;
    cout << "Status: " << p.getStatus() << endl;
}

void ParcelManager::updateParcelStatus() {
    int id, choice;

    cout << endl << "Enter tracking ID: ";
    cin >> id;

    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data.getTrackingID() == id) {
            if (temp->data.getStatus() == "DELIVERED") {
                cout << "Parcel has already been delivered." << endl;
                return;
            }

            string oldStatus = temp->data.getStatus();

            cout << endl << "Select new parcel status:" << endl;
            cout << "1. COLLECTED" << endl;
            cout << "2. ARRIVED AT WAREHOUSE" << endl;
            cout << "3. DISPATCHED" << endl;
            cout << "4. OUT FOR DELIVERY" << endl;
            cout << "5. DELIVERED" << endl;

            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    temp->data.setStatus("COLLECTED");
                    break;

                case 2:
                    temp->data.setStatus("ARRIVED AT WAREHOUSE");
                    break;

                case 3:
                    temp->data.setStatus("DISPATCHED");
                    break;

                case 4:
                    temp->data.setStatus("OUT FOR DELIVERY");
                    break;

                case 5:
                    temp->data.setStatus("DELIVERED");
                    break;

                default:
                    cout << "Invalid status choice." << endl;
                    return;
            }

            dispatchQueue->remove(id);
            undoStack->push(3, temp->data, oldStatus);

            cout << "Parcel status updated successfully!" << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Parcel not found." << endl;
}

void ParcelManager::cancelParcel(Customerman& cm) {
    int id;

    cout << endl << "Enter tracking ID to cancel: ";
    cin >> id;

    Parcel removed(0, 0, 0, 0);

    if (!findParcel(id, removed)) {
        cout << "Parcel not found." << endl;
        return;
    }

    if (removed.getStatus() == "DELIVERED") {
        cout << "Delivered parcels cannot be cancelled." << endl;
        return;
    }

    Customer* sender = cm.getCustomer(removed.getSenderID());
    Customer* receiver = cm.getCustomer(removed.getReceiverID());

    if (sender != nullptr) {
        sender->removeShipment(id);
    }

    if (receiver != nullptr) {
        receiver->removeShipment(id);
    }

    Parcel deleted(0, 0, 0, 0);
    removeParcel(id, deleted);
    dispatchQueue->remove(id);

    undoStack->push(2, removed);

    cout << "Parcel cancelled successfully!" << endl;
}

void ParcelManager::undoLastOperation(Customerman& cm) {
    UndoNode result(0, Parcel(0, 0, 0, 0), "");

    if (!undoStack->pop(result)) {
        cout << endl << "No operation available to undo." << endl;
        return;
    }

    int id = result.parcel.getTrackingID();

    if (result.operation == 1) {
        Parcel removed(0, 0, 0, 0);

        removeParcel(id, removed);
        dispatchQueue->remove(id);

        Customer* sender = cm.getCustomer(result.parcel.getSenderID());
        Customer* receiver = cm.getCustomer(result.parcel.getReceiverID());

        if (sender != nullptr) {
            sender->removeShipment(id);
        }

        if (receiver != nullptr) {
            receiver->removeShipment(id);
        }

        cout << endl << "Last parcel booking undone successfully!" << endl;
    }
    else if (result.operation == 2) {
        insertParcel(result.parcel);

        if (result.parcel.getStatus() == "BOOKED") {
            dispatchQueue->enqueue(id);
        }

        Customer* sender = cm.getCustomer(result.parcel.getSenderID());
        Customer* receiver = cm.getCustomer(result.parcel.getReceiverID());

        if (sender != nullptr) {
            sender->addShipment(id, "SENT");
        }

        if (receiver != nullptr) {
            receiver->addShipment(id, "RECEIVED");
        }

        cout << endl << "Parcel cancellation undone successfully!" << endl;
    }
    else if (result.operation == 3 || result.operation == 4) {
        Node* temp = head;

        while (temp != nullptr) {
            if (temp->data.getTrackingID() == id) {
                temp->data.setStatus(result.oldStatus);

                if (result.oldStatus == "BOOKED") {
                    dispatchQueue->enqueueFront(id);
                }

                cout << endl << "Parcel status update undone successfully!" << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "Parcel not found. Undo could not be completed." << endl;
    }
}

void ParcelManager::displayDispatchQueue() {
    dispatchQueue->display();
}

void ParcelManager::dispatchNextParcel() {
    int id;

    if (!dispatchQueue->peek(id)) {
        cout << endl << "No parcels waiting for dispatch." << endl;
        return;
    }

    Parcel p(0, 0, 0, 0);

    if (!findParcel(id, p)) {
        dispatchQueue->dequeue(id);
        cout << "Invalid parcel entry removed from queue." << endl;
        return;
    }

    if (p.getStatus() != "BOOKED") {
        dispatchQueue->dequeue(id);
        cout << "Parcel is no longer waiting for dispatch." << endl;
        return;
    }

    string oldStatus = p.getStatus();

    dispatchQueue->dequeue(id);

    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data.getTrackingID() == id) {
            temp->data.setStatus("DISPATCHED");
            undoStack->push(4, temp->data, oldStatus);
            break;
        }

        temp = temp->next;
    }

    cout << endl << "Parcel dispatched successfully!" << endl;
    cout << "Tracking ID: " << id << endl;
}

void ParcelManager::warehouseManagement() {
    int choice;

    do {
        cout << endl << "\t\tWAREHOUSE MANAGEMENT" << endl;
        cout << "1. Display Dispatch Queue" << endl;
        cout << "2. Dispatch Next Parcel" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayDispatchQueue();
                break;

            case 2:
                dispatchNextParcel();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 0);
}

void ParcelManager::copyParcels(vector<Parcel>& parcels) const {
    Node* temp = head;

    while (temp != nullptr) {
        parcels.push_back(temp->data);
        temp = temp->next;
    }
}

void ParcelManager::merge(vector<Parcel>& parcels, int left, int mid, int right) {
    vector<Parcel> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (parcels[i].getTrackingID() <= parcels[j].getTrackingID()) {
            temp.push_back(parcels[i]);
            i++;
        }
        else {
            temp.push_back(parcels[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(parcels[i]);
        i++;
    }

    while (j <= right) {
        temp.push_back(parcels[j]);
        j++;
    }

    for (int k = 0; k < static_cast<int>(temp.size()); k++) {
        parcels[left + k] = temp[k];
    }
}

void ParcelManager::mergeSort(vector<Parcel>& parcels, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(parcels, left, mid);
    mergeSort(parcels, mid + 1, right);

    merge(parcels, left, mid, right);
}

void ParcelManager::displayParcelsSorted() {
    vector<Parcel> parcels;

    copyParcels(parcels);

    if (parcels.empty()) {
        cout << "No parcels booked." << endl;
        return;
    }

    int n = static_cast<int>(parcels.size());

    mergeSort(parcels, 0, n - 1);

    cout << endl << "PARCELS SORTED BY TRACKING ID" << endl;

    for (int i = 0; i < n; i++) {
        cout << endl;
        cout << "Tracking ID: " << parcels[i].getTrackingID() << endl;
        cout << "Sender ID: " << parcels[i].getSenderID() << endl;
        cout << "Receiver ID: " << parcels[i].getReceiverID() << endl;
        cout << "Weight: " << parcels[i].getWeight() << " kg" << endl;
        cout << "Status: " << parcels[i].getStatus() << endl;
    }
}

void ParcelManager::binarySearchParcel() {
    vector<Parcel> parcels;

    copyParcels(parcels);

    if (parcels.empty()) {
        cout << "No parcels available to search." << endl;
        return;
    }

    int n = static_cast<int>(parcels.size());

    mergeSort(parcels, 0, n - 1);

    int id;

    cout << endl << "Enter tracking ID to search: ";
    cin >> id;

    int low = 0;
    int high = n - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (parcels[mid].getTrackingID() == id) {
            cout << endl << "Parcel found!" << endl;
            cout << "Tracking ID: " << parcels[mid].getTrackingID() << endl;
            cout << "Sender ID: " << parcels[mid].getSenderID() << endl;
            cout << "Receiver ID: " << parcels[mid].getReceiverID() << endl;
            cout << "Weight: " << parcels[mid].getWeight() << " kg" << endl;
            cout << "Status: " << parcels[mid].getStatus() << endl;

            found = true;
            break;
        }
        else if (parcels[mid].getTrackingID() < id) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Parcel not found." << endl;
    }
}
