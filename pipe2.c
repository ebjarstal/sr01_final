#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
    /* but du programme: père écrit un entier, fils le lit */
    /* fils le multiplie par 4, père lit le nouveau nombre */
    /* intérêt: communication à double sens avec des pipes */

    int fd[2];

    if (pipe(fd) == -1) {
        return 1;
    }

    int pid = fork();

    if (pid == -1) {
        return 2;
    }
    else if (pid == 0) {
        /* code processus fils */

        int x;

        /* pas besoin de wait car read attend      */
        /* qu'une donnée soit écrite dans le tuyau */
        if (read(fd[0], &x, sizeof(x)) == -1) {
            return 3;
        } printf("Ici le processus fils, j'ai lu %d le tuyau.\n", x);

        x = 4 * x;

        if (write(fd[1], &x, sizeof(x)) == -1) {
            return 4;
        } printf("Ici le processus fils, j'ai écrit %d dans le tuyau.\n", x);

        close(fd[0]); close(fd[1]);
        printf("Ici le fils. Adieu.\n");
    }
    else {
        /* code processus père */

        int y1, y2;
        printf("Entrer entier: ");
        scanf("%d", &y1);

        if (write(fd[1], &y1, sizeof(y1)) == -1) {
            return 5;
        } printf("Ici le processus père, j'ai écrit %d dans le tuyau.\n", y1);

        wait(NULL);  /* attend la fin de l'exécution du processus fils */

        if (read(fd[0], &y2, sizeof(y2)) == -1) {
            return 6;
        } printf("Ici le processus père, j'ai lu %d dans le tuyau.\n", y2);

        close(fd[0]); close(fd[1]);
    }

    return 0;
}