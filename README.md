# Smart Courier & Logistics Management System

A terminal-based Courier and Logistics Management System developed in **C++**, demonstrating the practical implementation of Data Structures and Algorithms.

The system manages customers, parcel bookings, shipment tracking, dispatch operations, and shipment history through an interactive menu-driven interface.

## Features

- **Customer Management:** Register, search, and display customers.
- **Parcel Booking:** Book parcels between registered customers.
- **Shipment Tracking:** Search parcels using unique tracking IDs.
- **Status Management:** Update parcel delivery status.
- **Cancellation:** Cancel eligible parcel bookings.
- **Undo Operations:** Reverse the most recent supported operation.
- **Dispatch Management:** Manage parcel dispatch using a queue.
- **Shipment History:** View customer shipment history in forward and reverse order.
- **Sorting:** Display parcels sorted by tracking ID.
- **Searching:** Search parcel records using Binary Search.

## Data Structures & Algorithms Implemented

| Concept | Application |
|---|---|
| Classes and Objects | Customer and Parcel management |
| Dynamic Memory Allocation | Runtime creation and deletion of nodes |
| Singly Linked List | Parcel storage |
| Doubly Linked List | Customer shipment history |
| Stack | Undo functionality |
| Queue | Parcel dispatch management |
| Hash Table (Separate Chaining) | Parcel lookup |
| Binary Search Tree (BST) | Tracking ID storage and traversal |
| Merge Sort | Sorting parcel records |
| Binary Search | Searching sorted parcel records |

## Project Structure

```text
Smart-Courier-Logistics-Management-System/
│
├── centre.cpp
│
├── customer.h
├── customer.cpp
│
├── parcel.h
├── parcel.cpp
│
├── undo.h
├── undo.cpp
│
├── dispatch_queue.h
├── dispatch_queue.cpp
│
├── hash_table.h
├── hash_table.cpp
│
├── bst.h
├── bst.cpp
│
└── .gitignore
```

## Technologies Used

- C++
- Standard Template Library (STL)
- Object-Oriented Programming
- Data Structures and Algorithms
- Git and GitHub

## How to Run

### Prerequisites

- C++ compiler (G++ recommended)
- C++17 support
- Git (optional)

### Compilation

Open the terminal in the project directory and execute:

```bash
g++ -std=c++17 -Wall -Wextra centre.cpp customer.cpp parcel.cpp undo.cpp dispatch_queue.cpp hash_table.cpp bst.cpp -o courier.exe
```

### Execution

**Windows PowerShell:**

```powershell
.\courier.exe
```

**Linux:**

```bash
./courier
```

## System Operations

The application provides a menu-driven interface for:

1. Customer Registration
2. Customer Display
3. Customer Search
4. Parcel Booking
5. Parcel Search
6. Display All Parcels
7. Update Parcel Status
8. Cancel Parcel
9. Warehouse Management
10. Undo Last Operation
11. Display Shipment History
12. Display Reverse Shipment History
13. Display Hash Table
14. Display BST
15. Display Parcels Sorted by Tracking ID
16. Binary Search Parcel

## Learning Objectives

This project demonstrates how fundamental data structures and algorithms can be integrated into a practical application.

It focuses on dynamic memory management, linked data structures, efficient searching and sorting, and maintaining consistency between multiple data structures.

## Author

**Abhinav Chaudhary**

B.Tech – Computer Science and Engineering

[GitHub Profile](https://github.com/20chaudharyabhinav2007-dot)

---

*Developed as an academic Data Structures and Algorithms project.*
