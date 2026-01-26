#ifndef MEMTRACK_H
#define MEMTRACK_H
#include <stddef.h>
/*
 * memtrack.h
 *
 * A small runtime memory tracking library for C programs.
 *
 * This library provides wrapper functions around dynamic memory allocation
 * (malloc, calloc, realloc, free) in order to track heap usage at runtime.
 *
 * The tracker records information about each allocation, including size
 * and allocation location, and can detect common memory errors such as:
 *   - memory leaks (allocated but not freed memory)
 *   - double frees
 *   - invalid frees (freeing untracked pointers)
 *
 * Only memory allocated through this library’s API is tracked.
 *
 * Typical usage:
 *   - Call mt_init() at program startup
 *   - Use MT_MALLOC / MT_FREE / MT_REALLOC instead of malloc/free/realloc
 *   - Call mt_report() or mt_shutdown() at program termination
 *
 * All diagnostic output is written to stderr.
 *
 * Not a production memory allocator
 */


/*
 * Initializes the memory tracking system.
 *
 * This function must be called before any tracked allocation functions
 * are used. It is safe to call this function multiple times.
 *
 * If the tracker is already initialized, calling mt_init() will reset
 * the internal tracking state. Any previously recorded allocation
 * information is discarded, and a warning is printed to stderr.
 */
void mt_init(void);

/*
 * Prints a memory usage report to stderr.
 *
 * This function outputs the current state of the memory tracker, including
 * information about active allocations and summary statistics.
 *
 * If the memory tracking system has not been initialized, this function
 * prints a warning to stderr indicating that no tracking data is available.
 *
 * This function does not allocate or free user memory and is safe to call
 * at any time.
 */
void mt_report(void);

/*
 * Shuts down the memory tracking system.
 *
 * This function prints a final memory usage report to stderr and then
 * releases all internal bookkeeping resources used by the tracker.
 *
 * It is safe to call this function even if the tracker has not been
 * initialized. After calling mt_shutdown(), the tracker is considered
 * uninitialized.
 *
 * This function is typically called at program termination to detect
 * memory leaks and ensure all tracking state is cleaned up.
 */

void mt_shutdown(void);

/*
 * Allocates a block of memory and tracks the allocation.
 *
 * This function behaves similarly to the standard malloc(), but records
 * information about the allocation for tracking purposes.
 *
 * On success, it returns a pointer to a newly allocated block of memory
 * of the requested size.
 *
 * On failure, this function prints an error message to stderr and returns
 * NULL. The caller is responsible for checking the return value.
 *
 * Memory returned by this function must be released using mt_free().
 */
void *mt_malloc(size_t byte_num, const char *file, int line);

#define MT_MALLOC(n) mt_malloc((n), __FILE__, __LINE__)

/*
 * Frees a block of memory previously allocated by the memory tracker.
 *
 * This function behaves similarly to the standard free(), but only accepts
 * pointers that are currently tracked as active allocations.
 *
 * If the pointer is NULL, this function does nothing.
 *
 * If the pointer was not allocated by this tracker, or if it has already
 * been freed, this function prints an error message to stderr and does not
 * attempt to free the memory.
 *
 * This function does not return a value.
 */
void mt_free(void *ptr, const char *file, int line);

#define MT_FREE(p) mt_free((p), __FILE__, __LINE__)

/*
 * Reallocates a tracked block of memory.
 *
 * This function behaves similarly to the standard realloc(), but only
 * accepts pointers that are currently tracked as active allocations.
 *
 * If ptr is NULL, this function behaves like mt_malloc() and attempts to
 * allocate a new block of the requested size.
 *
 * If new_size is 0 and ptr is not NULL, this function behaves like mt_free()
 * and returns NULL.
 *
 * On success, it returns a pointer to a block of memory of the requested size.
 * The returned pointer may be different from the original ptr.
 *
 * On failure, this function prints an error message to stderr and returns NULL.
 * In this case, the original ptr remains valid and tracked.
 */
void *mt_realloc(void *ptr, size_t byteNum, const char *file, int line);

#define MT_REALLOC(p, b) mt_realloc((p), (b), __FILE__, __LINE__)

/*
 * Returns the total number of memory tracking errors detected.
 *
 * This function returns the number of errors recorded since the most
 * recent call to mt_init(). Errors include invalid frees, double frees,
 * and attempts to reallocate untracked pointers.
 *
 * This function does not modify tracking state and is intended primarily
 * for testing and diagnostics.
 */
size_t mt_error_count(void);

#endif