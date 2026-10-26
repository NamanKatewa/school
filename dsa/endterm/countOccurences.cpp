#include <iostream>
using namespace std;

int firstIndex(int arr[], int n, int key) {
    int low = 0, high = n - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return result;
}

int lastIndex(int arr[], int n, int key) {
    int low = 0, high = n - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            result = mid;
            low = mid + 1;
        } else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return result;
}

int countOccurrences(int arr[], int n, int key) {
    int first = firstIndex(arr, n, key);
    if (first == -1) return 0;
    int last = lastIndex(arr, n, key);
    return last - first + 1;
}

int main() {
    int arr[] = {5, 7, 7, 8, 8, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 8;

    cout << "Count of " << key << " = "
         << countOccurrences(arr, n, key) << endl;

    return 0;
}
