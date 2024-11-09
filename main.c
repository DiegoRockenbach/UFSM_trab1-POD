#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_BUCKETS 5

int* generateValues(int numValues, int maxValue) {
  
  int* values = (int*)malloc(numValues * sizeof(int));
  
  srand(time(NULL));
  
  for (int i = 0; i < numValues; i++) {
      values[i] = rand() % (maxValue + 1);
  }

  return values;
}

void distributeBetweenBuckets(int* values, int numValues, int** buckets, int* bucketSizes, int maxValue) {
  
  int bucketIndex;

  for (int i = 0; i < numValues; i++) {
    bucketIndex = (values[i] * NUM_BUCKETS) / (maxValue + 1);
    buckets[bucketIndex][bucketSizes[bucketIndex]] = values[i];
    bucketSizes[bucketIndex]++;
  }
}

void insertionSort(int *bucket, int size){
  
  int i;
  
  for (i = 1; i < size; i++) {
    int key = bucket[i];
    int j = i - 1;

    while (j >= 0 && bucket[j] > key) {
        bucket[j + 1] = bucket[j];
        j = j - 1;
    }
    bucket[j + 1] = key;
  }
}

void bubbleSort(int *bucket, int size){

  int i, j, temp;

  for (i = 0; i < size - 1; i++) {
    for (j = 0; j < size - i - 1; j++) {
      if (bucket[j] > bucket[j + 1]) {
        temp = bucket[j];
        bucket[j] = bucket[j + 1];
        bucket[j + 1] = temp;
      }
    }
  }
}

void cocktailShakerSort(int *bucket, int size){

  int i, temp, swapped = 1, start = 0, end = size - 1;

  while (swapped) {
    swapped = 0;

    for (i = start; i < end; i++) {
      if (bucket[i] > bucket[i + 1]) {
        temp = bucket[i];
        bucket[i] = bucket[i + 1];
        bucket[i + 1] = temp;
        swapped = 1;
      }
    }

    if (!swapped) break;
    end--;

    for (i = end - 1; i >= start; i--) {
      if (bucket[i] > bucket[i + 1]) {
        temp = bucket[i];
        bucket[i] = bucket[i + 1];
        bucket[i + 1] = temp;
        swapped = 1;
      }
    }

    start++;
  }

}

void quickSort(int *bucket, int low, int high){

  int i, temp, pivot, pi;

  if (low < high) {
    pivot = bucket[high];
    i = low - 1;

    for (int j = low; j < high; j++) {
        if (bucket[j] < pivot) {
            i++;
            temp = bucket[i];
            bucket[i] = bucket[j];
            bucket[j] = temp;
        }
    }
    temp = bucket[i + 1];
    bucket[i + 1] = bucket[high];
    bucket[high] = temp;

    pi = i + 1;

    quickSort(bucket, low, pi - 1);
    quickSort(bucket, pi + 1, high);
  }

}

void printaBuckets(int** buckets, int* bucketSizes){

  int i, j;

  for (i = 0; i < NUM_BUCKETS; i++){
    printf("\nBUCKET %d:\n", i);
    for (j = 0; j < bucketSizes[i]; j++){
      printf("[%d]; ", buckets[i][j]);
    }
  }
}

int main(){

  int i, numValues = 10000, maxValue = 10000, bucketSizes[NUM_BUCKETS] = {0};
  int *values, *buckets[NUM_BUCKETS];
  clock_t start, end;

  values = generateValues(numValues, maxValue);

  for (i = 0; i < NUM_BUCKETS; i++) {
    buckets[i] = (int*)malloc(numValues * sizeof(int));
  }

  distributeBetweenBuckets(values, numValues, buckets, bucketSizes, maxValue);

  // Buckets não-ordenados
  /* printaBuckets(buckets, bucketSizes); */

  // Algoritmos de ordenação:

  start = clock();
  
/*   for (i = 0; i < NUM_BUCKETS; i++){
    insertionSort(buckets[i], bucketSizes[i]);
  } */

/*   for (i = 0; i < NUM_BUCKETS; i++){
    bubbleSort(buckets[i], bucketSizes[i]);
  } */

/*   for (i = 0; i < NUM_BUCKETS; i++){
    cocktailShakerSort(buckets[i], bucketSizes[i]);
  } */

/*   for (i = 0; i < NUM_BUCKETS; i++){
    quickSort(buckets[i], 0, bucketSizes[i]);
  } */

  end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("\nTempo execucao: %f segundos\n", time_taken);

  // Buckets ordenados
  /* printaBuckets(buckets, bucketSizes); */

  // Liberar memória
  free(values);
  for (int i = 0; i < NUM_BUCKETS; i++) {
    free(buckets[i]);
  }

  return 0;
}

