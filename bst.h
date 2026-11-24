
#ifndef BST_H
#define BST_H

class BST {
private:
    struct Node {
        int trackingID;
        Node* left;
        Node* right;

        Node(int id) {
            trackingID = id;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insertNode(Node* root, int id);
    Node* deleteNode(Node* root, int id);
    Node* findMin(Node* root);
    bool searchNode(Node* root, int id) const;
    void inorder(Node* root) const;
    void destroyTree(Node* root);

public:
    BST();
    ~BST();

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(int id);
    void remove(int id);
    bool search(int id) const;
    void display() const;
};

#endif
