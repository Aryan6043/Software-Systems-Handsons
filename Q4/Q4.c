#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

int main(void) {
    int fd;
    fd = open("/home/aryan/Documents/Workspace/Software-Systems/Q4/Temp/my_file.txt", O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error opening a file");
        return 1;
    }

    printf("fd = %d\n", fd);

    close(fd);
    return 0;
}