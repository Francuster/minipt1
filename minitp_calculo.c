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
    
    time_t begin = time(NULL);


    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();

    time_t end = time(NULL);
 
   /// calculate elapsed time by finding difference (end - begin)
    printf("The elapsed time is %li seconds", (end - begin));

    return 0;
}