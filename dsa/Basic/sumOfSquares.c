#include <stdio.h>
#include <math.h>

int main(){

    int num,sum=0;

    printf("Enter the num: ");
    scanf_s("%d",&num);

    for (int x=1;x<=num;x++){
        sum+=pow(x,2);
    }

    printf("The sum of squares of first %d natural numbers is %d",num,sum);

    return 0;
}