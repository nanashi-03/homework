#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

bool is_palindrome(char str[]) {
    int left = 0;
    int right = strlen(str) - 1;

    while (right > left) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    int pipe_p2c[2];
    int pipe_c2p[2];
    pid_t pid;

    if (pipe(pipe_p2c) == -1 || pipe(pipe_c2p) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        close(pipe_p2c[1]);
        close(pipe_c2p[0]);

        char child_buffer[BUFFER_SIZE];

        while (1) {
            int bytes_read = read(pipe_p2c[0], child_buffer, BUFFER_SIZE);
            if (bytes_read <= 0) break;

            child_buffer[bytes_read] = '\0';

            if (strcmp(child_buffer, "quit") == 0) {
                break;
            }

            if (is_palindrome(child_buffer)) {
                write(pipe_c2p[1], "YES", 4);
            }
            else {
                write(pipe_c2p[1], "NO", 3);
            }
        }

        close(pipe_p2c[0]);
        close(pipe_c2p[1]);
        printf("[Child] Terminating safely.\n");
        exit(0);

    }
    else {
        close(pipe_p2c[0]);
        close(pipe_c2p[1]);

        char parent_buffer[BUFFER_SIZE];
        char response[BUFFER_SIZE];

        while (1) {
            printf("\nEnter a string (or 'quit' to exit): ");

            if (fgets(parent_buffer, BUFFER_SIZE, stdin) == NULL) break;
            parent_buffer[strcspn(parent_buffer, "\n")] = '\0';

            write(pipe_p2c[1], parent_buffer, strlen(parent_buffer));

            if (strcmp(parent_buffer, "quit") == 0) {
                break;
            }

            int bytes_received = read(pipe_c2p[0], response, BUFFER_SIZE);
            if (bytes_received > 0) {
                response[bytes_received] = '\0';
                printf("[Parent] Is it a palindrome? -> %s\n", response);
            }
        }

        close(pipe_p2c[1]);
        close(pipe_c2p[0]);

        printf("[Parent] Waiting for child to clean up...\n");
        wait(NULL);
        printf("[Parent] Terminating safely.\n");
    }

    return 0;
}
