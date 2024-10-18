#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* next;
};


class Queue {
private:
    Node* front;  // Pointer to the front of the queue
    Node* rear;   // Pointer to the rear of the queue

public:

    Queue() {
        front = nullptr;
        rear = nullptr;
    }

  
    bool isEmpty() {
        return front == nullptr;
    }

  
    void enqueue(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (rear == nullptr) {
      
            front = rear = newNode;
        } else {
          
            rear->next = newNode;
            rear = newNode;
        }
        cout << value << " enqueued to queue." << endl;
    }

    
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }

     
        Node* temp = front;
        front = front->next;

        
        if (front == nullptr) {
            rear = nullptr;
        }

        cout << temp->data << " dequeued from queue." << endl;
        delete temp; 
    }

    
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty. Nothing to peek." << endl;
            return -1; 
        }
        return front->data;
    }

  
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

int main() {
    Queue q;
    int choice, value;

    do {
      
        cout << "\n----- Queue Menu -----\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Peek\n";
        cout << "4. Check if Queue is Empty\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        
        switch (choice) {
        case 1:
            
            cout << "Enter value to enqueue: ";
            cin >> value;
            q.enqueue(value);
            break;

        case 2:
           
            q.dequeue();
            break;

        case 3:
            
            value = q.peek();
            if (value != -1)
                cout << "Front element is: " << value << endl;
            break;

        case 4:
           
            if (q.isEmpty()) {
                cout << "Queue is empty." << endl;
            } else {
                cout << "Queue is not empty." << endl;
            }
            break;

        case 5:
            
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice! Please choose again." << endl;
        }

    } while (choice != 5);  

    return 0;
}