#include <stdio.h>

#define MAX_BLOCKS 100

int main() {
  int blocks[MAX_BLOCKS];
  int indexBlock, numFiles, numBlocks, blockNum;
  int fileBlocks[MAX_BLOCKS];

  for (int i = 0; i < MAX_BLOCKS; i++) {
    blocks[i] = 0;
  }

  printf("Enter the total number of files to allocate: ");
  scanf("%d", &numFiles);

  for (int i = 0; i < numFiles; i++) {
    printf("\n-----------------------------------------");
    printf("\nProcessing File %d:\n", i + 1);
    printf("Enter the index block number: ");
    scanf("%d", &indexBlock);

    if (blocks[indexBlock] == 1) {
      printf("Error: Block %d is already allocated. Allocation failed for this "
             "file.\n",
             indexBlock);
      continue;
    }

    printf("Enter the number of data blocks needed for this file: ");
    scanf("%d", &numBlocks);

    printf("Enter the block numbers for this file:\n");
    int allocationPossible = 1;

    for (int j = 0; j < numBlocks; j++) {
      printf("Block %d: ", j + 1);
      scanf("%d", &blockNum);
      fileBlocks[j] = blockNum;

      if (blocks[blockNum] == 1 || blockNum == indexBlock) {
        allocationPossible = 0;
      }
    }

    if (allocationPossible == 0) {
      printf("\nAllocation Failed: One or more blocks are already allocated or "
             "conflict with the index block.\n");
    } else {
      blocks[indexBlock] = 1;

      for (int j = 0; j < numBlocks; j++) {
        blocks[fileBlocks[j]] = 1;
      }

      printf("\nAllocation Successful!\n");
      printf("File %d Index Block: %d\n", i + 1, indexBlock);
      printf("Mapped Data Blocks: ");
      for (int j = 0; j < numBlocks; j++) {
        printf("%d -> ", fileBlocks[j]);
      }
      printf("NULL\n");
    }
  }

  printf("\n-----------------------------------------\n");
  printf("Simulation completed.\n");
  return 0;
}
