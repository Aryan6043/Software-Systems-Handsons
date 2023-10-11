/*
============================================================================
Name : Q15.c
Author : Aryan Yadav
Description : Write a simple program to send some data from parent to the child process.
Date: 9th Oct 2023.
============================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>

int main() {
  char message[80];
  int pipe_fd[2];
  pipe(pipe_fd);
  if(fork()){
     close(pipe_fd[0]); // Close read-end of pipe for parent
     printf("Enter message to the child: ");
     scanf(" %[^\n]", message); 
     write(pipe_fd[1], message, sizeof(message));
  }
  else{
    close(pipe_fd[1]); // Close write-end of pipe for child
    read(pipe_fd[0], message, sizeof(message));
    printf("Message from parent: %s\n", message);
  }
  wait(0); // Wait till all children have terminated
}
