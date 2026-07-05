#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REQ_SIZE 20

int main() {
    FILE *fptr = fopen("mids_requests.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < REQ_SIZE; i++) {
        int val = 80 + (rand() % 41);  // 80 - 120

        fprintf(fptr, "%d ", val);
    }

    fclose(fptr);
    printf("Successfully generated mids_requests.txt\n");
    return 0;
}
