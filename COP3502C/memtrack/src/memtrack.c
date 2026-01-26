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

static int ensure_capacity_for_new_record() {
    if (!tracker_initialized) {
        fprintf(stderr, "Error | Memory tracker has not been initialized.\n");
        error_count += 1;
        return 0;
    }

    if (record_count < record_capacity) {
        return 1;
    } else if (record_count == record_capacity) {
        AllocationRecord *temp_records = realloc(records, (record_capacity * 2) * sizeof(AllocationRecord));
        if (temp_records == NULL) {
            fprintf(stderr, "Error | Failed to reallocate new memory for records.\n");
            error_count += 1;
            return 0;
        }

        records = temp_records;
        record_capacity *= 2;
        return 1;
    }

    return 0;
}

size_t mt_error_count() {
    return error_count;
}

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

void *mt_malloc(size_t byte_num, const char *file, int line) {
    if (!tracker_initialized) {
        fprintf(stderr, "Error | Memory tracker has not been initialized.\n");
        error_count += 1;
        return NULL;
    }

    if (!ensure_capacity_for_new_record()) {
        return NULL;
    }

    void *ptr = malloc(byte_num);
    if (ptr == NULL) {
        fprintf(stderr, "Error | Error allocating user memory.\n");
        error_count += 1;
        return NULL;
    }

    AllocationRecord new_record;
    new_record.ptr = ptr;
    new_record.size = byte_num;
    new_record.file = file;
    new_record.line = line;
    new_record.is_active = 1;
    records[record_count] = new_record;

    record_count += 1;

    return ptr;
}