/*
============================================================================
Name: Q32a.c
Author: Aryan Yadav
Description:
    Write a program to implement a semaphore to protect any critical section.
    a. Rewrite the ticket number creation program using a semaphore
Date: 15th Oct 2023.
============================================================================
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void main() {
    char *ticketFile = "ticket_file.txt";
    off_t lseekOffset;
    int data;

    union semun {
        int val;               // Value of the semaphore
        struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
        unsigned short *array; /* Array for GETALL, SETALL */
        struct seminfo *__buf; /* Buffer for IPC_INFO */
    } semvar;

    int fd = open(ticketFile, O_CREAT | O_RDWR, 0600); // Set file permissions to owner-only read and write
    if (fd == -1) {
        perror("open returns");
        return;
    }

    key_t key = ftok(".", 'd');
    if (key == -1) {
        perror("semaphore key returns");
        return;
    }

    int semid = semget(key, 1, 0);
    if (semid == -1) {
        semid = semget(key, 1, IPC_CREAT | 0600); // Set semaphore permissions to owner-only read and write
        if (semid == -1) {
            perror("semget returns");
            return;
        }
        semvar.val = 1; // Set a binary semaphore
        int semctlflag = semctl(semid, 0, SETVAL, semvar);
        if (semctlflag == -1) {
            perror("semctl returns");
            return;
        }
    }

    struct sembuf semOp; // Defines the operation on the semaphore
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to obtain a lock on the critical section\n");
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

    ssize_t read_bytes = read(fd, &data, sizeof(data));
    if (read_bytes == -1) {
        perror("read returns");
        return;
    } else if (read_bytes == 0)
        data = 1;
    else {
        data += 1;
        lseekOffset = lseek(fd, 0, SEEK_SET);
        if (lseekOffset == -1) {
            perror("lseek returns");
            return;
        }
    }

    ssize_t write_bytes = write(fd, &data, sizeof(data));
    if (write_bytes == -1) {
        perror("write returns");
        return;
    }

    printf("Your ticket number is - %d\n", data);
    printf("Press enter to exit from the critical section!\n");
    getchar();

    // Use semaphore to unlock the critical section
    semOp.sem_op = 1;
    semopflag = semop(semid, &semOp, 1);
    if (semopflag == -1) {
        perror("semop returns");
        return;
    }

    close(fd);
}
