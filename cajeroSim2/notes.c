#include <stdio.h>

int sumCopy(int x, int y){
    // passing by copy
    return x += y;
}

int sumReference(int *x, int y){
    // passing by reference or memory direction
    return *x += y;
}
int main(){

    int num = 15;
    printf("\nnum initially values 15\n\n");

    printf("Sum by Copy: %d\n", sumCopy(num, 15));
    printf("num variable: %d is not modified\n", num);

    printf("Sum by Reference: %d\n", sumReference(&num, 20));
    printf("num variable: %d is modified\n", num);

   return 0;
}