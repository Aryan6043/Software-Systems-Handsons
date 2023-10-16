/*
============================================================================
Name : Q28.c
Author : Aryan Yadav
Description : 
    Write a program to change the existing message queue permission. (use msqid_ds structure)
Date: 13th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int mqid = msgget(key, 0);
    if (mqid == -1) {
        perror("msgget");
        return 1;
    }

    struct msqid_ds msq_info;
    if (msgctl(mqid, IPC_STAT, &msq_info) == -1) {
        perror("msgctl");
        return 1;
    }

    // Change the message queue permissions to 0666
    msq_info.msg_perm.mode = 0666;
    if (msgctl(mqid, IPC_SET, &msq_info) == -1) {
        perror("msgctl");
        return 1;
    }

    printf("Message queue permissions have been updated.\n");
    printf("New permissions: %o\n", msq_info.msg_perm.mode);

    return 0;
}
