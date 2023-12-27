#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    int id1 = fork();
    int id2 = fork();

    if (id1 == 0) {  // si c'est le fils direct issu du premier fork
        if (id2 == 0) {  // si c'est le fils (issu du second fork) du fils issu du premier fork
            printf("ID du fils du fils du premier fork: %d / ID père: %d\n", getpid(), getppid());
        }
        else {
            printf("ID du fils direct issu du premier fork: %d / ID père: %d\n", getpid(), getppid());
        }
    }
    else {
        if (id2 == 0) {  // si c'est le fils direct issu du second fork
            printf("ID du fils direct issu du second fork: %d / ID père: %d\n", getpid(), getppid());
        }
        else {
            printf("ID du processus principal: %d / ID père: %d\n", getpid(), getppid());
        }
    }

    while (wait(NULL) != -1 || errno != ECHILD) {
        printf("Le programme a attendu qu'un processus fils se termine.\n");

    }

    return 0;
}