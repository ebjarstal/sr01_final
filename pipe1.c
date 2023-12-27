#include <stdio.h>
#include <unistd.h>


int main(void) {
    int fd[2];
    /* fd[0] - lecture  */
    /* fd[1] - écriture */

    if (pipe(fd) == -1) {
        return 1;
    }
    /* la fonction pipe met les "clés"   */
    /* du pipe dans fd (file descriptor) */

    int id = fork();

    if (id == -1) {
        return 2;
    }
    else if (id == 0) {
        /* code du processus fils */

        close(fd[0]);
        /* on ferme le file descriptor de lecture  */
        /* car on va juste écrire une donnée       */

        int x;
        printf("Entrer un entier: ");
        scanf("%d", &x);

        if (write(fd[1], &x, sizeof(int)) == -1) {
            return 3;
        }

        close(fd[1]);
    }
    else {
        /* code du processus père */

        close(fd[1]);
        /* on ferme le fd d'écriture car */
        /* on va juste lire une donnée   */

        /* pas besoin de wait(NULL) car la fonction read() */
        /* attend qu'une donnée soit écrite dans le pipe   */

        int y;
        read(fd[0], &y, sizeof(int)); /* y <- x */
        close(fd[0]);

        printf("Valeur lue: %d\n", y);
    }

    return 0;
}