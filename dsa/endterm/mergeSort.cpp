#include <iostream>
using namespace std;

void merge(int arr[], int low, int mid, int high){
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *l = new int[n1];
    int *r = new int[n2];

    for (int i = 0; i < n1;i++){
        l[i] = arr[low + i];
    }

    for (int j = 0; j < n2;j++){
        r[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j<n2){
        if(l[i]<=r[j]){
            arr[k++] = l[i++];
        }
        else{
            arr[k++] = r[j++];
        }
    }

    while(i<n1){
        arr[k++] = l[i++];
    }

    while(j<n2){
        arr[k++] = r[j++];
    }

    delete[] l;
    delete[] r;
}


void mergeSort(int arr[], int low, int high){
    if(low>=high){
        return;
    }
    int mid = low + ((high - low) / 2);

    mergeSort(arr, low, mid);
    mergeSort(arr, mid+1, high);
    merge(arr, low, mid, high);
}

int main(){
    
    int arr[] = {38, 27, 43, 3, 9, 82, 10};

    mergeSort(arr, 0, 6);

    for(int x: arr){
        cout << x << " ";
    }
}