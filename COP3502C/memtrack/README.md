# MemTrack

## About

MemTrack is a lightweight runtime memory tracking library for C programs.

It wraps `malloc`, `free`, and `realloc` to detect memory leaks and invalid memory operations.  
All diagnostics are printed to `stderr`.

This project is designed for learning and debugging — not as a production allocator.

---

## How to Use

1) Initialize the tracker:

~~~c
mt_init();

// example in void main()
int main(void) {
    mt_init();

    ...
}
~~~

2) Use the macros instead of standard allocation functions:

~~~c
int *p = MT_MALLOC(sizeof(int));
p = MT_REALLOC(p, 2 * sizeof(int));
MT_FREE(p);
~~~

These macros automatically record file and line information.

3) Shut down the tracker:

~~~c
mt_shutdown();
~~~

This prints a memory report and releases internal tracking memory.

Sample output

~~~bash
Error | File [tests/realloc_test.c] Line 89 | Realloc of a freed pointer detected.
Error | File [tests/realloc_test.c] Line 107 | Realloc of a freed pointer detected.
===== Memory Tracker Report =====
Total allocations recorded: 2
Active allocations: 0
Active bytes: 0
Errors detected: 2
=================================
No active allocations (no leaks detected).
~~~

---

## Tests

From the project root, compile a test (example: `basic_test`):

~~~bash
gcc -std=c11 -Wall -Wextra -Werror -Isrc tests/basic_test.c src/memtrack.c -o basic_test
~~~

Run it:

~~~bash
./basic_test
~~~

Repeat for other tests by swapping the test file and output name, e.g.:

~~~bash
gcc -std=c11 -Wall -Wextra -Werror -Isrc tests/realloc_test.c src/memtrack.c -o realloc_test
./realloc_test
~~~

Each test:
- calls `mt_init()`
- performs memory operations
- checks `mt_error_count()`
- calls `mt_shutdown()`

Exit code:
- `0` → success
- `1` → failure
