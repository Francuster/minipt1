#include <stdio.h>




void calculo(){
    int contador=0;
    while (contador < 2147483647){
        contador=contador+1;
    }
    
}

int main(){
    printf("inicio calculo");
    calculo();
    calculo();
    calculo();
    calculo();

    printf("\n Press enter to continue:");
    int c = getchar();


    printf("\nfin calculo");

    return 0;

}