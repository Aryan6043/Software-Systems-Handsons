#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid[3];
    int status;
    
    // Create three child processes
    for (int i = 0; i < 3; i++) {
        child_pid[i] = fork();
        
        if (child_pid[i] == -1) {
            perror("Fork failed");
            return 1;
        }
        
        if (child_pid[i] == 0) {
            // Child process
            printf("Child %d (PID=%d) is running.\n", i, getpid());
            int sleep_time = 0;
            if (i == 1) {
                sleep_time += 2;
            } else {
                sleep_time += 4;
            }
            sleep(sleep_time); // Simulate some work in the child process
            printf("Child %d (PID=%d) is exiting.\n", i, getpid());
            exit(0);
        }
    }

    // Parent process
    printf("Parent process (PID=%d) created three child processes.\n", getpid());

    // Wait for a specific child (e.g., the second child with index 1)
    int specific_child_index = 1;
    pid_t specific_child_pid = child_pid[specific_child_index];
    
    printf("Parent process is waiting for Child %d (PID=%d).\n", specific_child_index, specific_child_pid);
    
    // Use waitpid to wait for the specific child
    if (waitpid(specific_child_pid, &status, 0) == -1) {
        perror("Error waiting for child process");
        return 1;
    }
    
    if (WIFEXITED(status)) {
        printf("Parent process received status from Child %d: %d\n", specific_child_index, WEXITSTATUS(status));
    }

    // Parent can continue its execution after waiting
    printf("Parent process is continuing.\n");

    printf("Parent process is exiting.\n");

    return 0;
}
