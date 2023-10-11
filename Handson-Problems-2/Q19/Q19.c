/*
============================================================================
Name: Q19.c
Author: Aryan Yadav
Description:
    Create a FIFO file using different methods and evaluate their performance.
    a. mknod command
    b. mkfifo command
    c. Compare with strace
    d. Use mknod system call
    e. Use mkfifo library function
Date: 9th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    // a. mknode command --> mknod pipe_name p

    // b. mkfifo command --> mkfifo pipe_name

    // c. comparision with strace:
    //    $ strace mknod pipe_name p
    //    $ strace mkfifo pipe_name

    // d. mknod system call
    int result = mknod("mknod_fifo", S_IFIFO, 0);
    if (result < 0)
        perror("mknod error");

    // e. mkfifo library function
    result = mkfifo("mkfifo_fifo", 0744);
    if (result < 0)
        perror("mkfifo error");

    return 1;
}
