#include <stdio.h>

void worstFit(int blockSizes[], int numBlocks, int processSizes[],
              int numProcesses) {
  int allocation[numProcesses];
  int isOccupied[numBlocks];

  for (int i = 0; i < numProcesses; i++) {
    allocation[i] = -1;
  }
  for (int j = 0; j < numBlocks; j++) {
    isOccupied[j] = 0;
  }

  for (int i = 0; i < numProcesses; i++) {
    int worstIdx = -1;

    for (int j = 0; j < numBlocks; j++) {
      if (!isOccupied[j] && blockSizes[j] >= processSizes[i]) {
        if (worstIdx == -1) {
          worstIdx = j;
        } else if (blockSizes[j] > blockSizes[worstIdx]) {
          worstIdx = j;
        }
      }
    }

    if (worstIdx != -1) {
      allocation[i] = worstIdx;
      isOccupied[worstIdx] = 1;
    }
  }

  printf("\nProcess No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < numProcesses; i++) {
    printf(" %d\t\t%d\t\t", i + 1, processSizes[i]);
    if (allocation[i] != -1) {
      printf("%d\n", allocation[i] + 1);
    } else {
      printf("Not Allocated\n");
    }
  }
}

int main() {
  int numBlocks, numProcesses;

  printf("Enter the number of memory blocks: ");
  scanf("%d", &numBlocks);
  printf("Enter the number of processes: ");
  scanf("%d", &numProcesses);

  int blockSizes[numBlocks];
  int processSizes[numProcesses];

  printf("\nEnter the sizes of the memory blocks:\n");
  for (int i = 0; i < numBlocks; i++) {
    printf("Block %d: ", i + 1);
    scanf("%d", &blockSizes[i]);
  }

  printf("\nEnter the sizes of the processes:\n");
  for (int i = 0; i < numProcesses; i++) {
    printf("Process %d: ", i + 1);
    scanf("%d", &processSizes[i]);
  }

  worstFit(blockSizes, numBlocks, processSizes, numProcesses);

  return 0;
}
