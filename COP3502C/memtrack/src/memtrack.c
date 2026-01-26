#include "memtrack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    int is_active;
} AllocationRecord;

static AllocationRecord *records = NULL;
static size_t record_count = 0;
static size_t record_capacity = 0;
static int tracker_initialized = 0;
static size_t error_count = 0;

void mt_init(void) {
    if (tracker_initialized) {
        fprintf(stderr, "Warning | Memory tracker already initialized. Resetting...\n");
        free(records);
        records = NULL;
        record_count = 0;
        record_capacity = 0;
        error_count = 0;
    }

    records = malloc(16 * sizeof(AllocationRecord));
    if (records == NULL) {
        fprintf(stderr, "Error | Initial record allocation failed.\n");
        tracker_initialized = 0;
        return;
    }
    record_capacity = 16;
    record_count = 0;
    error_count = 0;
    tracker_initialized = 1;
}