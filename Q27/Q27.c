#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Using execl
    execl("/bin/ls", "ls", "-Rl", NULL);

    // Using execlp
    execlp("ls", "ls", "-Rl", NULL);

    // Using execle
    char *envp[] = {NULL};
    execle("/bin/ls", "ls", "-Rl", NULL, envp);

    // Using execv
    char *args[] = {"/bin/ls", "-Rl", NULL};
    execv("/bin/ls", args);

    // Using execvp
    execvp("ls", args);

    // If any of the exec calls succeed, the code below won't be executed
    perror("exec failed");
    return 1;
}
