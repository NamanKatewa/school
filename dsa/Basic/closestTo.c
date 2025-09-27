#include <stdio.h>

int main(){

    int x,y;

    printf("Enter n: ");
    scanf_s("%d",&x);

    printf("Enter m: ");
    scanf_s("%d",&y);

    int res;

    for (int a=0;a<=x;a+=y){
        if(a%y==0){
            res = a;
        }
    }

    printf("%d",res);

    return 0;
}