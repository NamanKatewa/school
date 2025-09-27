#include <stdio.h>

int main(){

    int a,b,n;

    printf("Enter the first term: ");
    scanf_s("%d",&a);

    printf("Enter the second term: ");
    scanf_s("%d",&b);

    printf("Enter the term to find: ");
    scanf_s("%d",&n);

    int d = b-a;

    printf("The %dth term of the A.P. is %d",n, a+((n-1)*d));

    return 0;
}