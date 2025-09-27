#include <stdio.h>

int main(){

    int num,sum=0;

    printf("Enter the num: ");
    scanf_s("%d",&num);

    for (int x=1;x<=num;x++){
        sum+=x;
    }

    printf("The sum of first %d natural numbers is %d",num,sum);

    return 0;
}