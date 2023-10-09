#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s source_file destination_file\n", argv[0]);
        return 1;
    }

    int fd_read = open(argv[1], O_RDONLY);
    int fd_write = open(argv[2], O_WRONLY | O_CREAT, 0644); // 0644 represents file permissions

    if (fd_read == -1 || fd_write == -1) {
        perror("Error opening files");
        return 1;
    }

    while (1) {
        char buf;
        int char_read = read(fd_read, &buf, 1);
        if (char_read == 0) break; // 0 symbolises end of file
        int char_written = write(fd_write, &buf, 1);
        if (char_written != 1) {
            perror("Error writing to file");
            close(fd_read);
            close(fd_write);
            return 1;
        }
    }

    int fd_read_close = close(fd_read);
    int fd_write_close = close(fd_write);

    if (fd_read_close == -1 || fd_write_close == -1) {
        perror("Error closing files");
        return 1;
    }

    printf("File copied successfully.\n");

    return 0;
}