#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX_RESULTS 1024

int bestSize = 0;
double bestDensity = 0.0;
uint64_t bestMasks[MAX_RESULTS];
int bestCount = 0;

int bitCount(uint64_t x) {
  int count = 0;
  while (x) {
    x &= (x - 1);
    count++;
  }
  return count;
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

int edgeCount(int v, int graph[v][v], uint64_t mask) {
  int edges = 0;
  for (int i = 0; i < v; i++) {
    if (!(mask & (1ULL << i))) continue;
    for (int j = i + 1; j < v; j++) {
      if ((mask & (1ULL << j)) && graph[i][j])
        edges++;
    }
  }
  return edges;
}

double density(int v, int graph[v][v], uint64_t mask) {
  int k = bitCount(mask);
  if (k < 2) return 1.0;

  int e = edgeCount(v, graph, mask);
  return (2.0 * e) / (k * (k - 1));
}

void findMaxQClique(int v, int graph[v][v], int start, uint64_t c, double gamma) {
  int size = bitCount(c);
  double d = density(v, graph, c);

  if (d >= gamma) {
    if (size > bestSize || (size == bestSize && d > bestDensity)) {
      bestSize = size;
      bestDensity = d;
      bestCount = 0;
      bestMasks[bestCount++] = c;

    } 
    else if (size == bestSize && d == bestDensity) {
      if (bestCount < MAX_RESULTS)
        bestMasks[bestCount++] = c;
    }
  }

  for (int i = start + 1; i < v; i++) {
    if (size + (v - i) <= bestSize)
      return;
    
    uint64_t newc = c | (1ULL << i);

    if (density(v, graph, newc) >= gamma) {
      findMaxQClique(v, graph, i, newc, gamma);
    }
  }
}

void printMaximumClique(int v, int graph[v][v], double gamma) {
  bestSize = 0;
  bestDensity = 0.0;
  bestCount = 0;
  
  for (int i = 0; i < v; i++) {
    findMaxQClique(v, graph, i, (1ULL << i), gamma);
  }

  printf("\nMaximum %.2f-Quasi-Clique (size %d): ", gamma, bestSize);
  printf("Density: %.4f\n", bestDensity);
  printf("Number of solutions: %d\n\n", bestCount);

  for (int k = 0; k < bestCount; k++) {
    printf("Quasi-Clique %d: ", k + 1);
    for (int i = 0; i < v; i++) {
      if (bestMasks[k] & (1ULL << i))
        printf("%d ", i);
    }
    printf("\n");
  }
}

int main() {
  int v;
  double p, gamma;

  printf("Enter number of vertices (<= 64): ");
  scanf("%d", &v);

  if (v <= 0 || v > 64) {
    printf("Invalid vertex count.\n");
    return EXIT_FAILURE;
  }

  printf("Enter edge probability (0.0(empty) – 1.0(full)): ");
  scanf("%lf", &p);

  printf("Enter the gamma (0.0(least dense q-clique) - 1.0(clique)):");
  scanf("%lf", &gamma);

  srand(time(NULL));

  int graph[v][v];
  generateRandomGraph(v, graph, p);
  printGraph(v, graph);

  printMaximumClique(v, graph, gamma);

  return EXIT_SUCCESS;
}
