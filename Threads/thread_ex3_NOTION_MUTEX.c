// Compilar => gcc -o thread_ex3_NOTION_MUTEX thread_ex3_NOTION_MUTEX.c -lpthread
// Ex 3 com mutex para resolver problema de sincronização

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREAD 3
#define MAX_COUNT 10
int global = 0;
pthread_mutex_t mutex;

// pthread_mutex_init
// pthread_mutex_lock
// pthread_mutex_unlock
// pthread_attr_destroy

void* sensor (void* param) {
    int local = 0;
    while(1){
        sleep(1);
        pthread_mutex_lock(&mutex);
        if(global >= MAX_COUNT){
            pthread_mutex_unlock(&mutex);
            break;
        }
        global++;
        local++;
        printf("Variável Local na thread %ld: %d | Global: %d\n", (long)param, local, global);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0); 
}


int main() {

    pthread_t tid[MAX_COUNT];
    pthread_mutex_init(&mutex, NULL);
    
    for(long i = 0; i < MAX_THREAD; i++){ 
        pthread_create(&tid[i], NULL, sensor, (void*)i); 
    }

    for(int i = 0; i < MAX_THREAD; i++){
        pthread_join(tid[i], NULL);
    }

    printf("Variavel global: %d\n", global);
    pthread_mutex_destroy(&mutex);

    return 0;
}