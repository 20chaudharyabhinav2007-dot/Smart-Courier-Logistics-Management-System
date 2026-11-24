
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer {
private:
    struct HistoryNode {
        int trackingID;
        string type;
        HistoryNode* next;
        HistoryNode* prev;

        HistoryNode(int id, string t) {
            trackingID = id;
            type = t;
            next = nullptr;
            prev = nullptr;
        }
    };

    string name;
    int id;
    string address;
    string phone;

    HistoryNode* historyHead;
    HistoryNode* historyTail;

public:
    Customer(int i, string n, string a, string p);

    Customer(const Customer&) = delete;
    Customer& operator=(const Customer&) = delete;

    ~Customer();

    int getnumberid() const;
    string getname() const;
    string getaddress() const;
    string getphone() const;

    void addShipment(int trackingID, string type);
    void displayHistory() const;
    void displayReverseHistory() const;
    void removeShipment(int trackingID);
};

class Customerman {
private:
    vector<Customer*> customers;
    int nextId = 1000;

public:
    ~Customerman();

    void registerCustomer();
    void displayCustomers();
    void searchCustomer();
    bool customerExists(int id) const;
    Customer* getCustomer(int id) const;
    void displayShipmentHistory();
    void displayReverseShipmentHistory();
};

#endif
