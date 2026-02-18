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

void mt_free(void *ptr, const char *file, int line) {
    if (ptr == NULL) {
        return;
    }

    if (!tracker_initialized) {
        fprintf(stderr, "Error | Memory tracker has not been initialized.\n");
        error_count += 1;
        return;
    }

    size_t found_index = record_count;
    for (size_t i=0; i<record_count; i++) {
        if (records[i].ptr == ptr) {
            found_index = i;
            break;
        }
    }

    if (found_index == record_count) {
        fprintf(stderr, "Error | File [%s] Line %d | Invalid free, pointer not found.\n", file, line);
        error_count += 1;
        return;
    }

    if (records[found_index].is_active == 0) {
        fprintf(stderr, "Error | File [%s] Line %d | Double free detected.\n", file, line);
        error_count += 1;
        return;
    }

    free(records[found_index].ptr);
    records[found_index].is_active = 0;
    return;
}

void *mt_realloc(void *ptr, size_t byte_num, const char *file, int line) {
    if (ptr == NULL) {
        return mt_malloc(byte_num, file, line);
    }

    if (byte_num == 0) {
        mt_free(ptr, file, line);
        return NULL;
    }

    if (!tracker_initialized) {
        fprintf(stderr, "Error | Memory tracker has not been initialized.\n");
        error_count += 1;
        return NULL;
    }

    size_t found_index = record_count;
    for (size_t i=0; i<record_count; i++) {
        if (records[i].ptr == ptr) {
            found_index = i;
            break;
        }
    }

    if (found_index == record_count) {
        fprintf(stderr, "Error | File [%s] Line %d | Invalid realloc, pointer not found.\n", file, line);
        error_count += 1;
        return NULL;
    }

    if (records[found_index].is_active == 0) {
        fprintf(stderr, "Error | File [%s] Line %d | Realloc of a freed pointer detected.\n", file, line);
        error_count += 1;
        return NULL;
    }

    void *new_ptr = realloc(ptr, byte_num);
    if (new_ptr == NULL) {
        fprintf(stderr, "Error | File [%s] Line %d | Realloc failed.\n", file, line);
        error_count += 1;
        return NULL;
    }

    records[found_index].ptr = new_ptr;
    records[found_index].size = byte_num;
    records[found_index].file = file;
    records[found_index].line = line;
    return new_ptr;
}

void mt_report() {
    if (!tracker_initialized) {
        fprintf(stderr, "Warning | Memory tracker has not been initialized.\n");
        return;
    }

    size_t total_allocs = 0;
    size_t total_bytes = 0;
    for (size_t i=0; i<record_count; i++) {
        if (records[i].is_active) {
            total_allocs += 1;
            total_bytes += records[i].size;
        }
    }

    fprintf(stderr, "===== Memory Tracker Report =====\n");
    fprintf(stderr, "Total allocations recorded: %zu\n", record_count);
    fprintf(stderr, "Active allocations: %zu\n", total_allocs);
    fprintf(stderr, "Active bytes: %zu\n", total_bytes);
    fprintf(stderr, "Errors detected: %zu\n", error_count);
    fprintf(stderr, "=================================\n");

    if (total_allocs > 0) {
        fprintf(stderr, "Active allocation details:\n");

        for (size_t i = 0; i < record_count; i++) {
            if (records[i].is_active) {
                fprintf(stderr,
                        "  [%p] %zu bytes allocated at %s:%d\n",
                        (void *)records[i].ptr,
                        records[i].size,
                        records[i].file,
                        records[i].line);
            }
        }
    } else {
        fprintf(stderr, "No active allocations (no leaks detected).\n");
    }
}