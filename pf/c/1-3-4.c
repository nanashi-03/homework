#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sems 3
#define subs 6

void top4Subs(int n, int marks[n][sems][subs]){
  printf("\nTop 4 Subject Marks for Each Student:\n");

  for (int i = 0; i < n; i++) {
    int allMarks[sems * subs];
    int k = 0;

    for (int s = 0; s < sems; s++)
      for (int j = 0; j < subs; j++)
        allMarks[k++] = marks[i][s][j];

    for (int x = 0; x < k - 1; x++) {
      for (int y = x + 1; y < k; y++) {
        if (allMarks[x] < allMarks[y]) {
          int temp = allMarks[x];
          allMarks[x] = allMarks[y];
          allMarks[y] = temp;
        }
      }
    }

    printf("Student %d: ", i + 1);
    for (int m = 0; m < 4; m++)
      printf("%d ", allMarks[m]);
    printf("\n");
  }
}
void top5Scorers(int n, int marks[n][sems][subs]){
  printf("\nTop 5 Scorers in Each Subject (Semester-wise):\n");

  for (int s = 0; s < sems; s++) {
    for (int j = 0; j < subs; j++) {
      int score[n];
      int idx[n];

      for (int i = 0; i < n; i++) {
        score[i] = marks[i][s][j];
        idx[i] = i;
      }

      for (int x = 0; x < n - 1; x++) {
        for (int y = x + 1; y < n; y++) {
          if (score[x] < score[y]) {
            int temp = score[x];
            score[x] = score[y];
            score[y] = temp;

            temp = idx[x];
            idx[x] = idx[y];
            idx[y] = temp;
          }
        }
      }

      printf("Semester %d Subject %d: ", s + 1, j + 1);
      for (int k = 0; k < 5; k++)
        printf("S%d(%d) ", idx[k] + 1, score[k]);
      printf("\n");
    }
  }
}
void semTopper(int n, int marks[n][sems][subs]){
  printf("\nSemester-wise Top Scorers:\n");

  for (int s = 0; s < sems; s++) {
    int maxTotal = -1;
    int topper = -1;

    for (int i = 0; i < n; i++) {
      int total = 0;
      for (int j = 0; j < subs; j++)
        total += marks[i][s][j];

      if (total > maxTotal) {
        maxTotal = total;
        topper = i;
      }
    }

    printf("Semester %d: Student %d (Total = %d)\n", s+1, topper+1, maxTotal);
  }
}

int main()
{
  int n;
  printf("Enter the number of students:");
  scanf("%d", &n);
  int marks[n][sems][subs];
  
  srand(time(NULL));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < sems; j++) {
      for (int k = 0; k < subs; k++) {
        marks[i][j][k] = rand() % 100 + 1;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    printf("\nStudent %d\n", i+1);
    for (int j = 0; j < sems; j++) {
      printf("Sem %d\n", j+1);
      for (int k = 0; k < subs; k++) {
        printf("%d ", marks[i][j][k]);
      }
      printf("\n");
    }
  }

  top4Subs(n, marks);
  top5Scorers(n, marks);
  semTopper(n, marks);

  return EXIT_SUCCESS;
}
