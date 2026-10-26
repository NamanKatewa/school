#include<iostream>
using namespace std;

int sum_array(int arr[], int n){
    int sum = 0;

    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int main(){

    int arr[] = {3, 4, 2};
    int res = sum_array(arr, 3);
    cout << res << endl;

    return 0;
}