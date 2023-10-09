#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    struct flock lock;
    int fd;

    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Before entering the critical section\n");

    fcntl(fd, F_SETLKW, &lock);

    printf("Inside Critical Section\n");
    printf("Press enter to unlock\n");
    getchar();

    printf("Unlocked\n");

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("FINISH\n");
    close(fd);

    return 0;
}
