#include <iostream>
using namespace std;

int find_max(int arr[], int n){
    int max = arr[0];

    for (int i = 0; i < n; i++){
        if(arr[i]>max){
            max = arr[i];
        }
    }

        return max;
}

int main(){

    int arr[] = {10,20,15,14,75,35,95,0,11};
    int res = find_max(arr,9);
    cout << res << endl;

    return 0;
}