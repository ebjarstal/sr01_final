#include <unistd.h>
#include <time.h>


int main(void) {
    char* vect[] = {
            "ping",
            "google.com",
            NULL
    };

    execvp("ping", vect);
    /* la fonction exec existe sous les formats: exec[lv][p][e] */
    /* la seule vraie différence est au niveau des arguments    */

    return 0;
}