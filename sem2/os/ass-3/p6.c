#include <stdio.h>
#include <stdlib.h>

void fcfsDiskScheduling(int requests[], int numRequests, int initialHead) {
  int totalHeadMovement = 0;
  int currentHead = initialHead;

  printf("\n=========================================\n");
  printf("Seek Sequence: ");
  printf("%d", initialHead);
  for (int i = 0; i < numRequests; i++) {
    printf(" -> %d", requests[i]);
  }
  printf("\n=========================================\n");

  for (int i = 0; i < numRequests; i++) {
    totalHeadMovement += abs(requests[i] - currentHead);

    currentHead = requests[i];
  }

  printf("Total Head Movement (Seek Time): %d cylinders\n", totalHeadMovement);
  printf("Average Seek Time: %.2f cylinders\n",
         (float)totalHeadMovement / numRequests);
}

int main() {
  int numRequests, initialHead;

  printf("--- FCFS Disk Scheduling Simulation ---\n\n");
  printf("Enter the number of disk track requests: ");
  scanf("%d", &numRequests);

  int requests[numRequests];

  printf("Enter the track requests sequence:\n");
  for (int i = 0; i < numRequests; i++) {
    printf("Request %d: ", i + 1);
    scanf("%d", &requests[i]);
  }

  printf("Enter the initial position of the R/W Head: ");
  scanf("%d", &initialHead);

  fcfsDiskScheduling(requests, numRequests, initialHead);

  return 0;
}
