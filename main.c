#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* generateValues(int numValues, int biggestNum, int* values){
  int i;

  srand(time(NULL));

  for (i = 0; i < numValues; i++) { 
    values[i] = rand() % biggestNum;
  }

  return values;
}

void printaBuckets(int numValues, int buckets[5][numValues], int index[]){

  int i;

  printf("\n\nBUCKET 0 (0-100):\n");
  for (i = 0; i < index[0]; i++){
    printf("[%d]; ", buckets[0][i]);
  }
  printf("\n\nBUCKET 1 (101-200):\n");
  for (i = 0; i < index[1]; i++){
    printf("[%d]; ", buckets[1][i]);
  }
  printf("\n\nBUCKET 2 (201-300):\n");
  for (i = 0; i < index[2]; i++){
    printf("[%d]; ", buckets[2][i]);
  }
  printf("\n\nBUCKET 3 (301-400):\n");
  for (i = 0; i < index[3]; i++){
    printf("[%d]; ", buckets[3][i]);
  }
  printf("\n\nBUCKET 4 (401-500):\n");
  for (i = 0; i < index[4]; i++){
    printf("[%d]; ", buckets[4][i]);
  }

}

int main(){
  int i, numValues = 1000, bucket[5][numValues], index[5] = {0, 0, 0, 0, 0};
  int *values;

  values = (int*) malloc(numValues * sizeof(int));
  values = generateValues(numValues, 500, values);

  for (i = 0; i < numValues; i++){
    if (values[i] <= 100){
      bucket[0][index[0]] = values[i];
      index[0]++;
    }
    else if (values[i] >= 101 && values[i] <= 200){
      bucket[1][index[1]] = values[i];
      index[1]++;
    }
    else if (values[i] >= 201 && values[i] <= 300){
      bucket[2][index[2]] = values[i];
      index[2]++;
    }
    else if (values[i] >= 301 && values[i] <= 400){
      bucket[3][index[3]] = values[i];
      index[3]++;
    }
    else if (values[i] >= 401 && values[i] <= 500){
      bucket[4][index[4]] = values[i];
      index[4]++;
    }
  }

  printaBuckets(numValues, bucket, index);


  // INSERTION SORT (só no bucket 0)
  for (i = 1; i < index[0]; i++) {
    int key = bucket[0][i];
    int j = i - 1;

    while (j >= 0 && bucket[0][j] > key) {
        bucket[0][j + 1] = bucket[0][j];
        j = j - 1;
    }
    bucket[0][j + 1] = key;
  }


  printaBuckets(numValues, bucket, index);

  return 0;
}

