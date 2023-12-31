#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    printf("Waiting for input from STDIN for 10 seconds...\n");
    
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    
    int select_result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    
    if (select_result == -1) {
        perror("Error in select");
        return 1;
    }
    
    if (select_result == 0) {
        printf("Timeout reached, no data received within 10 seconds.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            printf("Data is available within 10 seconds!\n");
            char input[256];
            if (fgets(input, sizeof(input), stdin)) {
                input[strcspn(input, "\n")] = '\0'; // Removes newline character
                printf("You entered: %s\n", input);
            }
        }
    }
    
    return 0;
}
