
#include <iostream>
#include "customer.h"
#include "parcel.h"
using namespace std;

void showMenu() {
    cout << endl;
    cout << "===== SMART COURIER & LOGISTICS MANAGEMENT SYSTEM =====" << endl;
    cout << "1. Register Customer" << endl;
    cout << "2. Display All Customers" << endl;
    cout << "3. Search Customer" << endl;
    cout << "4. Book Parcel" << endl;
    cout << "5. Search Parcel" << endl;
    cout << "6. Display All Parcels" << endl;
    cout << "7. Update Parcel Status" << endl;
    cout << "8. Cancel Parcel" << endl;
    cout << "9. Warehouse Management" << endl;
    cout << "10. Undo Last Operation" << endl;
    cout << "11. Display Shipment History" << endl;
    cout << "12. Display Reverse Shipment History" << endl;
    cout << "13. Display Hash Table" << endl;
    cout << "14. Display BST" << endl;
    cout << "15. Display Parcels Sorted by Tracking ID" << endl;
    cout << "16. Binary Search Parcel" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Customerman cm;
    ParcelManager pm;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cm.registerCustomer();
                break;

            case 2:
                cm.displayCustomers();
                break;

            case 3:
                cm.searchCustomer();
                break;

            case 4:
                pm.bookParcel(cm);
                break;

            case 5:
                pm.searchParcel();
                break;

            case 6:
                pm.displayParcels();
                break;

            case 7:
                pm.updateParcelStatus();
                break;

            case 8:
                pm.cancelParcel(cm);
                break;

            case 9:
                pm.warehouseManagement();
                break;

            case 10:
                pm.undoLastOperation(cm);
                break;

            case 11:
                cm.displayShipmentHistory();
                break;

            case 12:
                cm.displayReverseShipmentHistory();
                break;

            case 13:
                pm.displayHashTable();
                break;

            case 14:
                pm.displayBST();
                break;

            case 15:
                pm.displayParcelsSorted();
                break;

            case 16:
                pm.binarySearchParcel();
                break;

            case 0:
                cout << "Exiting Smart Courier System..." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
