#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r){    
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
    
  int A[n1], B[n2];

  for (i = 0; i < n1; i++)
    A[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    B[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (A[i] <= B[j]) {
      arr[k] = A[i];
      i++;
    }
    else {
      arr[k] = B[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = A[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = B[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r){
  if(l < r) {
    int m = l + (r - l)/2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
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
  
  mergeSort(arr, 0, n-1);
  
  printf("Sorted Array:\n");
  for (int i = 0; i < n; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
