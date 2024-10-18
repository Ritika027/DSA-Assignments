#include <iostream>
#include <string>

struct Stu{
    int roll_no;
    std::string name;
    float sgpa;
};

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
};

void display(Stu* students[], int n){

    for (int i = 0; i<n; i++){
        std::cout << "student"<< i+1<< "\n";
        std::cout << "roll no "<< students[i]->roll_no;
        std::cout << " name "<< students[i]-> name;
        std::cout << " sgpa "<<students[i]->sgpa<< "\n\n";
    }

}
void display10(Stu* students[], int n){

    for (int i = 0; i<10; i++){
        std::cout << "student"<< i+1<< "\n";
        std::cout << "roll no "<< students[i]->roll_no;
        std::cout << " name "<< students[i]-> name;
        std::cout << " sgpa "<<students[i]->sgpa<< "\n\n";
    }

}
void sort(Stu* arr[], int n){
    for (int i = 0; i < n-1; i++) {
        for(int j = 0;j< n-i-1;j++){
            if(arr[j]->roll_no > arr[j+1]->roll_no){
                swap(arr[j]->roll_no,arr[j+1]->roll_no);
            }
        }

    }

}

void insertion_sort(Stu* arr[], int n){
    for(int i=0; i< n;i++){
        std :: string key = arr[i]->name;
        int j = i-1;
        while (j >= 0 && key < arr[j]->name){
            arr[j+1]->name = arr[j]->name;
            j = j-1;
        }
        arr[j+1]->name = key;
    }
}

int partion(Stu* arr[], int start, int end){
    float pivot = arr[end]->sgpa;
    int i = start -1;

    for (int j = start; j<=end; j++){
        if (arr[j]->sgpa < pivot){
            i++;
            int temp = arr[i]->sgpa;
            arr[i]->sgpa = arr[j]->sgpa;
            arr[j]->sgpa = temp;
        }
    }
    float temp = arr[i+1]->sgpa;
    arr[i+1]->sgpa = arr[end]->sgpa;
    arr[end]->sgpa = temp;
    return i+1;
}

void quick_sort(Stu* arr[], int start, int end){
    if (start < end){
        int pivot = partion(arr , start, end);
        quick_sort(arr, start, pivot-1);
        quick_sort(arr, pivot+1, end);
    }
}

int main (){
    int n;
    std::cout<< "enter the number of students you want to store: ";
    std::cin >> n;

    Stu* students[n];
    for(int i =0; i<n ; i++){
        students[i] = new Stu();
        std::cout<< "enter details for student "<< i+1 <<":\n";
        std::cout<< "roll no: ";
        std::cin >> students[i]->roll_no;

        std::cout<< "Name: ";
        std::cin >> students[i]->name;

        std::cout<< "SGPA: ";
        std::cin >> students[i]->sgpa;


    };
    // std::cout << "\n student details: (unsorted) \n";
    // display(students, n);


    // std::cout << "\n student details: (sorted) \n";
    
    std::cout << "\n student details: (top 10 students) \n";
    // insertion_sort(students, n);
    // sort(students,n);
    quick_sort(students, 0, n-1);
    display10(students,n);

return 0;
}
