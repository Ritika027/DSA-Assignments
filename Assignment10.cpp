#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    char division;
    string address;

    void inputStudentData() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Division: ";
        cin >> division;
        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);
    }

    void displayStudentData() {
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

void addStudent() {
    Student student;
    ofstream file("student.dat", ios::binary | ios::app);

    student.inputStudentData();
    file.write((char*)&student, sizeof(student));
    file.close();
}

void displayStudent(int roll) {
    Student student;
    ifstream file("student.dat", ios::binary);
    bool found = false;

    while (file.read((char*)&student, sizeof(student))) {
        if (student.rollNo == roll) {
            student.displayStudentData();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Record not found." << endl;
    }
    file.close();
}

void deleteStudent(int roll) {
    Student student;
    ifstream file("student.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);
    bool found = false;

    while (file.read((char*)&student, sizeof(student))) {
        if (student.rollNo == roll) {
            found = true;
        } else {
            tempFile.write((char*)&student, sizeof(student));
        }
    }

    file.close();
    tempFile.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (found) {
        cout << "Record deleted successfully." << endl;
    } else {
        cout << "Record not found." << endl;
    }
}

int main() {
    int choice, roll;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to search: ";
                cin >> roll;
                displayStudent(roll);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
