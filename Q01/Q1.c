#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    // Change the working directory to the desired location
    chdir("/home/aryan/Documents/Workspace/Software-Systems/Temp2");

    int v = symlink("/home/aryan/Documents/Workspace/Software-Systems/Q1.md", "softlink");
    if (v < 0) {
        perror("Failed ");
        return 1;
    }

    int f = link("/home/aryan/Documents/Workspace/Software-Systems/Q1.md", "hardlink");
    if (f < 0) {
        perror("Failed ");
        return 1;
    }

    int e = mkfifo("fifo_file", 0666);
    if (e < 0) {
        perror("Failed ");
        return 1;
    }

    return 0;
}
