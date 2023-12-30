#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#define ERR_FORK 1


void handle_sigusr1(int sig) {
    printf("A multiplication is basically like adding up the same number many times !\n");
}


int main(void) {
    // ask multiplication, have child process give hint after 5 seconds if no answer
    int pid = fork();
    if (pid == -1) {
        return ERR_FORK;
    }

    if (pid == 0) {
        // Child process
        sleep(5);
        kill(getppid(), SIGUSR1);
    }
    else {
        struct sigaction sa = { 0 };
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        int x;
        printf("What's 3x5 ? ");

        do {
            scanf("%d", &x);
            if (x == 15) {
                printf("Correct!\n");
            } else {
                printf("Wrong!\n");
            }
        } while (x != 15);

        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}