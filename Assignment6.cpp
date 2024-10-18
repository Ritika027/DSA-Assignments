#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool leftThread, rightThread;

    Node(int value) {
        data = value;
        left = right = nullptr;
        leftThread = rightThread = true;
    }
};

class ThreadedBinaryTree {
private:
    Node* root;

public:
    ThreadedBinaryTree() : root(nullptr) {}

    void insert(int key) {
        Node* newNode = new Node(key);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (key < current->data) {
                if (!current->leftThread) {
                    current = current->left;
                } else {
                    break;
                }
            } else {
                if (!current->rightThread) {
                    current = current->right;
                } else {
                    break;
                }
            }
        }

        if (key < parent->data) {
            newNode->left = parent->left;
            newNode->right = parent;
            parent->leftThread = false;
            parent->left = newNode;
        } else {
            newNode->left = parent;
            newNode->right = parent->right;
            parent->rightThread = false;
            parent->right = newNode;
        }
    }

    void inorder() {
        if (root == nullptr) return;

        Node* current = root;

        while (!current->leftThread) {
            current = current->left;
        }

        while (current != nullptr) {
            cout << current->data << " ";

            if (current->rightThread) {
                current = current->right;
            } else {
                current = current->right;
                while (current != nullptr && !current->leftThread) {
                    current = current->left;
                }
            }
        }
    }

    void preorder() {
        if (root == nullptr) return;

        Node* current = root;

        while (current != nullptr) {
          
            cout << current->data << " ";

            
            if (!current->leftThread) {
                current = current->left;
            }
           
            else {
                while (current != nullptr && current->rightThread) {
                    current = current->right;
                }
                if (current != nullptr) {
                    current = current->right;
                }
            }
        }
    }
};

int main() {
    ThreadedBinaryTree tree;
    int choice, value;

    do {
        cout << "\n--- Threaded Binary Tree Menu ---\n";
        cout << "1. Insert\n";
        cout << "2. In-order Traversal\n";
        cout << "3. Pre-order Traversal\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;

            case 2:
                cout << "In-order Traversal: ";
                tree.inorder();
                cout << endl;
                break;

            case 3:
                cout << "Pre-order Traversal: ";
                tree.preorder();
                cout << endl;
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
