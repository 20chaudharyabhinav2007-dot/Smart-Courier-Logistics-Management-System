
#include <iostream>
#include <limits>
#include "customer.h"
using namespace std;

Customer::Customer(int i, string n, string a, string p) {
    name = n;
    id = i;
    address = a;
    phone = p;
    historyHead = nullptr;
    historyTail = nullptr;
}

Customer::~Customer() {
    HistoryNode* temp = historyHead;

    while (temp != nullptr) {
        HistoryNode* current = temp;
        temp = temp->next;
        delete current;
    }
}

int Customer::getnumberid() const {
    return id;
}

string Customer::getname() const {
    return name;
}

string Customer::getaddress() const {
    return address;
}

string Customer::getphone() const {
    return phone;
}

void Customer::addShipment(int trackingID, string type) {
    HistoryNode* newNode = new HistoryNode(trackingID, type);

    if (historyHead == nullptr) {
        historyHead = newNode;
        historyTail = newNode;
    }
    else {
        historyTail->next = newNode;
        newNode->prev = historyTail;
        historyTail = newNode;
    }
}

void Customer::displayHistory() const {
    if (historyHead == nullptr) {
        cout << "No shipment history." << endl;
        return;
    }

    HistoryNode* temp = historyHead;

    while (temp != nullptr) {
        cout << "Tracking ID: " << temp->trackingID;
        cout << " | Type: " << temp->type << endl;
        temp = temp->next;
    }
}

void Customer::displayReverseHistory() const {
    if (historyTail == nullptr) {
        cout << "No shipment history." << endl;
        return;
    }

    HistoryNode* temp = historyTail;

    while (temp != nullptr) {
        cout << "Tracking ID: " << temp->trackingID;
        cout << " | Type: " << temp->type << endl;
        temp = temp->prev;
    }
}

void Customer::removeShipment(int trackingID) {
    HistoryNode* temp = historyHead;

    while (temp != nullptr) {
        if (temp->trackingID == trackingID) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            else {
                historyHead = temp->next;
            }

            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
            else {
                historyTail = temp->prev;
            }

            delete temp;
            return;
        }

        temp = temp->next;
    }
}

Customerman::~Customerman() {
    for (size_t i = 0; i < customers.size(); i++) {
        delete customers[i];
    }
}

void Customerman::registerCustomer() {
    string name, address, phone;

    cout << endl << "Enter customer name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter address: ";
    getline(cin, address);

    cout << "Enter phone number: ";
    getline(cin, phone);

    Customer* c = new Customer(nextId, name, address, phone);

    customers.push_back(c);

    cout << endl << "Customer registered successfully!" << endl;
    cout << "Customer ID: " << nextId << endl;

    nextId++;
}

void Customerman::displayCustomers() {
    if (customers.empty()) {
        cout << endl << "No customers registered." << endl;
        return;
    }

    cout << endl << "\t\tCUSTOMER DETAILS" << endl;

    for (size_t i = 0; i < customers.size(); i++) {
        cout << endl;
        cout << "Customer ID: " << customers[i]->getnumberid() << endl;
        cout << "Name: " << customers[i]->getname() << endl;
        cout << "Address: " << customers[i]->getaddress() << endl;
        cout << "Phone: " << customers[i]->getphone() << endl;
    }
}

void Customerman::searchCustomer() {
    int id;

    cout << endl << "Enter customer ID: ";
    cin >> id;

    Customer* c = getCustomer(id);

    if (c == nullptr) {
        cout << "Customer not found." << endl;
        return;
    }

    cout << endl << "Customer found!" << endl;
    cout << "Customer ID: " << c->getnumberid() << endl;
    cout << "Name: " << c->getname() << endl;
    cout << "Address: " << c->getaddress() << endl;
    cout << "Phone: " << c->getphone() << endl;
}

bool Customerman::customerExists(int id) const {
    return getCustomer(id) != nullptr;
}

Customer* Customerman::getCustomer(int id) const {
    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i]->getnumberid() == id) {
            return customers[i];
        }
    }

    return nullptr;
}

void Customerman::displayShipmentHistory() {
    int id;

    cout << endl << "Enter customer ID: ";
    cin >> id;

    Customer* c = getCustomer(id);

    if (c == nullptr) {
        cout << "Customer not found." << endl;
        return;
    }

    cout << endl << "SHIPMENT HISTORY" << endl;
    c->displayHistory();
}

void Customerman::displayReverseShipmentHistory() {
    int id;

    cout << endl << "Enter customer ID: ";
    cin >> id;

    Customer* c = getCustomer(id);

    if (c == nullptr) {
        cout << "Customer not found." << endl;
        return;
    }

    cout << endl << "REVERSE SHIPMENT HISTORY" << endl;
    c->displayReverseHistory();
}
