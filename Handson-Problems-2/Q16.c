/*
============================================================================
Name : Q16.c
Author : Aryan Yadav
Description : Write a program to send and receive data from parent to child vice versa. Use two-way communication.
Date: 9th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char parentMessage[50];
    char childMessage[50];
    int parentPipe[2];
    int childPipe[2];
    pipe(parentPipe);
    pipe(childPipe);

    if (!fork()) {
        close(parentPipe[0]); // Close read-end of parentPipe for child
        close(childPipe[1]); // Close write-end of childPipe for child

        printf("Enter message to parent: ");
        scanf("%[^\n]", childMessage);

        int writeResult = write(parentPipe[1], childMessage, sizeof(childMessage));
        if (writeResult == -1) {
            perror("write returns:");
            close(parentPipe[1]);
            return 1;
        }

        int readResult = read(childPipe[0], parentMessage, sizeof(parentMessage));
        if (readResult == -1) {
            perror("read returns:");
            close(childPipe[0]);
            return 1;
        }

        printf("Message from parent: %s\n", parentMessage);
    } else {
        close(parentPipe[1]); // Close write-end of parentPipe for parent
        close(childPipe[0]); // Close read-end of childPipe for parent

        int readResult = read(parentPipe[0], childMessage, sizeof(childMessage));
        if (readResult == -1) {
            perror("read returns:");
            close(parentPipe[0]);
            return 1;
        }

        printf("Message from child: %s\n", childMessage);
        printf("Enter message to child: ");
        scanf(" %[^\n]", parentMessage);

        int writeResult = write(childPipe[1], parentMessage, sizeof(parentMessage));
        if (writeResult == -1) {
            perror("write returns:");
            close(childPipe[1]);
            return 1;
        }
    }

    close(parentPipe[0]);
    close(childPipe[1]);
    return 1;
}
