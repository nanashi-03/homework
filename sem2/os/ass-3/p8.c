#include <stdio.h>

#define MAX_PAGES 50

int simulateFIFO(int pages[], int numPages, int numFrames) {
  int frames[numFrames];
  int pageFaults = 0;
  int index = 0;

  for (int i = 0; i < numFrames; i++) {
    frames[i] = -1;
  }

  printf("\n--- Simulation with %d Frames ---\n", numFrames);
  printf("Incoming Page | Frame State\n");
  printf("--------------|-----------------------\n");

  for (int i = 0; i < numPages; i++) {
    int currentPage = pages[i];
    int isHit = 0;

    for (int j = 0; j < numFrames; j++) {
      if (frames[j] == currentPage) {
        isHit = 1;
        break;
      }
    }

    if (isHit == 0) {
      pageFaults++;
      frames[index] = currentPage;
      index = (index + 1) % numFrames;
    }

    printf("      %2d      | ", currentPage);
    for (int j = 0; j < numFrames; j++) {
      if (frames[j] != -1) {
        printf("%2d ", frames[j]);
      } else {
        printf("-  ");
      }
    }

    if (isHit == 1) {
      printf(" (Hit)");
    } else {
      printf(" (Fault)");
    }
    printf("\n");
  }

  printf("Total Page Faults: %d\n", pageFaults);
  return pageFaults;
}

int main() {
  int numPages;

  printf("--- FIFO Page Replacement Algorithm Simulation ---\n\n");
  printf("Enter the length of the page reference string: ");
  scanf("%d", &numPages);

  int pages[MAX_PAGES];
  printf("Enter the page reference string (separated by spaces):\n");
  for (int i = 0; i < numPages; i++) {
    scanf("%d", &pages[i]);
  }

  int faultsWith3 = simulateFIFO(pages, numPages, 3);
  int faultsWith4 = simulateFIFO(pages, numPages, 4);

  printf("\n=========================================\n");
  printf("           COMPARISON RESULTS            \n");
  printf("=========================================\n");
  printf(" Frame Count  |  Total Page Faults \n");
  printf("--------------|-----------------------\n");
  printf("   3 Frames   |        %d\n", faultsWith3);
  printf("   4 Frames   |        %d\n", faultsWith4);
  printf("=========================================\n");

  if (faultsWith3 > faultsWith4) {
    printf("Conclusion: Increasing the frame allocation from 3 to 4 reduced "
           "the total page faults.\n");
  } else if (faultsWith3 == faultsWith4) {
    printf("Conclusion: Both configurations resulted in the same number of "
           "page faults.\n");
  } else {
    printf("Conclusion: Notice that page faults *increased* despite adding "
           "more memory blocks!\n");
    printf("            This unique behavior is known as Belady's Anomaly, "
           "which uniquely affects FIFO.\n");
  }

  return 0;
}
