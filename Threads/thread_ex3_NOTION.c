/*
3. Implemente um sistema em que há três sthread que tem a responsabilidade de ler o valor de um sensor e some ao valor 
de uma variável global e em uma variável local. Você deve simular a contagem com operação de incremento simples (+=1 ou ++). 
Print a variável local a cada 1 segundo e incremente a variável a cada 1 segundo. O programa deve chegar ao fim quando a soma 
da variável global chegar a 100. Ao fim, você consegue observar qual condição:
    a. Todas as threads tem o mesmo valor na variável interna?
        R: Sim
    b. O print da variável global segue um incremento linear?
        R 1.: Não
        R 2.: Ela nunca é impressa, pois ocorre uma condição de corrida  (race condition),
           onde as threads modificam uma mesma varíavel, mas sem sincronizar. Dessa forma,
           a contagem da variável global nunca é confiável.
*/

// Compilar => gcc -o thread_ex3_NOTION thread_ex3_NOTION.c -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREAD 3
#define MAX_COUNT 10
int global = 0;

void* sensor (void* param) {
    int local = 0;
    while(global < MAX_COUNT){
        // 1. Jeito certo
        global++;
        local++;
        sleep(1); // Delay 1 seg
        printf("Variável Local na thread %ld: %d | Global: %d\n", (long)param, local, global);
        
        // 2. Jeito errado
        // global++;
        // sleep(1); // Delay 1 seg
        // printf("Variável Local na thread %ld: %d\n", (long)param, local);
        // local++;
    }
    pthread_exit(0); // !perguntar se faz diferença!
}


int main() {

    pthread_t tid[MAX_COUNT];
    
    // Usando long pra evitar alocar memória para o id da thread
    // e também casting. O Tamanho do long (4 bytes) pode ser to tamanho do void 
    for(long i = 0; i < MAX_THREAD; i++){ 
        pthread_create(&tid[i], NULL, sensor, (void*)i); 
    }

    for(int i = 0; i < MAX_THREAD; i++){
        pthread_join(tid[i], NULL);
    }

    printf("Variavel global: %d\n", global);

    return 0;
}