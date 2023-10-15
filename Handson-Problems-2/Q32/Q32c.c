/*
============================================================================
Name: Q32c.c
Author: Aryan Yadav
Description:
    Write a program to implement a semaphore to protect any critical section.
    c. Protect multiple pseudo resources (may be two) using a counting semaphore
Date: 15th Oct 2023.
============================================================================
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void main() {
    char *filename = "sample.txt";
    char data[16]; // Sample data

    union semun {
        int val;
    } semvar;

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error while opening the file");
        return;
    }

    key_t key = ftok(".", 324);
    if (key == -1) {
        perror("ftok returns");
        return;
    }

    int semid = semget(key, 1, 0);
    if (semid == -1) {
        semid = semget(key, 1, IPC_CREAT | 0700);
        if (semid == -1) {
            perror("semget returns");
            return;
        }

        semvar.val = 2; // Set a counting semaphore
        int semctlflag = semctl(semid, 0, SETVAL, semvar);
        if (semctlflag == -1) {
            perror("semctl returns");
            return;
        }
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_flg = IPC_NOWAIT;

    printf("Press enter to obtain a lock for the critical section!\n");
    getchar();

    // Use semaphore to lock the critical section
    semOp.sem_op = -1;
    int semopflag = semop(semid, &semOp, 1);
    if (semopflag == -1) {
        perror("semop returns");
        return;
    }

    printf("Obtained a lock on the critical section!\n");
    printf("Now entering the critical section!\n");

    int read_bytes = read(fd, &data, 16);
    if (read_bytes == -1) {
        perror("read returns");
        return;
    } else if (read_bytes == 0) {
        printf("No data exists!\n");
    } else {
        printf("Sample data: %s\n", data);
    }

    printf("\nPress the Enter key to exit the critical section!\n");
    getchar();

    // Use semaphore to unlock the critical section
    semOp.sem_op = 1;
    semopflag = semop(semid, &semOp, 1);
    if (semopflag == -1) {
        perror("Error while operating on the semaphore!");
        return;
    }

    close(fd);
}
