#include <stdio.h>
#include <stdlib.h>

int bestSize = 0;
int bestMask = 0;

int bitCount(int x) {
  int c = 0;
  while (x) {
    c += x & 1;
    x >>= 1;
  }
  return c;
}

int canAdd(int v, int graph[v][v], int i, int c) {
  for (int j = 0; j < v; j++) {
    if ((c & (1 << j)) && graph[i][j] == 0)
      return 0;
  }
  return 1;
}

void findMaxClique(int v, int graph[v][v], int start, int c) {
  int size = bitCount(c);

  if (size > bestSize) {
    bestSize = size;
    bestMask = c;
  }

  for (int i = start + 1; i < v; i++) {
    if (size + (v - i) <= bestSize)
      return;

    if (canAdd(v, graph, i, c))
      findMaxClique(v, graph, i, c | (1 << i));
  }
}

void printMaximumClique(int v, int graph[v][v]) {
  for (int i = 0; i < v; i++)
    findMaxClique(v, graph, i, 1 << i);

  printf("\nMaximum Clique (size %d): ", bestSize);
  for (int i = 0; i < v; i++) {
    if (bestMask & (1 << i))
      printf("%d ", i + 1);
  }
  printf("\n");
}

int main() {
  int v;
  printf("Enter the number of vertices: ");
  scanf("%d", &v);

  int graph[v][v];

  for (int i = 0; i < v; i++) {
    printf("Enter adjacency for vertex %d: ", i + 1);
    for (int j = 0; j < v; j++) {
      scanf("%d", &graph[i][j]);
    }
  }

  printMaximumClique(v, graph);

  return EXIT_SUCCESS;
}
