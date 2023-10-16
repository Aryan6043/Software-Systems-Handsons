/*
============================================================================
Name : Q26.c
Author : Aryan Yadav
Description : 
    Write a program to send messages to the message queue. Check $ipcs -q
Date: 13th Oct 2023
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
  
    int mqid = msgget(key, IPC_CREAT | 0700);
    if (mqid == -1) {
        perror("msgget");
        return 1;
    }
  
    printf("Enter message type: ");
    scanf("%ld", &myq.m_type);
  
    printf("Enter message text: ");
    scanf(" %[^\n]", myq.message); // Remove the 's' to read the message correctly
  
    int size = strlen(myq.message);
    int y = msgsnd(mqid, &myq, size + 1, 0);
    if (y == -1) {
        perror("msgsnd");
        return 1;
    }
  
    printf("Message sent successfully!!\n");
    return 0;
}
