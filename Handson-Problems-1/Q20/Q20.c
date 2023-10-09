#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    int currentPriority, newPriority;

    // Get the current priority
    currentPriority = getpriority(PRIO_PROCESS, 0);
    printf("Current Priority = %d\n", currentPriority);

    // Change the priority using nice
    nice(5);

    // Get the new priority
    newPriority = getpriority(PRIO_PROCESS, 0);
    printf("New Priority = %d\n", newPriority);

    return 0;
}
