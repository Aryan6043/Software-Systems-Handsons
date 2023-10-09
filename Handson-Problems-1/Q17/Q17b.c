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

    struct flock lck;
    
    // Set lock attributes
    lck.l_type = F_WRLCK;
    lck.l_whence = SEEK_SET;
    lck.l_start = 0;
    lck.l_len = 0; 
    
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    lck.l_type = F_WRLCK;
    lck.l_whence = SEEK_SET;
    lck.l_start = 0;
    lck.l_len = 0;
    lck.l_pid = getpid();

    printf("Before entering the critical section\n");
    fcntl(fd, F_SETLKW, &lck);
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

    lck.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lck);

    printf("FINISH\n");
    close(fd);
    return 0;
}
