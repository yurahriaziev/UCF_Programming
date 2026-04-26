/*              COP 3502C PA 6
This program is written by: Yurii Hriaziev */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 25 // max name of a cat
// given code
typedef enum {
    MODE_ADOPTION = 0,
    MODE_TRIAGE = 1
} Mode;

typedef struct Cat {
    char *name;
    char *breed;
    int age;
    int friendliness;
    int health; // 0...100 where higher means healthier
    int arrival_id;
    int quarantine;
    double key;
} Cat;

typedef struct {
    Cat **arr;
    int size;
    int capacity;
    Mode mode;
} CatHeap;

/* ---------- Global Shelter State ---------- */
typedef struct {
    Mode mode;
    char *featured_breed; /* NULL => none; else dynamically allocated breed string */
    double alpha; /* multiplier for featured breed (>= 1.0; default 1.0)*/
    int next_arrival_id; /* increments on each ADD */
    CatHeap heap;
} Shelter;

/* Returns heap index of cat with given name, or -1 if not found */
int find_cat_index(const CatHeap *heap, const char *name);
/* Returns the current adoption-mode key for cat c using S->featured_breed and S->alpha. */
double compute_adoption_key(const Cat *c, const Shelter *S);
/* Returns the current triage-mode key for cat c. */
double compute_triage_key(const Cat *c);
/* Recomputes all keys for the active mode and rebuilds heap in O(n) using bottom-up heapify. */
void recompute_all_keys_and_build(Shelter *S);

/* ========== Command Handlers (I/O-Free Logic) ========== */
/* Allocates a new Cat, initializes fields, computes key for active mode,
ensures no duplicate name exists (linear scan), and inserts into the heap. */
void cmd_add (Shelter *S, const char *name, const char *breed, int age, int friendl, int health);
/* Locate the cat by name using a linear scan of the heap array.
If found, update the requested field.
For AGE/FRIEND/HEALTH: recompute key for active mode and restore heap order.
For QUARANTINE: update the flag only (numeric key unchanged), then restore heap
order. */
void cmd_update(Shelter *S, const char *name, const char *field, int new_value);
/* Locate the cat by name using a linear scan of the heap array.
Remove it from the heap, restore heap order, and free the Cat. */
void cmd_remove(Shelter *S, const char *name);
/* Prints the current top cat for the active mode (does not modify heap). */
void cmd_peek (const Shelter *S);
/* Serves the highest-priority cat based on the active mode.
ADOPTION: adopt highest-priority non-quarantined cat.
TRIAGE: treat most urgent cat. */
void cmd_serve(Shelter *S);
/* Sets S->mode, sets heap mode, then recompute_all_keys_and_build(S). */
void cmd_mode (Shelter *S, const char *mode_str);
/* Sets (or clears) featured breed and alpha, then
recompute_all_keys_and_build(S). */
void cmd_featured(Shelter *S, const char *breed, double alpha);
/* Non-destructive: print top k according to active mode.
Recommended: copy heap array into a temp heap and extract k from the copy. */
void cmd_print (const Shelter *S, int k);

int find_cat_index(const CatHeap *heap, const char *name) {
    if (heap == NULL) {
        return -1;
    }

    for (int i=1; i<=heap->size; i++) {
        if (strcmp(heap->arr[i]->name, name) == 0) {
            return i;
        }
    }

    return -1;
}

double compute_adoption_key(const Cat *c, const Shelter *S) {
    double base = 1.6 * c->friendliness + 1.1 * c->health - 0.7 * c->age;
    double mult = 1.0;

    if (S->featured_breed != NULL && strcmp(c->breed, S->featured_breed) == 0) {
        mult = S->alpha;
    }

    return base * mult + (-1e-6 * c->arrival_id);
}

int max(int a, int b) {
    if (a < b) {
        return b;
    }
    return a;
}
double compute_triage_key(const Cat *c) {
    return (100 - c->health)*2.0 + max(0, c->age-12)*1.0 - 0.05*c->friendliness;
}

void cmd_mode(Shelter *S, const char *mode_str) {
    if (strcmp(mode_str, "ADOPTION") == 0) {
        S->mode = MODE_ADOPTION;
        S->heap.mode = MODE_ADOPTION;
        // recompute_all_keys_and_build(S);
        printf("Mode set to ADOPTION. Rebuilding priorities...\n");
    } else if (strcmp(mode_str, "TRIAGE") == 0) {
        S->mode = MODE_TRIAGE;
        S->heap.mode = MODE_TRIAGE;
        // recompute_all_keys_and_build(S);
        printf("Mode set to TRIAGE. Rebuilding priorities...\n");
    }
}

int main() {
    Shelter s;
    s.mode = MODE_ADOPTION;
    s.featured_breed = NULL;
    s.alpha = 1.0;
    s.next_arrival_id = 1;
    s.heap.capacity = 10;
    s.heap.arr = malloc((s.heap.capacity + 1) * sizeof(Cat *));
    s.heap.size = 0;
    s.heap.mode = MODE_ADOPTION;

    int q;

    scanf("%d", &q);

    for (int i=0; i<q; i++) {
        char cmd[10];
        scanf("%s", cmd);
        if (strcmp(cmd, "MODE") == 0) {
            char mode_str[10];
            scanf("%s", mode_str);
            cmd_mode(&s, mode_str);
        }
    }

    return 0;
}