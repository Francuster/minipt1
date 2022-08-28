#include <stdio.h> //libreria estandar input output
#include <unistd.h> // para hacer sleep
#include <time.h> // para inicializar el tiempo
#include <pthread.h>

void* calculo_aritmetico(void* pid){
    //casteamos el parametro de tipo void* al tipo original que nos pasaron, en este caso fue un long (entero de 8 bytes)
    long id = (long) pid;

    
  
    int contador=0;
    while (contador < 2147483647){
        contador=contador+1;
    }

    //el thread imprime lo que le pasaron de parametro
    printf("Thread: fin de ejecucion del thread %ld \n", id);

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
 
    time_t begin = time(NULL);

    create_threads();

    time_t end = time(NULL);
 
    /// calculate elapsed time by finding difference (end - begin)
    printf("The elapsed time is %d seconds", (end - begin));

    return 0;
}