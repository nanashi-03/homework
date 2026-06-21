#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_JOBS 30
#define MAX_PRIORITY 5
#define MAX_BURST_PAIRS 5

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int jobs = (argc > 1 && atoi(argv[1]) > 0) ? atoi(argv[1]) : TOTAL_JOBS;

    FILE *file = fopen("profile.txt", "w");
    if (!file) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }

    int current_arrival_time = 0;

    for (int i = 1; i <= jobs; i++) {
        int id = i;
        int priority = (rand() % MAX_PRIORITY) + 1;

        current_arrival_time += (rand() % 6);

        fprintf(file, "%d %d %d", id, priority, current_arrival_time);

        int burst_pairs = (rand() % MAX_BURST_PAIRS) + 1;

        for (int j = 0; j < burst_pairs; j++) {
            int cpu_burst = (rand() % 25) + 5;
            fprintf(file, " %d", cpu_burst);

            if (j < burst_pairs - 1) {
                int io_burst = (rand() % 15) + 2;
                fprintf(file, " %d", io_burst);
            }
        }

        fprintf(file, " -1\n");
    }

    fclose(file);
    printf("Successfully generated 'profile.txt' with %d randomized job configurations!\n", jobs);

    return EXIT_SUCCESS;
}
