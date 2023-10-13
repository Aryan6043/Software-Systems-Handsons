/*
============================================================================
Name : Q30a.c
Author : Aryan Yadav
Description : 
    Write a program to create shared memory.
    a. Write some data to the shared memory
Date: 13th Oct 2023.
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
        perror("ftok");
        return 1;
    }

    shmid = shmget(key, 1024, IPC_CREAT | 0744);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    data = shmat(shmid, 0, 0);
    printf("Enter the text: ");
    scanf(" %[^\n]", data);

    return 0;
}
