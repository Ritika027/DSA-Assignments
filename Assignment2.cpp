#include <iostream>
#include <vector>

// implementation of stack using linked list 


struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top; 

public:
    
    Stack() {
        top = nullptr;
    }

   
    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }

    
    void push(int value) {
        Node* newNode = new Node(); 
        newNode->data = value;
        newNode->next = top; 
        top = newNode;       
    }

   
    void pop() {
        if (isEmpty()) {
            std::cout << "Stack underflow. Cannot pop from an empty stack.\n";
            return;
        }
        Node* temp = top;    
        top = top->next;
        std::cout << "poped the top element \n" << std :: endl;     
        delete temp;        
    }

    
    int peek() {
        if (isEmpty()) {
            std::cout << "Stack is empty.\n";
            return -1; 
        }
        return top->data;
    }

    int count_elements(){
        int count = 0;
        Node* temp = top;
        while(temp != nullptr){
            count++;
            temp = temp->next;
        }
        return count;
    }

   
    bool isEmpty() {
        return top == nullptr;
    }
    
};

int main(){
    int number;
    Stack stack1;

    do {
        std::cout << "Enter 1 to push onto stack" << std :: endl;
        std::cout << "Enter 2 to pop from stack" << std::endl;
        std::cout << "Enter 3 to peek at top of stack" << std::endl;
        std::cout<< "Enter 4 to check if stack is empty" << std::endl;
        std::cout << "Enter 5 to count elements in stack" << std::endl;
        std::cout << "Enter 0 to exit" << std::endl;
        std::cin >> number;


        switch (number)
        {
        case 1:
            int num;
            std::cout << "Enter a number to push onto stack \n" << std::endl;
            std :: cin >> num;
            stack1.push(num);

            break;
        case 2:
            stack1.pop();
            break;
        case 3:
            std::cout << "Top of stack is: " << stack1.peek() << std:: endl << "\n";
            break;
        case 4:
            std::cout << "Stack is empty: " << std::boolalpha << stack1.isEmpty() << std :: endl<< "\n";
            break;
        case 5:
            std::cout << "length of stack is: " << stack1.count_elements() << std:: endl << "\n";
            break;
        default:
            continue;
        }

    } while (number != 0);
   
    
    return 0;
}