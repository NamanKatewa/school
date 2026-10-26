#include <iostream>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSortOnePass(int arr[], int n){
    for (int i = 0; i < n - 1;i++){
        if(arr[i]>arr[i+1]){
            swap(arr[i], arr[i + 1]);
        }
    }
}

int main(){

    int arr[] = {5, 3, 8, 4, 2};
    cout << "Initial Array: ";
    for (int x:arr){
        cout << x << " ";
    }
    cout << endl;
    bubbleSortOnePass(arr, 5);
    cout << "After Single Bubble Sort Pass: ";
    for (int x:arr){
        cout << x << " ";
    }

    return 0;
}