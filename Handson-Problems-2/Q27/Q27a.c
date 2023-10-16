/*
============================================================================
Name : Q27a.c
Author : Aryan Yadav
Description : 
    Write a program to receive messages from the message queue.
    a. with 0 as a flag
Date: 13th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main() {
    struct msg {
        long int m_type;
        char message[80];
    } myq;

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

    printf("Enter message type: ");
    scanf("%ld", &myq.m_type);

    int ret = msgrcv(mqid, &myq, sizeof(myq.message), myq.m_type, 0);
    if (ret == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Message type: %ld\nMessage: %s\n", myq.m_type, myq.message);
    return 0;
}
