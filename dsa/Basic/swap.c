#include <stdio.h>

int main(){

    int x,y;

    printf("Enter num 1: ");
    scanf_s("%d",&x);
    printf("Enter num 2: ");
    scanf_s("%d",&y);

    printf("Original values %d %d\n",x,y);

    int temp = x;
    x=y;
    y=temp;

    printf("Swapped values %d <-> %d",x,y);

    return 0;
}