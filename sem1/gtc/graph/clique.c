#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX_CLIQUES 1024

int bestSize = 0;
uint64_t bestCliques[MAX_CLIQUES];
int bestCount = 0;

int bitCount(uint64_t x) {
  return __builtin_popcountll(x);
}

void printGraph(int v, int graph[v][v]) {
  printf("\nAdjacency Matrix:\n");
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
}

void generateRandomGraph(int v, int graph[v][v], double p) {
  for (int i = 0; i < v; i++)
    for (int j = 0; j < v; j++)
      graph[i][j] = 0;

  for (int i = 0; i < v; i++) {
    for (int j = i + 1; j < v; j++) {
      if ((double)rand() / RAND_MAX < p) {
        graph[i][j] = 1;
        graph[j][i] = 1;
      }
    }
  }
}

int canAdd(int v, int graph[v][v], int i, uint64_t c) {
  for (int j = 0; j < v; j++) {
    if ((c & (1ULL << j)) && graph[i][j] == 0)
      return 0;
  }
  return 1;
}

void findMaxClique(int v, int graph[v][v], int start, uint64_t c) {
  int size = bitCount(c);

  if (size > bestSize) {
    bestSize = size;
    bestCount = 0;
    bestCliques[bestCount++] = c;
  }
  else if (size == bestSize) {
    if (bestCount < MAX_CLIQUES)
      bestCliques[bestCount++] = c;
  }

  for (int i = start + 1; i < v; i++) {
    if (size + (v - i) <= bestSize)
      return;

    if (canAdd(v, graph, i, c)) {
      findMaxClique(v, graph, i, c | (1ULL << i));
    }
  }
}

void printMaximumClique(int v, int graph[v][v]) {
  bestSize = 0;
  bestCount = 0;

  for (int i = 0; i < v; i++) {
    findMaxClique(v, graph, i, (1ULL << i));
  }

  printf("\nMaximum Clique Size: %d\n", bestSize);
  printf("Number of maximum cliques found: %d\n\n", bestCount);

  for (int k = 0; k < bestCount; k++) {
    printf("Clique %d: ", k + 1);
    for (int i = 0; i < v; i++) {
      if (bestCliques[k] & (1ULL << i))
        printf("%d ", i);
    }
    printf("\n");
  }
}

int main() {
  int v;
  double p;

  printf("Enter number of vertices (<= 64): ");
  scanf("%d", &v);

  if (v <= 0 || v > 64) {
    printf("Invalid vertex count.\n");
    return EXIT_FAILURE;
  }

  printf("Enter edge probability (0.0 – 1.0): ");
  scanf("%lf", &p);

  srand(time(NULL));

  int graph[v][v];
  generateRandomGraph(v, graph, p);
  printGraph(v, graph);

  printMaximumClique(v, graph);

  return EXIT_SUCCESS;
}
