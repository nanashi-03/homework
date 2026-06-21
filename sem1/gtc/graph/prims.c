#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 999
#define MAXE 4096

void printGraph(int v, int graph[v][v]) {
  printf("\nAdjacency Matrix:\n");
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      if (graph[i][j] != INF)
        printf("%d ", graph[i][j]);
      else
        printf("0 ");
    }
    printf("\n");
  }
}

void generateRandomGraph(int v, int graph[v][v], double p) {
  for (int i = 0; i < v; i++)
    for (int j = 0; j < v; j++)
      graph[i][j] = INF;

  for (int i = 0; i < v; i++) {
    for (int j = i + 1; j < v; j++) {
      if ((double)rand() / RAND_MAX < p) {
        int w = rand() % 100 + 1;
        graph[i][j] = w;
        graph[j][i] = w;
      }
    }
  }
}

void prims(int v, int graph[v][v]) {
  int inMST[v];
  for (int i = 0; i < v; i++)
    inMST[i] = 0;

  inMST[0] = 1;

  int edges = 0;
  int mincost = 0;

  printf("\nEdges in MST:\n");

  while (edges < v - 1) {
    int min = INF;
    int a = -1, b = -1;

    for (int i = 0; i < v; i++) {
      if (inMST[i]) {
        for (int j = 0; j < v; j++) {
          if (!inMST[j] && graph[i][j] < min) {
            min = graph[i][j];
            a = i;
            b = j;
          }
        }
      }
    }

    if (a == -1 || b == -1) {
      printf("\nGraph is disconnected. MST not possible.\n");
      return;
    }

    printf("(%d, %d) cost = %d\n", a, b, min);
    mincost += min;
    inMST[b] = 1;
    edges++;
  }

  printf("\nMinimum cost = %d\n", mincost);
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

  prims(v, graph);

  return EXIT_SUCCESS;
}

