#include <stdio.h>

int main(){

    int num,sum=0;

    printf("Enter num: ");
    scanf_s("%d",&num);

    int temp = num;

    while(num>0){
        sum+=num%10;
        num=num/10;
    }

    printf("The sum of digits of %d is %d",temp,sum);

    return 0;
}