/*
============================================================================
Name : Q24.c
Author : Aryan Yadav
Description : 
    Write a program to create a message queue and print the key and message queue id.
Date: 12th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main() {
    key_t key = ftok(".", 'a'); // Generate a unique key with proj_id 'a'

    int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0666); // Create a message queue with permissions 0666

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    printf("key=0x%x\tmsgid=%d\n", key, msgid); // Print the key and message queue ID

    return 0;
}
