#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int stdout_fd = open("/dev/tty", O_WRONLY);
    if (stdout_fd == -1) {
        perror("open /dev/tty");
        return 1;
    }

    int fd = open("tmp.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open tmp.txt");
        return 2;
    }

    // Redirect stdout to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 3;
    }
    close(fd);
    printf("To file.\n");

    // Associate the file descriptor with the stdout stream
    if (freopen("/dev/tty", "w", stdout) == NULL) {
        perror("freopen");
        return 4;
    }

    // Print to the console
    printf("In console.\n");

    return 0;
}
