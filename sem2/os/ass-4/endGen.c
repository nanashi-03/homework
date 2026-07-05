#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REQ_SIZE 20

int main() {
    FILE *fptr = fopen("ends_requests.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < REQ_SIZE; i++) {
        int val;
        if (rand() % 2 == 0) {
            val = rand() % 41; // 50% chance of being 0 - 40
        } else {
            val = 160 + (rand() % 40); // 50% chance of being 160 - 199
        }
        fprintf(fptr, "%d ", val);
    }

    fclose(fptr);
    printf("Successfully generated ends_requests.txt\n");
    return 0;
}
