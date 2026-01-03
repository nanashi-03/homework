#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int l, int r) {
  int pivot = arr[l];
  int i = l - 1, j = r + 1;

  while (1) {
    do {
      i++;
    } while (arr[i] < pivot);

    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j)
      return j;

    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

void quickSort(int arr[], int l, int r){
  if(l < r){
    int pi = partition(arr, l, r);
    
    quickSort(arr, l, pi);
    quickSort(arr, pi+1, r);
  }
}

int main()
{
  int n;
  printf("Enter a number:");
  scanf("%d", &n);
  int arr[n];
  srand(time(NULL));

  for(int i = 0; i < n; i++){
    arr[i] = rand() % 1000;
  }
  
  printf("Unsorted Array:\n");
  for (int i = 0; i < n; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");
  
  quickSort(arr, 0, n-1);

  printf("Sorted Array:\n");
  for (int i = 0; i < n; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
