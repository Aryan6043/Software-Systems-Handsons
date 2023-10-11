/*
============================================================================
Name : Q14.c
Author : Aryan Yadav
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 9th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];
    char write_buffer[50];
    char read_buffer[50];

    if (pipe(pipe_fd) == -1) {
        printf("Error creating a pipe\n");
    }

    printf("Enter message:\n");
    scanf("%[^\n]s", write_buffer);

    size_t bytes_written = write(pipe_fd[1], write_buffer, sizeof(write_buffer)); // writing into pipe
    if (bytes_written == -1) {
        perror("returns:");
        close(pipe_fd[1]);
        return 1;
    }

    int fd_read = read(pipe_fd[0], read_buffer, sizeof(read_buffer)); // reading from pipe
    if (fd_read == -1) {
        perror("returns");
        close(pipe_fd[0]);
        return 1;
    }

    printf("Message received from pipe: %s\n", read_buffer);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    return 1;
}
