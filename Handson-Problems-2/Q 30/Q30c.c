/*
============================================================================
Name: Q30c.c
Author: Aryan Yadav
Description:
    Write a program to create shared memory.
    c. Detach the shared memory.
Date: 15th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
    int key, shmid;
    char *data;

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

    data = shmat(shmid, 0, 0);
    if (data == (void *)-1) {
        perror("shmat returns");
        return 1;
    }

    int k = shmdt(data);
    if (k == -1) {
        perror("shmdt returns");
        return 1;
    }
    
    return 0;
}
