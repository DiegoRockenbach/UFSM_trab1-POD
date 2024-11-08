#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_BUCKETS 5
#define BUCKET_INTERVAL 100

// Função para gerar valores aleatórios
int* generateValues(int numValues, int maxValue) {
    int* values = (int*)malloc(numValues * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < numValues; i++) {
        values[i] = rand() % (maxValue + 1);
    }
    return values;
}

// Função para distribuir valores nos baldes
void distributeToBuckets(int* values, int numValues, int** buckets, int* bucketSizes) {
    for (int i = 0; i < numValues; i++) {
        int bucketIndex = values[i] / BUCKET_INTERVAL;
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = values[i];
    }
}

// Função genérica de ordenação (Insertion Sort) para ordenar um balde específico
void sortBucket(int* bucket, int size) {
    for (int i = 1; i < size; i++) {
        int key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Função para imprimir os baldes
void printBuckets(int** buckets, int* bucketSizes) {
    for (int i = 0; i < NUM_BUCKETS; i++) {
        printf("\nBUCKET %d (%d-%d):\n", i, i * BUCKET_INTERVAL, (i + 1) * BUCKET_INTERVAL - 1);
        for (int j = 0; j < bucketSizes[i]; j++) {
            printf("[%d] ", buckets[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int numValues = 1000;
    int maxValue = 500;
    int* values = generateValues(numValues, maxValue);

    // Inicializar baldes com memória dinâmica
    int* buckets[NUM_BUCKETS];
    int bucketSizes[NUM_BUCKETS] = {0};
    for (int i = 0; i < NUM_BUCKETS; i++) {
        buckets[i] = (int*)malloc(numValues * sizeof(int));
    }

    // Distribuir valores nos baldes
    distributeToBuckets(values, numValues, buckets, bucketSizes);

    // Imprimir baldes antes da ordenação
    printf("Buckets antes da ordenação:");
    printBuckets(buckets, bucketSizes);

    // Ordenar cada balde individualmente
    for (int i = 0; i < NUM_BUCKETS; i++) {
        sortBucket(buckets[i], bucketSizes[i]);
    }

    // Imprimir baldes após a ordenação
    printf("\nBuckets após a ordenação:");
    printBuckets(buckets, bucketSizes);

    // Liberar memória
    free(values);
    for (int i = 0; i < NUM_BUCKETS; i++) {
        free(buckets[i]);
    }

    return 0;
}
