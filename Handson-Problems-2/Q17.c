/*
============================================================================
Name : Q17.c
Author : Aryan Yadav
Description :
    Write a program to execute ls -l | wc.
        a. use dup
        b. use dup2
        c. use fcntl
Date: 9th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void executeWithDup(int fd[]) {
    if (!fork()) {
        close(1); // close STDOUT
        close(fd[0]);
        dup(fd[1]);
        execlp("ls", "ls", "-l", NULL); // execlp() will write the output of "ls -l" to fd with value = 1
    } else {
        close(0); // close STDIN
        close(fd[1]);
        dup(fd[0]);
        execlp("wc", "wc", NULL); // execlp() will read input from fd with value = 0 (read-end of pipe) as input to “wc” command
        // and show output to fd with value = 1 => STDOUT
    }
}

void executeWithDup2(int fd[]) {
    if (!fork()) {
        close(1);
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("ls", "ls", "-l", NULL);
    } else {
        close(0);
        close(fd[1]);
        dup2(fd[0], 0);
        execlp("wc", "wc", NULL);
    }
}

void executeWithFcntl(int fd[]) {
    if (!fork()) {
        close(1);
        close(fd[0]);
        fcntl(fd[1], F_DUPFD, 1);
        execlp("ls", "ls", "-l", NULL);
    } else {
        close(0);
        close(fd[1]);
        fcntl(fd[0], F_DUPFD, 0);
        execlp("wc", "wc", NULL);
    }
}

int main() {
    int pipe_fd[2];
    pipe(pipe_fd);
    int choice;
    printf("Select one:\n");
    printf("1. dup\t2. dup2\t3. fcntl\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            executeWithDup(pipe_fd);
            break;
        case 2:
            executeWithDup2(pipe_fd);
            break;
        case 3:
            executeWithFcntl(pipe_fd);
            break;
        default:
            printf("Please enter the correct choice\n");
    }
}
