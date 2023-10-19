/*
============================================================================
Name: Q30d.c
Author: Aryan Yadav
Description:
    Write a program to create shared memory.
    d. Remove the shared memory.
Date: 15th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
    int key, shmid;

    key = ftok(".", 'b');
    if (key == -1) {
        perror("ftok returns");
        return 1;
    }

    shmid = shmget(key, 1024, 0);
    if (shmid == -1) {
        perror("shmget returns");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl returns");
        return 1;
    }

    return 0; // Return 0 to indicate success
}
