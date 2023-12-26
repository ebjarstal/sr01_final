#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int id = fork();

    if (id == 0) {
        sleep(1);
    }

    printf("ID actuel: %d\nID du ps père: %d\n", getpid(), getppid());

    int res = wait(NULL);
    if (res == -1) {
        printf("Pas de ps fils en attente\n");
    }
    else {
        printf("Fin d'exécution de %d\n", res);
    }

    return 0;
}