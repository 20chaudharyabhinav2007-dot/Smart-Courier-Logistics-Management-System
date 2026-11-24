
#include <iostream>
#include "bst.h"
using namespace std;

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    destroyTree(root);
}

BST::Node* BST::insertNode(Node* root, int id) {
    if (root == nullptr) {
        return new Node(id);
    }

    if (id < root->trackingID) {
        root->left = insertNode(root->left, id);
    }
    else if (id > root->trackingID) {
        root->right = insertNode(root->right, id);
    }

    return root;
}

void BST::insert(int id) {
    root = insertNode(root, id);
}

bool BST::searchNode(Node* root, int id) const {
    if (root == nullptr) {
        return false;
    }

    if (root->trackingID == id) {
        return true;
    }

    if (id < root->trackingID) {
        return searchNode(root->left, id);
    }

    return searchNode(root->right, id);
}

bool BST::search(int id) const {
    return searchNode(root, id);
}

BST::Node* BST::findMin(Node* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }

    return root;
}

BST::Node* BST::deleteNode(Node* root, int id) {
    if (root == nullptr) {
        return nullptr;
    }

    if (id < root->trackingID) {
        root->left = deleteNode(root->left, id);
    }
    else if (id > root->trackingID) {
        root->right = deleteNode(root->right, id);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->trackingID = temp->trackingID;
        root->right = deleteNode(root->right, temp->trackingID);
    }

    return root;
}

void BST::remove(int id) {
    root = deleteNode(root, id);
}

void BST::inorder(Node* root) const {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->trackingID << endl;
    inorder(root->right);
}

void BST::display() const {
    if (root == nullptr) {
        cout << "BST is empty." << endl;
        return;
    }

    cout << endl << "PARCEL TRACKING IDs IN SORTED ORDER" << endl;
    inorder(root);
}

void BST::destroyTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}
