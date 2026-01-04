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

typedef struct {
  int u, v, w;
} Edge;

int find(int x, int parent[]) {
  if (parent[x] != x)
    parent[x] = find(parent[x], parent);
  return parent[x];
}

void graphunion(int a, int b, int parent[], int rank[]) {
  a = find(a, parent);
  b = find(b, parent);

  if (a == b)
    return;

  if (rank[a] < rank[b])
    parent[a] = b;
  else if (rank[a] > rank[b])
    parent[b] = a;
  else {
    parent[b] = a;
    rank[a]++;
  }
}

int cmpEdge(const void *a, const void *b) {
  return ((Edge *)a)->w - ((Edge *)b)->w;
}

void kruskal(int v, int graph[v][v]) {
  Edge edges[MAXE];
  int edgeCount = 0;

  for (int i = 0; i < v; i++) {
    for (int j = i + 1; j < v; j++) {
      if (graph[i][j] != INF) {
        edges[edgeCount++] = (Edge){i, j, graph[i][j]};
      }
    }
  }

  qsort(edges, edgeCount, sizeof(Edge), cmpEdge);

  int parent[v], rank[v];
  for (int i = 0; i < v; i++) {
    parent[i] = i;
    rank[i] = 0;
  }

  int mstEdges = 0;
  int mincost = 0;

  printf("\nEdges in MST:\n");

  for (int i = 0; i < edgeCount && mstEdges < v - 1; i++) {
    int u = edges[i].u;
    int w = edges[i].v;
    int cost = edges[i].w;

    if (find(u, parent) != find(w, parent)) {
      graphunion(u, w, parent, rank);
      printf("(%d, %d) cost = %d\n", u, w, cost);
      mincost += cost;
      mstEdges++;
    }
  }

  if (mstEdges != v - 1)
    printf("\nGraph is disconnected. MST not possible.\n");
  else
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

  kruskal(v, graph);

  return EXIT_SUCCESS;
}

