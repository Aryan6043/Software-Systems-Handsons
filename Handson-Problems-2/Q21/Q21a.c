/*
============================================================================
Name : Q21a.c
Author : Aryan Yadav
Description : 
    Write two programs so that both can communicate by FIFO - Use two-way communication.
    In this file process 1 is writing first and reading from process 2 through the pipe 
Date: 12th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char message_to_send[50];
    char received_message[50]; 
   
    int write_fd = open("myfifo1", O_WRONLY);
    int read_fd = open("myfifo2", O_RDONLY);
    if (write_fd == -1 || read_fd == -1) {
        printf("Unable to open FIFO files\n");
        return 1;
    }
   
    printf("Enter the text to send:\n");
    scanf(" %[^\n]", message_to_send);
   
    int bytes_written = write(write_fd, message_to_send, sizeof(message_to_send));
    if (bytes_written == -1) {
        perror("write");
        close(write_fd);
        close(read_fd);
        return 1;
    }
   
    int bytes_read = read(read_fd, received_message, sizeof(received_message));
    if (bytes_read == -1) {
        perror("read");
        close(write_fd);
        close(read_fd);
        return 1;
    }
    printf("The text from program 2 is: %s\n", received_message);
    close(write_fd);
    close(read_fd);
    return 0;
}
