#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void) {
    int id = fork();
    int n;

    if (id != 0) {  // si c'est le ps père
        n = 6;
        wait(&id);  // on attend que le ps fils termine d'afficher ses nombres
    }
    else {  // si c'est le ps fils
        n = 1;
    }

    int i;
    for (i = n; i < n+5; i++) {
        printf("%d ", i);
        fflush(stdout);
    }
    printf("\n");

    return 0;
}