#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct Journey {
    int journey_id;
    int seat_count;
};

int main() {
    int fd, input;
    fd = open("/home/aryan/Documents/Workspace/Software-Systems/Q18/Test/file.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    printf("Select journey number: 1, 2, 3\n");
    scanf("%d", &input);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (input - 1) * sizeof(struct Journey);
    lock.l_len = sizeof(struct Journey);
    lock.l_pid = getpid();
    printf("Before entering critical section\n");
    
    fcntl(fd, F_SETLKW, &lock);

    struct Journey journey;
    lseek(fd, (input - 1) * sizeof(struct Journey), SEEK_SET);
    read(fd, &journey, sizeof(struct Journey));
    
    printf("Current seat count is: %d\n", journey.seat_count);

    journey.seat_count++;

    lseek(fd, -1 * sizeof(struct Journey), SEEK_CUR);
    write(fd, &journey, sizeof(struct Journey));
    printf("To book seat, press enter\n");
    getchar();
    getchar();
    printf("Unlocked\n");

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Booked seat count is: %d\n", journey.seat_count);

    close(fd);
    return 0;
}