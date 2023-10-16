/*
============================================================================
Name : Q25.c
Author : Aryan Yadav
Description : 
    Write a program to print a message queue's attributes using msqid_ds and ipc_perm structures.
    a. Access permission
    b. User ID, Group ID
    c. Time of last message sent and received
    d. Time of last change in the message queue
    e. Size of the queue
    f. Number of messages in the queue
    g. Maximum number of bytes allowed
    h. Process ID of the last msgsnd and msgrcv
Date: 12th Oct 2023.
============================================================================
*/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main() {
    struct msqid_ds ds;
  
    key_t key = ftok(".", 'b'); 
    if (key == -1) {
        perror("ftok");
        return 1;
    }
  
    int msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0744);
    if (msqid == -1) {
        perror("msgget");
        return 1;
    } 
  
    if (msgctl(msqid, IPC_STAT, &ds) == -1) {
        perror("msgctl");
        return 1;
    } else {
        printf("Permissions: %o\n", ds.msg_perm.mode);
        printf("User ID: %d\n", ds.msg_perm.uid);
        printf("Group ID: %d\n", ds.msg_perm.gid);
        printf("Time of last message sent: %ld\n", ds.msg_stime);
        printf("Time of last message received: %ld\n", ds.msg_rtime);
        printf("Time of last change in the message queue: %ld\n", ds.msg_ctime);
        printf("Size of the queue: %ld\n", ds.__msg_cbytes);
        printf("Number of messages in the queue: %ld\n", ds.msg_qnum);
        printf("Maximum number of bytes allowed: %ld\n", ds.msg_qbytes);
        printf("Process ID of the last msgsnd: %d\n", ds.msg_lspid);
        printf("Process ID of the last msgrcv: %d\n", ds.msg_lrpid);
    }
}
