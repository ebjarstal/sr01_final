#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

#define ERR_FORK 1

void mesurer_temperature() {
    printf("Temp: 13°C\n");
}

int main(void) {
    int pid = fork();

    if (pid == -1) {
        return ERR_FORK;
    }
    else if (pid == 0) {
        while (1) {
            mesurer_temperature();
            sleep(5);
        }
    }
    else {
        kill(pid, SIGSTOP);
        char c;
        printf("Démarrer thermomètre ? (y/n): ");
        scanf("%c", &c);
        if (c == 'y') {
            kill(pid, SIGCONT);
        } else {
            kill(pid, SIGKILL);
            printf("Thermomètre éteint.\n");
        }
        wait(NULL);
    }

    return 0;
}