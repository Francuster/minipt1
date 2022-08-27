#include <stdio.h> //libreria estandar input output
#include <unistd.h> // para hacer sleep
#include <time.h> // para inicializar el tiempo
#include <pthread.h>

void calculo_aritmetico(){
    int contador=0;
    while (contador < 2147483647){
        contador=contador+1;
    }
}

create_thread(){
    int iterations = 5;
    pthread_t   threads[iterations]; 
    int i;
    for( i=0; i < iterations; i++ ){
        printf("main() : creando thread %d \n", i);

        int out = pthread_create(&threads[i],    //identificador unico
                            NULL,        //atributos del thread
                            calculo_aritmetico(),    //funcion a ejecutar 
                            (void *)i);    //parametros de la funcion a ejecutar, pasado por referencia
    }

}


int main(){
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    calculo_aritmetico();
    return 0;
}