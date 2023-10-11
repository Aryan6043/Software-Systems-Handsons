/*
============================================================================
Name : Q18.c
Author : Aryan Yadav
Description :
    Write a program to find out the total number of directories in the current directory.
    Execute ls -l | grep ^d | wc using only dup2.
Date: 9th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int pipe_ls[2], pipe_grep[2];

    // This child will only be used for writing the output of "ls -l" to pipe_ls[1] (STDOUT)
    if (!fork()) {
        dup2(pipe_ls[1], 1);
        close(pipe_ls[0]);
        close(pipe_grep[0]);
        close(pipe_grep[1]);
        execlp("ls", "ls", "-l", NULL);
    } else {
        // This child is responsible for running "ls -l | grep ^d" where input is received from pipe_ls[0] (STDIN) and output
        // is written to pipe_grep[1] (STDOUT)
        if (!fork()) {
            dup2(pipe_grep[1], 1);
            dup2(pipe_ls[0], 0);
            close(pipe_ls[1]);
            close(pipe_grep[0]);
            execlp("grep", "grep", "^d", NULL);
        }
        // This parent is responsible for running "ls -l | grep ^d | wc" where input is received from pipe_grep[0] (STDIN)
        // and output is written to STDOUT
        else {
            dup2(pipe_grep[0], 0);
            close(pipe_grep[1]);
            close(pipe_ls[0]);
            close(pipe_ls[1]);
            execlp("wc", "wc", NULL);
        }
    }
}
