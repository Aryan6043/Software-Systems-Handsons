#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

struct Ticket {
    int t_num;
} ticket;

int main(int argc, char *argv[]) {

    struct flock lock;
    
    // Set lock attributes
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; 
    
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Before entering the critical section\n");
    fcntl(fd, F_SETLKW, &lock);
    printf("Inside Critical Section\n");
    printf("Press enter to unlock\n");

    read(fd, &ticket, sizeof(ticket));
    printf("\nTicket number is: %d", ticket.t_num);
    ticket.t_num++;
    lseek(fd, 0, SEEK_SET);
    int fd_write = write(fd, &ticket, sizeof(ticket));
    if (fd_write == -1) {
        perror("Error writing to the file");
        close(fd);
        return 1;
    }

    getchar();
    printf("Unlocked\n");

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("FINISH\n");
    close(fd);
    return 0;
}
