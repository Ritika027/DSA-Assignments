#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Node {
    string value;
    Node* left, *right;

    Node(string v) : value(v), left(nullptr), right(nullptr) {}
};

bool isOperator(const string& c) {
    return (c == "+" || c == "-" || c == "*" || c == "/");
}

void inorderRecursive(Node* root) {
    if (root) {
        inorderRecursive(root->left);
        cout << root->value << " ";
        inorderRecursive(root->right);
    }
}

void preorderRecursive(Node* root) {
    if (root) {
        cout << root->value << " ";
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }
}

void postorderRecursive(Node* root) {
    if (root) {
        postorderRecursive(root->left);
        postorderRecursive(root->right);
        cout << root->value << " ";
    }
}

void inorderNonRecursive(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    while (curr != nullptr || !s.empty()) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->value << " ";
        curr = curr->right;
    }
}

void preorderNonRecursive(Node* root) {
    if (root == nullptr) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        cout << curr->value << " ";
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}

void postorderNonRecursive(Node* root) {
    if (root == nullptr) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        Node* curr = s2.top();
        s2.pop();
        cout << curr->value << " ";
    }
}

vector<string> tokenizeInput(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

Node* constructTreeFromPostfix(const vector<string>& postfix) {
    stack<Node*> st;
    for (const string& token : postfix) {
        if (!isOperator(token)) {
            st.push(new Node(token));
        } else {
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            Node* newNode = new Node(token);
            newNode->left = left;
            newNode->right = right;
            st.push(newNode);
        }
    }
    return st.top();
}

Node* constructTreeFromPrefix(const vector<string>& prefix) {
    stack<Node*> st;
    for (auto it = prefix.rbegin(); it != prefix.rend(); ++it) {
        if (!isOperator(*it)) {
            st.push(new Node(*it));
        } else {
            Node* left = st.top(); st.pop();
            Node* right = st.top(); st.pop();
            Node* newNode = new Node(*it);
            newNode->left = left;
            newNode->right = right;
            st.push(newNode);
        }
    }
    return st.top();
}

Node* userInputExpressionTree(bool isPostfix) {
    string expression;
    cout << "Enter the " << (isPostfix ? "postfix" : "prefix") << " expression: ";
    getline(cin, expression);

    vector<string> tokens = tokenizeInput(expression);

    Node* tree;
    if (isPostfix) {
        tree = constructTreeFromPostfix(tokens);
    } else {
        tree = constructTreeFromPrefix(tokens);
    }

    return tree;
}

void displayTraversalMenu(Node* root) {
    int choice;
    do {
        cout << "\nTraversal Menu:\n";
        cout << "1. Recursive Inorder Traversal\n";
        cout << "2. Non-recursive Inorder Traversal\n";
        cout << "3. Recursive Preorder Traversal\n";
        cout << "4. Non-recursive Preorder Traversal\n";
        cout << "5. Recursive Postorder Traversal\n";
        cout << "6. Non-recursive Postorder Traversal\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Recursive Inorder traversal: ";
                inorderRecursive(root);
                cout << endl;
                break;
            case 2:
                cout << "Non-recursive Inorder traversal: ";
                inorderNonRecursive(root);
                cout << endl;
                break;
            case 3:
                cout << "Recursive Preorder traversal: ";
                preorderRecursive(root);
                cout << endl;
                break;
            case 4:
                cout << "Non-recursive Preorder traversal: ";
                preorderNonRecursive(root);
                cout << endl;
                break;
            case 5:
                cout << "Recursive Postorder traversal: ";
                postorderRecursive(root);
                cout << endl;
                break;
            case 6:
                cout << "Non-recursive Postorder traversal: ";
                postorderNonRecursive(root);
                cout << endl;
                break;
            case 7:
                cout << "Exiting traversal menu.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 7);
}

int main() {
    char choice;
    cout << "Do you want to input a prefix (P) or postfix (F) expression? (P/F): ";
    cin >> choice;
    cin.ignore();

    Node* root = nullptr;

    if (choice == 'P' || choice == 'p') {
        root = userInputExpressionTree(false);
    } else if (choice == 'F' || choice == 'f') {
        root = userInputExpressionTree(true);
    } else {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    if (root) {
        displayTraversalMenu(root);
    }

    return 0;
}
