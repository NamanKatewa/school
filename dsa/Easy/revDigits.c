#include <stdio.h>

int main(){

    int num,rev=0,temp;

    printf("Enter num: ");
    scanf_s("%d",&num);

    temp = num;

    while(num>0){
        rev= (rev*10) + (num%10);
        num=num/10;
    }

    printf("%d reversed is %d",temp,rev);

    return 0;
}