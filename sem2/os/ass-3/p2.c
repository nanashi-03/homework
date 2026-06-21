#include <stdbool.h>
#include <stdio.h>

int main() {
  int numProcesses, numResources;

  printf("Enter the number of Processes: ");
  scanf("%d", &numProcesses);
  printf("Enter the number of Resources: ");
  scanf("%d", &numResources);

  int alloc[numProcesses][numResources];
  int max[numProcesses][numResources];
  int avail[numResources];
  int need[numProcesses][numResources];
  int finish[numProcesses];
  int safeSequence[numProcesses];
  int work[numResources];
  int index = 0;

  for (int i = 0; i < numProcesses; i++) {
    finish[i] = 0;
  }

  printf("\nEnter the Allocation Matrix:\n");
  for (int i = 0; i < numProcesses; i++) {
    printf("For Process P%d: ", i);
    for (int j = 0; j < numResources; j++) {
      scanf("%d", &alloc[i][j]);
    }
  }

  printf("\nEnter the Max Matrix:\n");
  for (int i = 0; i < numProcesses; i++) {
    printf("For Process P%d: ", i);
    for (int j = 0; j < numResources; j++) {
      scanf("%d", &max[i][j]);
    }
  }

  printf("\nEnter the Available Resources:\n");
  for (int i = 0; i < numResources; i++) {
    printf("Resource %d: ", i);
    scanf("%d", &avail[i]);
    work[i] = avail[i];
  }

  for (int i = 0; i < numProcesses; i++) {
    for (int j = 0; j < numResources; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }

  for (int k = 0; k < numProcesses; k++) {
    for (int i = 0; i < numProcesses; i++) {
      if (finish[i] == 0) {
        bool canProceed = true;

        for (int j = 0; j < numResources; j++) {
          if (need[i][j] > work[j]) {
            canProceed = false;
            break;
          }
        }

        if (canProceed) {
          safeSequence[index++] = i;

          for (int y = 0; y < numResources; y++) {
            work[y] += alloc[i][y];
          }

          finish[i] = 1;
        }
      }
    }
  }

  bool isSafe = true;
  for (int i = 0; i < numProcesses; i++) {
    if (finish[i] == 0) {
      isSafe = false;
      printf(
          "\nResult: The system is NOT in a safe state! Deadlock detected.\n");
      break;
    }
  }

  if (isSafe) {
    printf("\nResult: The system is in a SAFE STATE.\n");
    printf("Following is the SAFE SEQUENCE:\n");
    for (int i = 0; i < numProcesses - 1; i++) {
      printf(" P%d ->", safeSequence[i]);
    }
    printf(" P%d\n", safeSequence[numProcesses - 1]);
  }

  return 0;
}
