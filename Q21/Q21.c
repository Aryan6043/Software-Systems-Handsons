#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Fork a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        printf("Below statement prints due to child process\n");
        printf("Child process: PID = %d\n", getpid());
    } else {
        printf("Below statement prints due to parent process\n");
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), child_pid);
    }
    
    return 0;
}
