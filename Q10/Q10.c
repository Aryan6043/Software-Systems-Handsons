#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    int fd;
    const char* data1 = "ABCDEFGHIJ";
    const char* data2 = "zyxwvutsrq";

    // Open the file in read-write mode or create if not exists
    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write the first string
    ssize_t bytesWritten = write(fd, data1, strlen(data1));
    if (bytesWritten == -1) {
        perror("Error writing data1");
        close(fd);
        return 1;
    }

    // Move the file pointer by the length of the first string
    off_t newOffset = lseek(fd, strlen(data1) + 10, SEEK_SET);
    if (newOffset == -1) {
        perror("Error seeking file pointer");
        close(fd);
        return 1;
    }

    // Write the second string at the new file pointer position
    bytesWritten = write(fd, data2, strlen(data2));
    if (bytesWritten == -1) {
        perror("Error writing data2");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    printf("Data written and file pointer moved successfully.\n");

    return 0;
}
