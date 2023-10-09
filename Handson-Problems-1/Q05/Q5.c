#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
    // Change the working directory to the desired location
    chdir("/home/aryan/Documents/Workspace/Software-Systems/Q5/Temp");

    while (1) {
        int fd1 = creat("file1", 0744);
        int fd2 = creat("file2", 0744);
        int fd3 = creat("file3", 0744);
        int fd4 = creat("file4", 0744);
        int fd5 = creat("file5", 0744);
        
        // Check for errors in file creation
        if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1 || fd5 == -1) {
            perror("Error creating file");
            return 1;
        }

        // Close the file descriptors
        close(fd1);
        close(fd2);
        close(fd3);
        close(fd4);
        close(fd5);
    }
    
    return 0;
}
