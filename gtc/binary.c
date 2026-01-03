#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  int n;
  printf("Enter the number of elements:");
  scanf("%d", &n);
  int arr[n];
  srand(time(NULL));

  int incr = time(NULL) % 1000;

  for (int i = 0; i < n; i++) {
    arr[i] = incr;
    incr = incr + (rand()%100);
  }

  int sindex = rand() % n;

  int select = arr[sindex];

  int l = 0, u = n-1, m;
  printf("%d %d %d %d\n", l, u, sindex, select);

  int index;

  while(l <= u){
    m = (l + u)/2;
    printf("%d\n", m);
    if(arr[m] == select){
      index = m;
      // printf("Found at %d\n", m);
      break;
    }
    else if(arr[m] > select) {
      u = m - 1;
      // printf("u reduced to %d\n", u);
    }
    else if(arr[m] < select) {
      l = m + 1;
      // printf("l increased to %d\n", l);
    }
  }

  for (int i = 0; i < n; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\nFound at index %d", index);
  printf("\n");

  return EXIT_SUCCESS;
}
