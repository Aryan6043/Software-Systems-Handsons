/*
============================================================================
Name : fifo_reader.c
Author : Aryan Yadav
Description : 
    Write two programs so that both can communicate by FIFO - Use one-way communication.
    (This file is for reading through the pipe)
Date: 30th Sept 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char message[50];
    
    int fd = open("myfifo", O_RDONLY);
    if (fd == -1) {
        printf("Error opening pipe\n");
        return 1;
    }
    
    int bytes_read = read(fd, message, sizeof(message));
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    
    printf("%s\n", message);
    close(fd);  
    return 0;  
}
