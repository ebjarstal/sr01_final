#include <stdio.h>
#include <signal.h>

void handle_sigtstp(int sig) {
    printf(" Stop not allowed\n");
}

void handle_sigcont(int sig) {
    printf("Entrer nombre: ");
    fflush(stdout);
}

int main(void) {
    struct sigaction sa;
    sa.sa_handler = &handle_sigcont;
    sa.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa, NULL);
    sigaction(SIGCONT, &sa, NULL);

    // signal(SIGTSTP, &handle_sigtstp);

    int x;
    printf("Entrer nombre: ");
    scanf("%d", &x);
    printf("%d\n", 4*x);

    return 0;
}
