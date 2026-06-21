#include <stdio.h>

#define MAX_PAGES 50

int findLRU(int time[], int n) {
  int minimum = time[0], minIndex = 0;
  for (int i = 1; i < n; i++) {
    if (time[i] < minimum) {
      minimum = time[i];
      minIndex = i;
    }
  }
  return minIndex;
}

int simulateLRU(int pages[], int numPages, int numFrames) {
  int frames[numFrames];
  int time[numFrames];
  int pageFaults = 0;
  int counter = 0;

  for (int i = 0; i < numFrames; i++) {
    frames[i] = -1;
    time[i] = 0;
  }

  printf("\n--- Simulation with %d Frames ---\n", numFrames);
  printf("Incoming Page | Frame State\n");
  printf("--------------|-----------------------\n");

  for (int i = 0; i < numPages; i++) {
    int currentPage = pages[i];
    int flag1 = 0, flag2 = 0;

    for (int j = 0; j < numFrames; j++) {
      if (frames[j] == currentPage) {
        counter++;
        time[j] = counter;
        flag1 = 1;
        flag2 = 1;
        break;
      }
    }

    if (flag1 == 0) {
      for (int j = 0; j < numFrames; j++) {
        if (frames[j] == -1) {
          counter++;
          pageFaults++;
          frames[j] = currentPage;
          time[j] = counter;
          flag2 = 1;
          break;
        }
      }
    }

    if (flag2 == 0) {
      int lruIndex = findLRU(time, numFrames);
      counter++;
      pageFaults++;
      frames[lruIndex] = currentPage;
      time[lruIndex] = counter;
    }

    printf("      %2d      | ", currentPage);
    for (int j = 0; j < numFrames; j++) {
      if (frames[j] != -1) {
        printf("%2d ", frames[j]);
      } else {
        printf("-  ");
      }
    }
    if (flag1 == 1) {
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

  printf("--- LRU Page Replacement Algorithm Simulation ---\n\n");
  printf("Enter the length of the page reference string: ");
  scanf("%d", &numPages);

  int pages[MAX_PAGES];
  printf("Enter the page reference string (separated by spaces):\n");
  for (int i = 0; i < numPages; i++) {
    scanf("%d", &pages[i]);
  }

  int faultsWith4 = simulateLRU(pages, numPages, 4);
  int faultsWith5 = simulateLRU(pages, numPages, 5);

  printf("\n=========================================\n");
  printf("           COMPARISON RESULTS            \n");
  printf("=========================================\n");
  printf(" Frame Count  |  Total Page Faults \n");
  printf("--------------|-----------------------\n");
  printf("   4 Frames   |        %d\n", faultsWith4);
  printf("   5 Frames   |        %d\n", faultsWith5);
  printf("=========================================\n");

  if (faultsWith4 > faultsWith5) {
    printf("Conclusion: Increasing the frame allocation from 4 to 5 reduced "
           "the total page faults.\n");
  } else if (faultsWith4 == faultsWith5) {
    printf("Conclusion: Both configurations resulted in the same number of "
           "page faults for this reference string.\n");
  } else {
    printf("Conclusion: Notice that LRU strictly obeys the inclusion property, "
           "meaning page faults will not increase when adding frames.\n");
  }

  return 0;
}
