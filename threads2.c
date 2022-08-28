#include <stdio.h> //libreria estandar input output
#include <unistd.h> // para hacer sleep
#include <time.h> // para inicializar el tiempo
#include <pthread.h>

void* calculo_aritmetico(void* pid){
    //casteamos el parametro de tipo void* al tipo original que nos pasaron, en este caso fue un long (entero de 8 bytes)
    long id = (long) pid;

    //el thread imprime lo que le pasaron de parametro
    printf("Thread: hola, mi proceso principal tiene pid %ld \n", id);
  
    int contador=0;
    while (contador < 2147483647){
        contador=contador+1;
    }

    pthread_exit(NULL);//necesario para terminar el thread

}

void create_threads(){
    int thread_count = 5;
    pthread_t   threads[thread_count]; 
    int i;
    for( i=0; i < thread_count; i++ ){
        printf("main() : creando thread %d \n", i);

        int out = pthread_create(&threads[i],    //identificador unico
                            NULL,        //atributos del thread
                            calculo_aritmetico,    //funcion a ejecutar 
                            (void *)i);    //parametros de la funcion a ejecutar, pasado por referencia
    }

    //esperamos a que el thread termine para salir del programa principal
   //se pasa el trhead de parametro a la funcion pthread_join
   
   for (int i = 0; i < thread_count; i++)
       pthread_join(threads[i], NULL);

}


int main(){
    // to store the execution time of code
    double time_spent = 0.0;
 
    clock_t begin = clock();

    create_threads();

    clock_t end = clock();
 
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);

    return 0;
}