#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(void) {

    int fd = open("fichier.txt", O_WRONLY | O_CREAT, 0777);
    if (fd == -1) {
        return 1;
    }
    printf("file descriptor for 'fichier.txt': %d\n", fd);
    dup2(fd, STDOUT_FILENO);
    /*
    L'élément correspondant à STDOUT_FILENO (1 en général)
    est remplacé par celui associé à fd. Par exemple si on avait:
    0 STDIN
    1 STDOUT
    2 STDERR
    3 fichier.txt

    Le tableau change et devient:
    0 STDIN
    1 fichier.txt
    2 STDERR
    3 fichier.txt

    D'ailleurs il est tout à fait bon et normal de vouloir faire close(3)
    */
    printf("file descriptor for 'fichier.txt': %d\n", fd);  /* s'écrit dans le fichier */
    close(fd);
    printf("in file again\n"); /* s'écrit aussi dans fichier car close(fd) = close(3)  */
                               /* donc les printf passent juste par 1                  */

    return 0;
}