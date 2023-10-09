#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int policy;
    struct sched_param param;

    // Get the current scheduling policy and parameters
    pid_t pid = getpid();
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy: ");
    switch (policy) {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }

    // Modify the scheduling policy to SCHED_FIFO
    param.sched_priority = 50;  // Priority for SCHED_FIFO
    if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        return 1;
    }

    printf("Scheduling policy modified to SCHED_FIFO.\n");

    // Get the new scheduling policy
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy: ");
    switch (policy) {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }

    return 0;
}
