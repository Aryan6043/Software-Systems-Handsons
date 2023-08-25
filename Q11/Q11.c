#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file_path> <data_to_append>\n", argv[0]);
        return 1;
    }

    // Opening a file
    int fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error opening a file");
        return 1;
    }

    // Copy data to a local variable
    char a[sizeof(argv[2])];
    strncpy(a, argv[2], sizeof(argv[2]));

    // Appending data into the file using the original descriptor
    ssize_t bytes = write(fd, a, sizeof(a) - 1);
    if (bytes == -1) {
        perror("Error appending data using the file descriptor");
        close(fd);
        return 1;
    }

    // Creating a duplicate descriptor using dup()
    int new_fd1 = dup(fd);
    bytes = write(new_fd1, a, sizeof(a) - 1);
    if (bytes == -1) {
        perror("Error appending data using dup() descriptor");
        close(new_fd1);
        return 1;
    } else {
        printf("Appended data successfully using dup() file descriptor\n");
    }

    // Creating a duplicate descriptor using dup2()
    int new_fd2 = dup2(fd, 4);
    bytes = write(new_fd2, a, sizeof(a) - 1);
    if (bytes == -1) {
        perror("Error appending data using dup2() descriptor");
        close(new_fd2);
        return 1;
    } else {
        printf("Appended data successfully using dup2() file descriptor\n");
    }

    // Creating a duplicate descriptor using fcntl()
    int new_fd3 = fcntl(fd, F_DUPFD, 5);
    bytes = write(new_fd3, a, sizeof(a) - 1);
    if (bytes == -1) {
        perror("Error appending data using fcntl()");
        close(new_fd3);
        return 1;
    } else {
        printf("Appended data successfully using fcntl file descriptor\n");
    }

    // Closing the file
    int close_fd = close(fd);
    if (close_fd == -1) {
        perror("Error closing the file");
        return 1;
    }

    return 0;
}