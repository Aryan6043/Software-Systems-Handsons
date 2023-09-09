#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    // Change the working directory to the desired location
    chdir("/home/aryan/Documents/Workspace/Software Systems/Q3/Temp");

    // Path to the file to be created
    const char *filename = "my_file.txt";

    // Create the file using creat() system call
    int fd = creat(filename, 0644); // 0644 represents file permissions

    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    printf("File created successfully with file descriptor: %d\n", fd);

    // Close the file descriptor
    close(fd);

    return 0;
}