/*2. Faça uma aplicação que tenha um vetor de 10 valores, gerados randomicamente ou com entrada do usuário. 
Com o vetor preenchido, eles devem gerar uma soma e um produto (resultado de uma multiplicação). Você deve
 usar pelo menos duas threads para cada operação (soma e multiplicação) e utilizar os dados no vetor original.*/

// Compilar => gcc -o thread_ex2_NOTION thread_ex2_NOTION.c -lpthread

//Corrigir -> Você deve
//usar pelo menos duas threads para cada operação

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREAD 2
#define TAM 10

int vetor[10] = {0};
int resultado_soma = 0;
int resultado_mul = 1;
int parte = 0;

void* inputValor(void* param){
    for(int i = 0; i < 10; i++){
        printf("Digite o %do valor: \n", i+1);
        scanf("%d", &vetor[i]);
    }
}

void* soma(void* param){

    int tid = parte++;
    int start = tid * (TAM / MAX_THREAD);
    int stop = (tid + 1) * (TAM / MAX_THREAD);

    for(int i = start; i < stop; i++){ 
        resultado_soma += vetor[i];
    }

    // pthread_exit(0);
}

void* multiplicacao(void* param){
    
    parte = 0;
    int tid = parte++;
    int start = tid * (TAM / MAX_THREAD);
    int stop = (tid + 1) * (TAM / MAX_THREAD);

    for(int i = start; i < stop; i++){ 
        resultado_mul *= vetor[i];
    }

}


int main() {

    pthread_t tid_input;
    pthread_t tid[MAX_THREAD]; // criar um vetor de id's de thread

    pthread_create(&tid_input, NULL, inputValor, NULL);
    pthread_join(tid_input, NULL);

    for(int i = 0; i < MAX_THREAD; i++){
        pthread_create(&tid[i], NULL, soma, NULL);
    }

    for(int i = 0; i < MAX_THREAD; i++){
        pthread_join(tid[i], NULL); 
    }

    for(int i = 0; i < MAX_THREAD; i++){
        pthread_create(&tid[i], NULL, multiplicacao, NULL);
    }

    for(int i = 0; i < MAX_THREAD; i++){
        pthread_join(tid[i], NULL); 
    }

    printf("Resultado final soma: %d\n", resultado_soma);
    printf("Resultado final multiplicacao: %d\n", resultado_mul);

    return 0;
}