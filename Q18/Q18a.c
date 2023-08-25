#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

struct Trip {
    int trip_id;
    int seat_count;
};

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct Trip trips[3]; // Array to store trip data

    for (int i = 0; i < 3; i++) {
        trips[i].trip_id = i + 1;
        trips[i].seat_count = 0;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    ssize_t bytes_written = write(fd, trips, sizeof(trips));
    if (bytes_written == -1) {
        perror("Error writing into the file");
        close(fd);
        return 1;
    }

    int close_result = close(fd);
    if (close_result == -1) {
        perror("Error closing the file");
        return 1;
    }

    printf("File '%s' initialized with trip data.\n", argv[1]);
    return 0;
} 