/*
============================================================================
Name: Q30b.c
Author: Aryan Yadav
Description:
    Write a program to create shared memory.
    Attach with O_RDONLY and check whether you are able to overwrite.
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
        perror("ftok");
        return 1;
    }

    shmid = shmget(key, 1024, IPC_CREAT | 0744);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    data = shmat(shmid, 0, SHM_RDONLY);
    if (data == (void *)-1) {
        perror("shmat");
        return 1;
    }

    printf("Enter the text: ");
    scanf("%[^\n]", data);
    
    return 0;
}
