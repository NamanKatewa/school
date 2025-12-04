#include<iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {

        int mIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[mIndex]) {
                mIndex = j;
            }
        }

        if (mIndex != i) {
            int temp = arr[i];
            arr[i] = arr[mIndex];
            arr[mIndex] = temp;
        }
    }
}

int main() {
    int n;
    cout << "Number of elements: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid size\n";
        return 1;
    }

    int *arr = new int[n];
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    selectionSort(arr, n);

    cout << "Sorted: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    delete[] arr;
    return 0;
}