#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {

    const char *filename = "output.txt";
    int fd;

    // Open the file for writing (create if it doesn't exist)
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error forking");
        return 1;
    }

    if (pid == 0) {
        // Child process
        const char *childMessage = "Hello from child process!\n";
        write(fd, childMessage, strlen(childMessage));
        close(fd);
        exit(0);
    } else {
        // Parent process
        const char *parentMessage = "Hello from parent process!\n";
        write(fd, parentMessage, strlen(parentMessage));
        close(fd);

        // Wait for the child to complete
        wait(NULL);
    }

    close(fd);

    return 0;
}
