#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {;
        printf("[Child]  My PID: %d\n", getpid());
        printf("[Child]  My Parent's PID: %d\n", getppid());

        printf("[Child]  Exiting with status 1...\n");
        exit(1);
    }
    else {
        printf("[Parent] My PID: %d\n", getpid());
        printf("[Parent] My Parent's PID (Shell/Terminal): %d\n", getppid());
        printf("[Parent] Waiting for the child process to finish...\n");

        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("[Parent] Child process finished normally.\n");
            printf("[Parent] Child's exit status was: %d\n", exit_status);
        } else {
            printf("[Parent] Child process did not terminate normally.\n");
        }
    }

    return 0;
}
