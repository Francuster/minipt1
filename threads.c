#include <stdio.h> //libreria estandar input output
#include <unistd.h> // para hacer sleep
#include <time.h> // para inicializar el tiempo

void calculo_aritmetico(){
    int contador=0;
    while (contador < 2147483647){
        contador=contador+1;
    }
}

int main(){
    // to store the execution time of code
    double time_spent = 0.0;
 
    clock_t begin = clock();

    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();

    clock_t end = clock();
 
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
    
    return 0;
}