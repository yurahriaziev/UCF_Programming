#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define NUM_TEST_INSERTS 150

#define NUM_TOTAL_OPS 10000000
#define PRINT 0

typedef struct heap_struct {
    int *heap_array;
    int capacity;
    int size;
} heap_struct;

heap_struct *init_heap();
heap_struct *init_heap_from_array(int *values, int len);
void heapify(heap_struct *heap); // runtime: O(n)

void percolate_down(heap_struct *heap, int index);
void percolate_up(heap_struct *heap, int index);
int insert(heap_struct *heap, int value);

int get_right_child_index(int parent_index) {
    return (parent_index * 2) + 1;
}
int get_left_child_index(int parent_index) {
    return parent_index * 2;
}
int get_parent_from_child_index(int child_index) {
    return child_index / 2;
}

int remove_min(heap_struct *heap);
int print_heap(heap_struct *heap);
void free_heap(heap_struct *heap);

void sort(int values[], int length); // runtime: O(n log n)

heap_struct *init_heap() {
    struct heap_struct *h;
    h = (heap_struct*)(malloc(sizeof(heap_struct)));
    h->capacity = SIZE;
    h->heap_array = (int *)malloc(sizeof(int) * (SIZE+1));
    h->size = 0;
}

int insert(heap_struct *heap, int value) {
    int *temp;
    int *throwaway;
    int i;

    // check if capacity is reached
    if (heap->size == heap->capacity) {
        heap->heap_array = (int *)realloc(heap->heap_array, sizeof(int) *(2*heap->capacity+1));
        if (heap->heap_array == NULL) return 0;
        heap->capacity *= 2;
    }

    // insert new item at the end of the list
    heap->size++;
    heap->heap_array[heap->size] = value;

    // percolate up start here
    percolate_up(heap, heap->size);
    return 1;
}

// swap two given values in the heap
void swap(heap_struct *heap, int index_a, int index_b) {
    int temp = heap->heap_array[index_a];
    heap->heap_array[index_a] = heap->heap_array[index_b];
    heap->heap_array[index_b] = temp;
}

// percolate up to check if parent of given index is bigger, if so swap, until parent is smaller or root is reached
void percolate_up(heap_struct *heap, int index) {
    if (index > 1) {
        if (heap->heap_array[index/2] > heap->heap_array[index]) {
            swap(heap, index, index/2);

            percolate_up(heap, index/2);
        }
    }
}

int remove_min(heap_struct *heap) {
    int ret_val;

    // check if heap is not empty
    if (heap->size > 0) {
        // get root value
        ret_val = heap->heap_array[1];

        // send last item to root
        heap->heap_array[1] = heap->heap_array[heap->size];
        heap->size--;

        percolate_down(heap, 1);

        return ret_val;
    }
}

int minimum(int value_a, int index_a, int value_b, int index_b) {
    if (value_a < value_b) {
        return index_a;
    }

    return index_b;
}

void percolate_down(heap_struct *heap, int index) {
    int min;

    // check if parent has two children (left and right)
    if ((2*index+1) <= heap->size) {
        // get minumum of two children
        min = minimum(heap->heap_array[2*index], 2*index, heap->heap_array[2*index+1], 2*index+1);

        // check if min is smaller than given parent, swap if so and continue percolate down process
        if (heap->heap_array[index] > heap->heap_array[min]) {
            swap(heap, index, min);

            percolate_down(heap, min);
        }
    } else if (heap->size == 2*index) { // if parent only has left child, cannot have only right value since it breaks complete bin tree property
        if (heap->heap_array[index] > heap->heap_array[2*index]) {
            swap(heap, index, 2*index);
        }
    }
}

void heapify(heap_struct *heap) {
    for (int i=heap->size/2; i>0; i--) {
        percolate_down(heap, i);
    }
}

int main() {
    int item;

    srand(time(0));
    heap_struct *heap = init_heap();

    int i;
    for (i=0; i<NUM_TEST_INSERTS; i++) {
        item = rand()%100;
        int outcome = insert(heap, item);
        if (!outcome) break;
    }

    // printf()
}