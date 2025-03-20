/* Desenvolver uma aplicação de leia uma entrada do teclado, some com uma constante e imprima 
na tela o dado resultante da soma. Divida as tarefas em threads usando a biblioteca pthread (preferencialmente).*/

// Compilar => gcc -o thread_ex1_NOTION thread_ex1_NOTION.c -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int entrada = 0;

// void pointers => Não estão associados a nenhum tipo de dado.
void* entradaTeclado(void* param) {
    printf("Escreva algo: \n");
    scanf("%d", &entrada);
}

void* soma(void* param) {
    entrada = entrada + 10;
}

void* imprimirResultado(void* param) {
    printf("O resultado da operação é: %d\n", entrada);
}

int main() {
   
    pthread_t tid_entrada, tid_soma, tid_print; // Id's das threads
    // pthread_attr_t attr; // Atributos da thread, usados para executar a thread com configurações diferentes da padrão
    // pthread_attr_init(&attr); // inicializar os atributos, mas como não usamos nenhum, da pra ignorar

    // Criar as threads, realizar create e depois join por motivo de dependêcia
    pthread_create(&tid_entrada, NULL, entradaTeclado, NULL);
    pthread_join(tid_entrada, NULL); // espera a thread terminar

    pthread_create(&tid_soma, NULL, soma, NULL);
    pthread_join(tid_soma, NULL);

    pthread_create(&tid_print, NULL, imprimirResultado, NULL);
    pthread_join(tid_print, NULL);

    printf("Fim do programa\n");

    return 0;
}