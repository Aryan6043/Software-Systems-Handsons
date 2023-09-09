#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void runScript() {
    // Replace this with the command to run your script
    system("/home/aryan/Documents/Workspace/Software-Systems/Q30/script.sh");
}

int main() {
    time_t now, actual;
    struct tm *deadline;

    // Get the current time
    time(&now);
    deadline = localtime(&now);

    // Set the desired execution time (e.g., 22:31:00)
    deadline->tm_hour = 18;
    deadline->tm_min = 6;
    deadline->tm_sec = 10;

    // Convert the desired time to a time_t value
    actual = mktime(deadline);

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child's PID: %d, Parent's PID: %d\n", getpid(), getppid());
        printf("Waiting until the scheduled time...\n");
        
        // Wait until the scheduled time
        while (difftime(actual, time(NULL)) > 0) {
            sleep(1);
        }

        printf("Time matched\n");

        // Execute the script
        runScript();
        exit(0);
    } else {
        // Parent process
        printf("Parent %d is going to exit\n", getpid());
        return 0;
    }
}
