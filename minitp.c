#include <stdio.h>




void calculo(){
    int contador=0;
    while (contador < 2147483647){
        contador=contador+1;
    }

    printf("\nenter value:");
    int c = getchar();

    printf( "\nYou entered: ");
    putchar( c );
}

void main(){
    printf("inicio calculo");
    calculo();
    printf("\nfin calculo");

}