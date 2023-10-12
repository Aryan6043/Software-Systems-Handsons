/*
============================================================================
Name : Q21b.c
Author : Aryan Yadav
Description : 
    Write two programs so that both can communicate by FIFO - Use two-way communication.
    In this file process 2 is reading first and writing to process 1 through the pipe 
Date: 12th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char received_message[50];
    char message_to_send[50]; 

    int read_fd = open("myfifo1", O_RDONLY);
    int write_fd = open("myfifo2", O_WRONLY);
    if (read_fd == -1 || write_fd == -1) {
        printf("Unable to open FIFO files\n");
        return 1;
    }

    int bytes_read = read(read_fd, received_message, sizeof(received_message));
    if (bytes_read == -1) {
        perror("read");
        close(read_fd);
        close(write_fd);
        return 1;
    }
    printf("The text from program 1 is: %s\n", received_message);

    printf("Enter the text:\n");
    scanf(" %[^\n]", message_to_send);

    int bytes_written = write(write_fd, message_to_send, sizeof(message_to_send));
    if (bytes_written == -1) {
        perror("write");
        close(read_fd);
        close(write_fd);
        return 1;
    }

    close(read_fd);
    close(write_fd);
    return 1;
}
