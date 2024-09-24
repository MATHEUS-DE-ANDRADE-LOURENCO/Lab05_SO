#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAMANHO 100  // Tamanho do vetor
#define CONTADOR_THREADS 2  // Número de threads

int vetor[TAMANHO];
int maximos[CONTADOR_THREADS];

void* encontrar_maximo(void* arg) {
    int id_thread = *(int*)arg;
    int inicio = id_thread * (TAMANHO / CONTADOR_THREADS);
    int fim = (id_thread + 1) * (TAMANHO / CONTADOR_THREADS);
    
    int maximo_local = vetor[inicio];
    for (int i = inicio + 1; i < fim; i++) {
        if (vetor[i] > maximo_local) {
            maximo_local = vetor[i];
        }
    }
    maximos[id_thread] = maximo_local;
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    // Inicialização do vetor com valores randômicos
    for (int i = 0; i < TAMANHO; i++) {
        vetor[i] = rand() % 1000;  // Valores entre 0 e 999
    }

    // Criação das threads
    pthread_t threads[CONTADOR_THREADS];
    int ids_threads[CONTADOR_THREADS];

    for (int i = 0; i < CONTADOR_THREADS; i++) {
        ids_threads[i] = i;
        pthread_create(&threads[i], NULL, encontrar_maximo, (void*)&ids_threads[i]);
    }

    // Esperar as threads terminarem
    for (int i = 0; i < CONTADOR_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Encontrar o maior valor entre os resultados das threads
    int maximo_geral = maximos[0];
    for (int i = 1; i < CONTADOR_THREADS; i++) {
        if (maximos[i] > maximo_geral) {
            maximo_geral = maximos[i];
        }
    }

    // Exibir o vetor e o maior valor encontrado
    printf("Vetor: ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\nMaior valor: %d\n", maximo_geral);

    return 0;
}
