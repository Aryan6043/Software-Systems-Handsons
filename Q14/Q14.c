#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid arguments passed through command line.\n");
        return 0;
    }

    printf("Enter Choice: \n");
    printf("1. stat\n");
    printf("2. lstat\n");
    printf("3. fstat\n");

    int choice;
    printf("Enter Choice: ");
    scanf("%d", &choice);

    struct stat st, lst, fst;

    if (choice == 1) {
        if (stat(argv[1], &st) == -1) {
            printf("No stat\n");
            return 0;
        }
        if (S_ISREG(st.st_mode)) {
            printf("Regular File\n");
        } else if (S_ISDIR(st.st_mode)) {
            printf("Directory File\n");
        } else if (S_ISBLK(st.st_mode)) {
            printf("Block File\n");
        } else if (S_ISCHR(st.st_mode)) {
            printf("Character File\n");
        } else if (S_ISLNK(st.st_mode)) {
            printf("Symbolic Link\n");
        } else if (S_ISSOCK(st.st_mode)) {
            printf("Socket\n");
        } else if (S_ISFIFO(st.st_mode)) {
            printf("Fifo File\n");
        } else {
            printf("Unknown\n");
        }
    } else if (choice == 2) {
        if (lstat(argv[1], &lst) == -1) {
            printf("No lstat\n");
            return 0;
        }
        if (S_ISREG(lst.st_mode)) {
            printf("Regular File\n");
        } else if (S_ISDIR(lst.st_mode)) {
            printf("Directory File\n");
        } else if (S_ISBLK(lst.st_mode)) {
            printf("Block File\n");
        } else if (S_ISCHR(lst.st_mode)) {
            printf("Character File\n");
        } else if (S_ISLNK(lst.st_mode)) {
            printf("Symbolic Link\n");
        } else if (S_ISSOCK(lst.st_mode)) {
            printf("Socket\n");
        } else if (S_ISFIFO(lst.st_mode)) {
            printf("Fifo File\n");
        } else {
            printf("Unknown");
        }
    } else if (choice == 3) {
        int fd = open(argv[1], O_RDONLY);
        if (fstat(fd, &fst) == -1) {
            printf("No fstat\n");
            close(fd);
            return 0;
        }
        if (S_ISREG(fst.st_mode)) {
            printf("Regular File\n");
        } else if (S_ISDIR(fst.st_mode)) {
            printf("Directory File\n");
        } else if (S_ISBLK(fst.st_mode)) {
            printf("Block File\n");
        } else if (S_ISCHR(fst.st_mode)) {
            printf("Character File\n");
        } else if (S_ISLNK(fst.st_mode)) {
            printf("Symbolic Link\n");
        } else if (S_ISSOCK(fst.st_mode)) {
            printf("Socket\n");
        } else if (S_ISFIFO(fst.st_mode)) {
            printf("Fifo File\n");
        } else {
            printf("Unknown\n");
        }
        close(fd);
    } else {
        printf("NOT VALID CHOICE\n");
    }

    return 0;
}
