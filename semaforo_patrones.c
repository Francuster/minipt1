#include <stdio.h>
#include <stdlib.h>    


#include <pthread.h>
#include <semaphore.h>


#include <unistd.h>     // para hacer sleep

sem_t A;
sem_t B;

int iterations = 2;

void funcion_a(){

    int counter = 0;

    while(1){
        sem_wait(&A);
        printf("A");
        sem_post(&B);
        if(iterations == counter){
            break;
        }
        counter++;
    }

    pthread_exit(NULL);
}

void funcion_b(){

    int counter = 0;

    while(1){
        sem_wait(&B);
        printf("B");
        sem_post(&A);
        if(iterations == counter){
            break;
        }
        counter++;

    }
    
    pthread_exit(NULL);

}

void main(){

    //inicializar semaforos
    sem_init(&A, 0, 1);
    sem_init(&B, 0, 0);

    pthread_t thread_a; 
    pthread_t thread_b;
    //crear threads
    pthread_create(&thread_a, NULL, funcion_a, NULL);
    pthread_create(&thread_b, NULL, funcion_b, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);


    //eliminar semaforo
    sem_destroy(&A);
    sem_destroy(&B);
}