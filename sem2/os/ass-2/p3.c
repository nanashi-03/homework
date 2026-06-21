#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int main() {
    int num_children = 10;
    int range_size = 10;
    pid_t pid;

    printf("[Parent] Starting 10 child processes to find prime numbers...\n\n");

    for (int i = 0; i < num_children; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0) {
            int start = (i * range_size) + 1;
            int end = (i + 1) * range_size;

            printf("[Child %d] PID: %d is checking range %d to %d\n", i + 1, getpid(), start, end);

            for (int num = start; num <= end; num++) {
                if (is_prime(num)) {
                    printf("[Child %d Found]: %d\n", i + 1, num);
                }
            }

            printf("[Child %d] PID: %d finished.\n", i + 1, getpid());
            exit(0);
        }
    }

    printf("\n[Parent] All children spawned. Waiting for them to complete...\n\n");

    for (int i = 0; i < num_children; i++) {
        wait(NULL);
    }

    printf("\n[Parent] All child processes have finished. Exiting.\n");
    return 0;
}
