#include <stdio.h>
#include <stdlib.h>    
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 	// para hacer sleep


sem_t S;
int saldo=1000;

//#define TIEMPO 1000000 //en microsegundos 1000000us=1s
#define TIEMPO 500000 //en microsegundos 500000us=1/2s



void* funcion_depositar (void* monto_depositado)
{   
   int monto = (intptr_t)monto_depositado;

   //Se ingresa a la sección crítica
   sem_wait(&S);
   int aux=saldo;

  /********************************
   * simular un tiempo para que ocurra una condición de carrera
   *********************************/
   //inicializar la semilla del generador random:
   int microseconds; srand (time(NULL));

   //generar un numer random entre 1 y 10000:
   microseconds = rand() % 10000 + 1;

   //dormir el thread, simula que esta haciendo alguna tarea
   usleep(microseconds);
   /****************************
   * fin simular un tiempo
   ******************************/

   aux=aux+monto;
   saldo=aux;
   //Se sale de la sección crítica
   sem_post(&S);

   pthread_exit(NULL);
}


int main ()
{
   pthread_t T1;
   pthread_t T2;

   int res = sem_init(&S, 0, 1);

   //////////////////////////////////////////////////////////////////////
   // lanzamiento de los threads
   //////////////////////////////////////////////////////////////////////
   
   int rc = pthread_create(&T1,	//identificador unico
                      	NULL,     	//atributos del thread
                      	funcion_depositar, 	//funcion a ejecutar
                      	(void *) 100); //parametros de la funcion a ejecutar, pasado por referencia
   rc = pthread_create(&T2,	//identificador unico
                      	NULL,     	//atributos del thread
                      	funcion_depositar, 	//funcion a ejecutar
                      	(void *) 200); //parametros de la funcion a ejecutar, pasado por referencia
   


   pthread_join(T1 , NULL);
   pthread_join(T2 , NULL);
   	 
   printf("El saldo final es = %d \n", saldo);

   sem_destroy(&S);

   pthread_exit(NULL);
}
