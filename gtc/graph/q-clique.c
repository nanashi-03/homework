#include <stdio.h>
#include <stdlib.h>

int main()
{
  int v;
  printf("Enter the number of vertices:");
  scanf("%d", &v);
  int graph[v][v];

  for (int i = 0; i < v; i++) {
    printf("\nEnter the connected vertices for vertex %d: ", i+1);
    for (int j = 0; j < v; j++) {
      scanf("%d", &graph[i][j]);
    }
  }

  return EXIT_SUCCESS;
}
