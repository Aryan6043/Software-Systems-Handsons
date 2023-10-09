#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process (PID=%d) is running.\n", getpid());
        sleep(5); // Simulate some work in the child process
        printf("Child process (PID=%d) is exiting.\n", getpid());
    } else {
        // Parent process
        printf("Parent process (PID=%d) created child process (PID=%d).\n", getpid(), child_pid);

        // Parent process exits immediately without waiting for the child
        printf("Parent process (PID=%d) is exiting.\n", getpid());
        exit(0); // Parent exits
    }

    return 0;
}
