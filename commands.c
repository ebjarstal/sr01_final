#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(void) {
    int pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
        if (err == -1) {
            printf("Could not find program to execute.\n");
            return 2;
        }
    } else {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            int statusCode = WEXITSTATUS(wstatus);
            if (statusCode == 0) {
                printf("Command executed succesfully.\n");
            } else {
                printf("Command exited with error %d.\n", statusCode);
            }
        }
        printf("Some post processing goes here!\n");
    }

    return 0;
}