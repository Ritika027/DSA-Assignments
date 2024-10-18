#include <iostream>
#include <vector>
using namespace std;

class HeapSort {
private:
    vector<int> heap;

    void heapifyMax(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] > heap[largest])
            largest = left;

        if (right < n && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyMax(n, largest);
        }
    }

    void heapifyMin(int n, int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] < heap[smallest])
            smallest = left;

        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyMin(n, smallest);
        }
    }

public:
    void insertValue(int value) {
        heap.push_back(value);
    }

    void maxHeapSort() {
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyMax(n, i);

        for (int i = n - 1; i >= 0; i--) {
            swap(heap[0], heap[i]);
            heapifyMax(i, 0);
        }
    }

    void minHeapSort() {
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyMin(n, i);

        for (int i = n - 1; i >= 0; i--) {
            swap(heap[0], heap[i]);
            heapifyMin(i, 0);
        }
    }

    void displayHeap() {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    HeapSort hs;
    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Value\n";
        cout << "2. Sort Using Max Heap (Descending Order)\n";
        cout << "3. Sort Using Min Heap (Ascending Order)\n";
        cout << "4. Display Sorted Values\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                hs.insertValue(value);
                break;
            case 2:
                hs.maxHeapSort();
                cout << "Heap sorted using Max Heap (Descending Order).\n";
                break;
            case 3:
                hs.minHeapSort();
                cout << "Heap sorted using Min Heap (Ascending Order).\n";
                break;
            case 4:
                cout << "Sorted Values: ";
                hs.displayHeap();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
