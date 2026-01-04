#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8
#define TOTAL (N * N)

void printMatrix(int a[N][N]) {
  printf("\nMatrix:\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("%3d ", a[i][j]);
    printf("\n");
  }
}

void verticalExchange(int a[N][N]) {
  for (int i = 0; i < N / 2; i++) {
    for (int j = 0; j < N; j++) {
      int temp = a[i][j];
      a[i][j] = a[N - 1 - i][j];
      a[N - 1 - i][j] = temp;
    }
  }
  printf("Vertical exchange completed.\n");
}

void horizontalExchange(int a[N][N]) {
  for (int j = 0; j < N / 2; j++) {
    for (int i = 0; i < N; i++) {
      int temp = a[i][j];
      a[i][j] = a[i][N - 1 - j];
      a[i][N - 1 - j] = temp;
    }
  }
  printf("Horizontal exchange completed.\n");
}

void randomExchange(int a[N][N]) {
  int flat[TOTAL];
  int k = 0;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      flat[k++] = a[i][j];

  for (int i = TOTAL - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = flat[i];
    flat[i] = flat[j];
    flat[j] = temp;
  }

  k = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      a[i][j] = flat[k++];

  printf("Random exchange completed.\n");
}

void stopProgram(int a[N][N]) {
  printMatrix(a);
  printf("Program terminated.\n");
  exit(0);
}

int main() {
  int a[N][N];
  int choice;
  srand(time(NULL));

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      a[i][j] = rand() % 100;

  void (*ops[])(int[N][N]) = {
    verticalExchange,
    horizontalExchange,
    randomExchange,
    stopProgram
  };

  srand(time(NULL));

  while (1) {
    printMatrix(a);

    printf("\nMenu:\n");
    printf("1. Vertical Exchange\n");
    printf("2. Horizontal Exchange\n");
    printf("3. Random Exchange\n");
    printf("4. Stop\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 4) {
      printf("Invalid choice.\n");
      continue;
    }

    ops[choice - 1](a);
  }

  return 0;
}
