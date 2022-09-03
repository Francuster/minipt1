#include <stdio.h>
#include <stdlib.h>    


#include <pthread.h>
#include <semaphore.h>


sem_t sem_equipo_a;
sem_t sem_equipo_b;
sem_t sem_equipo_c;
sem_t sem_ganador;

int ganador = 0;



void calculo_aritmetico(){
    int value = 0;
    while (value != 2147483647){
        value++;
    }
}

void elejir_ganador(int numeroEquipo){

    sem_wait(&sem_ganador);
    if(ganador == 0){
        ganador = numeroEquipo;
    }
    sem_post(&sem_ganador);
}

void corre_equipo_a(){

    int counter = 0;

    while(counter =! 2){
        sem_wait(&sem_equipo_a);
        calculo_aritmetico();
        sem_post(&sem_equipo_a);
    }    
    elejir_ganador(1);

    pthread_exit(NULL);

}

void corre_equipo_b(){

    int counter = 0;

    while(counter =! 2){
        sem_wait(&sem_equipo_b);
        calculo_aritmetico();
        sem_post(&sem_equipo_b);
    } 
    elejir_ganador(2);

    pthread_exit(NULL);

}

void corre_equipo_c(){

    int counter = 0;

    while(counter =! 2){
        sem_wait(&sem_equipo_c);
        calculo_aritmetico();
        sem_post(&sem_equipo_c);
    }    
    elejir_ganador(3);

    pthread_exit(NULL);

}

void main(){

    //inicializar semaforos
    sem_init(&sem_equipo_a, 0, 1);
    sem_init(&sem_equipo_b, 0, 1);
    sem_init(&sem_equipo_c, 0, 1);
    sem_init(&sem_ganador, 0, 1);


    //declarar threads
    pthread_t thread_a;
    pthread_t thread_b;
    pthread_t thread_c;

    //inicializar threads
    pthread_create(&thread_a, NULL, corre_equipo_a, NULL);
    pthread_create(&thread_b, NULL, corre_equipo_b, NULL);
    pthread_create(&thread_c, NULL, corre_equipo_c, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);

    printf("El ganador fue el equipo %d", ganador);
    printf("\n");


    //eliminar threads
    sem_destroy(&sem_equipo_a);
    sem_destroy(&sem_equipo_b);
    sem_destroy(&sem_equipo_c);
    sem_destroy(&sem_ganador);



}