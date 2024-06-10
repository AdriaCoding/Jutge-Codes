#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

// Treap Node
struct Node {
    string value;  // The actual string value stored
    int priority;  // Random priority to maintain heap property
    int size;      // Size of the subtree rooted at this node
    int length;    // Total length of strings in the subtree rooted at this node
    Node* left;
    Node* right;

    Node(const string& val) : value(val), priority(rand()), size(1), length(val.size()), left(nullptr), right(nullptr) {}
};

// Update the size and length of the node
void update(Node* node) {
    if (node) {
        node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
        node->length = node->value.size() + (node->left ? node->left->length : 0) + (node->right ? node->right->length : 0);
    }
}

// Split the treap into two based on position
void split(Node* node, int pos, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
    } else {
        int leftSize = node->left ? node->left->size : 0;
        if (pos <= leftSize) {
            split(node->left, pos, left, node->left);
            right = node;
        } else {
            split(node->right, pos - leftSize - 1, node->right, right);
            left = node;
        }
        update(node);
    }
}

// Merge two treaps
Node* merge(Node* left, Node* right) {
    if (!left || !right) {
        return left ? left : right;
    } else if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

// Insert a new node at a given position
void insert(Node*& root, const string& value, int pos) {
    Node* newNode = new Node(value);
    Node *left, *right;
    split(root, pos, left, right);
    root = merge(merge(left, newNode), right);
}

// Get the character at a specific position
char getChar(Node* node, int& pos) {
    if (!node) return '\0';

    if (node->left && pos < node->left->length) {
        return getChar(node->left, pos);
    }

    if (node->left) pos -= node->left->length;
    
    if (pos < node->value.size()) {
        return node->value[pos];
    }
    
    pos -= node->value.size();
    return getChar(node->right, pos);
}

int main() {
    srand(time(0));

    Node* root = nullptr;
    string command, s;
    int i, j;

    while (cin >> command && command != "E") {
        if (command == "I") {
            cin >> s >> i;
            insert(root, s, i);
        } else if (command == "C") {
            cin >> j;
            cout << getChar(root, j);
        }
    }
    cout << endl;
    return 0;
}
