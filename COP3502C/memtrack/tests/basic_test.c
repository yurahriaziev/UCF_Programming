#include <stdio.h>
#include <stdlib.h>
#include "../src/memtrack.h"

int main(void) {
    mt_init();

    int *p = MT_MALLOC(2 * sizeof(int));
    if (p == NULL) {
        fprintf(stderr, "Error allocating\n");
        return 1;
    }

    p[0] = 10;
    p[1] = 20;

    MT_FREE(p);
    
    if (mt_error_count() != 0) {
        fprintf(stderr, "Error occured\n");
        return 1;
    }

    // double free
    // MT_FREE(p);

    // int *d = malloc(sizeof(int));
    MT_FREE(p);
    
    mt_shutdown();
    return 0;
}