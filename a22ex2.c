#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#define ERR_FORK 1

int t = 4;

void handle_sigusr1(int sig) {
    int temp = rand() % 31 + 10;
    printf("\nTempérature: %d°C\n", temp);
}

void handle_sigalrm(int sig) {
    alarm(t);
}

int main(void) {
    // prélèvement chaque 5 secondes
    // entre deux mesures, barre de progression
    // utiliser une alarme avec SIGALRM
    // thermomètre -> processus fils. Endormi dans une boucle pause() et se réveille avec l'alarme pour
    // mesurer la température. La temp est un entier random entre 10 et 40.
    // Utiliser handlers, SIGALRM et SIGUSR1

    int n = 5;
    srand(time(NULL));

    struct sigaction sa = { 0 };
    sa.sa_handler = &handle_sigusr1;
    sigaction(SIGUSR1, &sa, NULL);

    struct sigaction sa_alarm = { 0 };
    sa_alarm.sa_handler = &handle_sigalrm;
    sigaction(SIGALRM, &sa_alarm, NULL);

    int pid = fork();
    if (pid == -1) {
        return ERR_FORK;
    }

    if (pid == 0) {
        // Child process
        while (1) {
            pause();
        }
    }
    else {
        // Parent process
        alarm(t);
        do {
            printf("Mesure en cours");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(1);
            kill(pid, SIGUSR1);
            sleep(1);
            n--;
        } while (n > 0);

        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}