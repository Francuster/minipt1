#include <stdio.h>
#include <stdlib.h>    


#include <pthread.h>
#include <semaphore.h>


#include <unistd.h>     // para hacer sleep


sem_t A;
sem_t B;


//#define TIEMPO 1000000 //en microsegundos 1000000us=1s
#define TIEMPO 500000 //en microsegundos 500000us=1/2s
#define CANTIDAD_PRINTS 4 //cuantas veces quiero que el thread imprima su nombre




void* funcionA (void* parametro)
{   
   //tomar los datos del thread 
   char nombreProceso = *(char *) parametro;


   int i;
   for(i=0; i < CANTIDAD_PRINTS; i++ ){
       sem_wait(&A);
   
       //imprimir mi nombre de proceso y dormir 1 segundo para que no sea muy rapido
       printf("Hola soy el proceso = %c \n", nombreProceso);
       usleep(TIEMPO);
   
       sem_post(&B);
   }      
   pthread_exit(NULL);
}




void* funcionB (void* parametro)
{   
   //tomar los datos del thread 
   char nombreProceso = *(char *) parametro;


   int i;
   for(i=0; i < CANTIDAD_PRINTS; i++ ){
       sem_wait(&B);
   
       //imprimir mi nombre de proceso y dormir 1 segundo para que no sea muy rapido
       printf("Hola soy el proceso = %c \n", nombreProceso);
       usleep(TIEMPO);
   
       sem_post(&A);
   }      
   pthread_exit(NULL);
}




int main ()
{
   pthread_t threadA;
   pthread_t threadB;


   //inicializo el semaforo A 
   int res = sem_init(&A, //se inicializa el semaforo pasado por referencia
             0,//tipo de semaforo, si es 0 el semaforo es local para el proceso actual
                     //en otro caso el semaforo puede ser compartido entre procesos
             1);//valor inicial para el semaforo 
   if (res != 0) {
        perror("Inicializacion del semaforo ha fallado :(");
        exit(EXIT_FAILURE);
   }




   //inicializo el semaforo B 
   res = sem_init(&B, //se inicializa el semaforo pasado por referencia
             0,//tipo de semaforo, si es 0 el semaforo es local para el proceso actual
                     //en otro caso el semaforo puede ser compartido entre procesos
             0);//valor inicial para el semaforo 
   if (res != 0) {
        perror("Inicializacion del semaforo ha fallado :(");
        exit(EXIT_FAILURE);
   }


   //////////////////////////////////////////////////////////////////////
   // lanzamiento de los threads
   //////////////////////////////////////////////////////////////////////
   
   //lanzo primero el thread B
   //recordar que quiero la secuencia AB AB AB AB....
   char nombreProcesoB='B';
   int rc = pthread_create(&threadB,    //identificador unico
                          NULL,         //atributos del thread
                          funcionB,     //funcion a ejecutar 
                          (void *) &nombreProcesoB); //parametros de la funcion a ejecutar, pasado por referencia
    if (rc){
         printf("Error: no se puede crear el thread, %d \n", rc);


         exit(-1);
    }
   
   //lanzo el thread A
   char nombreProcesoA='A';
   rc = pthread_create(&threadA,    //identificador unico
                          NULL,         //atributos del thread
                          funcionA,     //funcion a ejecutar 
                          (void *) &nombreProcesoA); //parametros de la funcion a ejecutar, pasado por referencia
    if (rc){
         printf("Error: no se puede crear el thread, %d \n", rc);


         exit(-1);
    }
   


   //antes de borrar los semaforos, espero que los threads terminen 
   pthread_join(threadA , NULL);
   pthread_join(threadB , NULL);
        
   
   //destruir los semaforos
   sem_destroy(&A);
   sem_destroy(&B);


   pthread_exit(NULL);
}


//Para compilar:   gcc sincronizacion_ej1.c -o sincronizacion_ej1 -lpthread
//Para ejecutar:   ./sincronizacion_ej1