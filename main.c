#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_BUCKETS 5
#define BUCKET_INTERVAL 100

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

  int i, numValues = 1000, maxValue = 500, bucketSizes[NUM_BUCKETS] = {0};
  int *values, *buckets[NUM_BUCKETS];

  values = generateValues(numValues, maxValue);

  for (i = 0; i < NUM_BUCKETS; i++) {
    buckets[i] = (int*)malloc(numValues * sizeof(int));
  }

  distributeBetweenBuckets(values, numValues, buckets, bucketSizes, maxValue);

  printaBuckets(buckets, bucketSizes);

  for (i = 0; i < NUM_BUCKETS; i++){
    insertionSort(buckets[i], bucketSizes[i]);
  }

  printaBuckets(buckets, bucketSizes);

  // Liberar memória
  free(values);
  for (int i = 0; i < NUM_BUCKETS; i++) {
    free(buckets[i]);
  }

  return 0;
}

