//incluimos las librerias para
#include <stdio.h>   //standard input/output: printf
#include <pthread.h> //threads: declarar, ejecutar
#include <unistd.h>  //operaciones sobre procesos: getpid (obtener id del proceso)



//declaramos la funcion a ser ejecutada por el thread
//observar que el tipo void*, en C es el tipo de datos mas generico
//y es la forma que debe tener una funcion para threads, lo mas generico posible
void* funcion_para_el_thread (void* parametro){
 
  //casteamos el parametro de tipo void* al tipo original que nos pasaron, en este caso fue un long (entero de 8 bytes)
  long id = (long) parametro;

  //el thread imprime lo que le pasaron de parametro
  printf("Thread: hola, mi proceso principal tiene pid %ld \n", id);

  //hacemos una pausa para poder observar por el htop
  printf("Thread: presione enter para continuar \n");
  getchar();

  pthread_exit(NULL);//necesario para terminar el thread
}


void main() {
   //como proceso principal obtenemos nuestro identificador de proceso
   //observar que devuelve un dato de tipo long (entero de 8 bytes)
   long pid = getpid();
   //lo imprimimos
   printf("Proceso principal: mi pid es %ld \n", pid);

   //advertimos al usuario que esta a punto de crear un thread
   printf("Proceso principal: Ud. va a crear un Thread. Presione enter para continuar \n");
   getchar();
 pthread_t t1; //declaramos el thread
   int out = pthread_create(&t1,	//pasamos el thread por referencia (observar el ampersand &)
                      	NULL, 	//atributos del thread (no pasamos nada)
                      	funcion_para_el_thread,	//funcion a ejecutar  por el thread
                      	(void*) pid);	//parametros de la funcion a ejecutar, pasado por referencia

   //esperamos a que el thread termine para salir del programa principal
   //se pasa el trhead de parametro a la funcion pthread_join
   pthread_join(t1 , NULL);

   //fin del proceso principal
   printf("Proceso principal: Fin \n");
}
