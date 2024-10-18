#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value == node->data) {
            cout << "Duplicate value found. Not inserting: " << value << endl;
        } else if (value < node->data) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return root;

        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* search(Node* root, int key) {
        if (root == nullptr || root->data == key)
            return root;
        if (key < root->data)
            return search(root->left, key);
        return search(root->right, key);
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    int calculateDepth(Node* node) {
        if (node == nullptr) return 0;
        return max(calculateDepth(node->left), calculateDepth(node->right)) + 1;
    }

    void displayParentChild(Node* node) {
        if (node == nullptr) return;
        if (node->left != nullptr)
            cout << "Parent: " << node->data << ", Left Child: " << node->left->data << endl;
        if (node->right != nullptr)
            cout << "Parent: " << node->data << ", Right Child: " << node->right->data << endl;
        displayParentChild(node->left);
        displayParentChild(node->right);
    }

    void displayLeafNodes(Node* node) {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {
            cout << node->data << " ";
        }
        displayLeafNodes(node->left);
        displayLeafNodes(node->right);
    }

    Node* mirror(Node* node) {
        if (node == nullptr) return node;
        Node* temp = node->left;
        node->left = mirror(node->right);
        node->right = mirror(temp);
        return node;
    }

    Node* copy(Node* node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    void levelOrder(Node* node) {
        if (node == nullptr) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            cout << current->data << " ";
            q.pop();
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    void search(int key) {
        Node* result = search(root, key);
        if (result != nullptr)
            cout << "Element " << key << " found in the tree." << endl;
        else
            cout << "Element " << key << " not found in the tree." << endl;
    }

    void inOrderTraversal() {
        inOrder(root);
        cout << endl;
    }

    int getDepth() {
        return calculateDepth(root);
    }

    void displayParentChild() {
        displayParentChild(root);
    }

    void displayLeafNodes() {
        displayLeafNodes(root);
        cout << endl;
    }

    void mirrorTree() {
        root = mirror(root);
    }

    void copyTree() {
        Node* newTree = copy(root);
        cout << "Copied tree in in-order: ";
        inOrder(newTree);
        cout << endl;
    }

    void levelOrderTraversal() {
        levelOrder(root);
        cout << endl;
    }
};

int main() {
    BST bst;
    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. In-order Traversal\n";
        cout << "5. Display Depth of Tree\n";
        cout << "6. Display Parent-Child Nodes\n";
        cout << "7. Display Leaf Nodes\n";
        cout << "8. Display Mirror Image (In-order)\n";
        cout << "9. Copy Tree (In-order)\n";
        cout << "10. Level Order Traversal\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bst.insert(value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                bst.deleteNode(value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                bst.search(value);
                break;
            case 4:
                cout << "In-order Traversal: ";
                bst.inOrderTraversal();
                break;
            case 5:
                cout << "Depth of Tree: " << bst.getDepth() << endl;
                break;
            case 6:
                cout << "Parent-Child Nodes:\n";
                bst.displayParentChild();
                break;
            case 7:
                cout << "Leaf Nodes: ";
                bst.displayLeafNodes();
                break;
            case 8:
                bst.mirrorTree();
                cout << "Mirror Image (In-order Traversal): ";
                bst.inOrderTraversal();
                break;
            case 9:
                bst.copyTree();
                break;
            case 10:
                cout << "Level Order Traversal: ";
                bst.levelOrderTraversal();
                break;
            case 11:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}
