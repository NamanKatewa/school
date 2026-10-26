#include<iostream>
using namespace std;

void print_elem(int arr[], int n){

    for (int i = 0; i < n; i++){
        cout<< arr[i]<< " ";
    }

}

int main(){

    int arr[] = {3, 4, 2};
    print_elem(arr, 3);

    return 0;
}