#include <iostream>
using namespace std;

int linearSearch(int arr[], int key,int n){
    int comparisons = 0;

    for (int i = 0; i < n;i++){
        comparisons++;
        if(arr[i] == key){
            break;
        }
    }

        return comparisons;
}

int binarySearch(int arr[], int key, int low, int high){
    if(low>high){
        return 0;
    }

    int mid = low + (high - low) / 2;

    if(arr[mid] == key){
        return 1;
    }else{
        if(arr[mid]<key){
            return 1 + binarySearch(arr, key, mid + 1, high);
        }else{
            return 1 + binarySearch(arr, key, low, mid-1);
        }
    }
}

int main(){

    int arr[] = {5,9,14,18,23,29,35,40,46,53,60,66,70,72,73,81};
    int key = 73;

    int linRes = linearSearch(arr, key, 16);
    int binRes = binarySearch(arr, key, 0, 15);

    cout << "Linear Comparisons: " << linRes << endl;
    cout << "Binary Comparisons: " << binRes << endl;

    return 0;
}