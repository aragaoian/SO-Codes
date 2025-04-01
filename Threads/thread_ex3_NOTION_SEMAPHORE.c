// Compilar => gcc -o thread_ex3_NOTION_SEMAPHORE thread_ex3_NOTION_SEMAPHORE.c -lpthread
// Ex 3 com semaphore para resolver problema de sincronização

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_THREAD 3
#define MAX_COUNT 10
int global = 0;
sem_t semaphore;

void* sensor (void* param) {
    int local = 0;
    while(1){
        sleep(1);
        sem_wait(&semaphore); // mesmo que 'lock' do mutex
        if(global >= MAX_COUNT){
            sem_post(&semaphore);
            break;
        }
        global++;
        local++;
        printf("Variável Local na thread %ld: %d | Global: %d\n", (long)param, local, global);
        sem_post(&semaphore); // mesmo que 'unlock' do mutex
    }
    pthread_exit(0); 
}


int main() {

    pthread_t tid[MAX_COUNT];
    sem_init(&semaphore, 0, 1);

    for(long i = 0; i < MAX_THREAD; i++){ 
        pthread_create(&tid[i], NULL, sensor, (void*)i); 
    }

    for(int i = 0; i < MAX_THREAD; i++){
        pthread_join(tid[i], NULL);
    }

    printf("Variavel global: %d\n", global);
    sem_destroy(&semaphore);

    return 0;
}