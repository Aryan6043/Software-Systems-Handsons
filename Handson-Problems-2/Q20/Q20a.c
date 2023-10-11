/*
============================================================================
Name : Q20a.c
Author : Aryan Yadav
Description : 
    Write two programs so that both can communicate by FIFO -Use one way communication.
    (This file writing through a pipe)
Date: 30th Sept 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char message[50];
    
    int fd = open("myfifo", O_WRONLY);
    if (fd == -1) {
        printf("Error opening pipe\n");
        return 1;
    }
    
    printf("Enter the text:\n");
    scanf(" %[^\n]", message);
    
    int bytes_written = write(fd, message, sizeof(message));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    
    close(fd);
    return 0;
}
