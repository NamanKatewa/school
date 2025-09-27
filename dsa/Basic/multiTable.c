#include <stdio.h>

int main(){

    int tableOf,tableTill;

    printf("Enter the number for which you want the table: ");
    scanf_s("%d", &tableOf);
    
    printf("Enter the number till where you want the table: ");
    scanf_s("%d", &tableTill);

    for (int x=1; x<=tableTill;x++){
        printf("%d X %d = %d\n",tableOf,x, tableOf*x);
    }


    return 0;
}