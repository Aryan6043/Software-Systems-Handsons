/*
============================================================================
Name : Q23.c
Author : Aryan Yadav
Description : 
    Write a program to print the maximum number of files that can be opened within a process and the size of a pipe (circular buffer).
Date: 12th OCt 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    long PIPE_BUF, OPEN_MAX;

    PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
    OPEN_MAX = sysconf(_SC_OPEN_MAX);
    
    if (PIPE_BUF == -1) {
        perror("pathconf");
        return 1;
    }
    
    if (OPEN_MAX == -1) {
        perror("sysconf");
        return 1;
    }

    printf("Max number of files that can be opened within a process: %ld\n", OPEN_MAX);
    printf("Max amount of data that can be written to a pipe or FIFO atomically is: %ld\n", PIPE_BUF);
    return 0;
}
