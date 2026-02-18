 // tests/realloc_test.c
#include <stdio.h>
#include <stdlib.h>
#include "../src/memtrack.h"

int main(void) {
    mt_init();

    // ----------------------------
    // 1) MT_REALLOC(NULL, n) behaves like MT_MALLOC(n)
    // ----------------------------
    int *p = MT_REALLOC(NULL, 2 * sizeof(int));
    if (p == NULL) {
        fprintf(stderr, "FAIL: MT_REALLOC(NULL, ...) returned NULL\n");
        mt_shutdown();
        return 1;
    }

    p[0] = 10;
    p[1] = 20;

    // ----------------------------
    // 2) Grow realloc: preserve existing contents
    // ----------------------------
    int *p_grow = MT_REALLOC(p, 4 * sizeof(int));
    if (p_grow == NULL) {
        fprintf(stderr, "FAIL: MT_REALLOC grow returned NULL\n");
        mt_shutdown();
        return 1;
    }
    p = p_grow;

    if (p[0] != 10 || p[1] != 20) {
        fprintf(stderr, "FAIL: realloc grow did not preserve data (got %d, %d)\n", p[0], p[1]);
        mt_shutdown();
        return 1;
    }

    p[2] = 30;
    p[3] = 40;

    // ----------------------------
    // 3) Shrink realloc: still should preserve prefix
    // ----------------------------
    int *p_shrink = MT_REALLOC(p, 1 * sizeof(int));
    if (p_shrink == NULL) {
        fprintf(stderr, "FAIL: MT_REALLOC shrink returned NULL\n");
        mt_shutdown();
        return 1;
    }
    p = p_shrink;

    if (p[0] != 10) {
        fprintf(stderr, "FAIL: realloc shrink did not preserve first element (got %d)\n", p[0]);
        mt_shutdown();
        return 1;
    }

    // ----------------------------
    // 4) MT_REALLOC(ptr, 0) behaves like free(ptr) and returns NULL
    // ----------------------------
    void *freed = MT_REALLOC(p, 0);
    if (freed != NULL) {
        fprintf(stderr, "FAIL: MT_REALLOC(ptr, 0) should return NULL\n");
        mt_shutdown();
        return 1;
    }
    p = NULL;

    // Up to here, no errors should have occurred.
    if (mt_error_count() != 0) {
        fprintf(stderr, "FAIL: expected 0 errors before misuse cases, got %zu\n", mt_error_count());
        mt_shutdown();
        return 1;
    }

    // ----------------------------
    // Misuse Case A: realloc of a freed tracked pointer (should error)
    // ----------------------------
    int *q = MT_MALLOC(sizeof(int));
    if (q == NULL) {
        fprintf(stderr, "FAIL: MT_MALLOC returned NULL in misuse setup\n");
        mt_shutdown();
        return 1;
    }
    *q = 123;
    MT_FREE(q);

    int *q_bad = MT_REALLOC(q, 2 * sizeof(int)); // q is freed; should error + return NULL
    if (q_bad != NULL) {
        fprintf(stderr, "FAIL: realloc of freed pointer should return NULL\n");
        mt_shutdown();
        return 1;
    }

    // ----------------------------
    // Misuse Case B: realloc of an untracked pointer (plain malloc) (should error)
    // ----------------------------
    int *u = (int *)malloc(sizeof(int));
    if (u == NULL) {
        fprintf(stderr, "FAIL: system malloc returned NULL in misuse setup\n");
        mt_shutdown();
        return 1;
    }
    *u = 777;

    int *u_bad = MT_REALLOC(u, 2 * sizeof(int)); // untracked pointer; should error + return NULL
    if (u_bad != NULL) {
        fprintf(stderr, "FAIL: realloc of untracked pointer should return NULL\n");
        free(u);
        mt_shutdown();
        return 1;
    }

    // Clean up the untracked pointer using real free (NOT MT_FREE).
    free(u);

    // We expect exactly 2 errors from the 2 misuse cases above.
    size_t errs = mt_error_count();
    if (errs != 2) {
        fprintf(stderr, "FAIL: expected 2 errors after misuse cases, got %zu\n", errs);
        mt_shutdown();
        return 1;
    }

    mt_shutdown();
    return 0;
}
