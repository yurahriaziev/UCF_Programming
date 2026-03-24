#include <stdio.h>
#include <stdlib.h>

struct queue {
    int *array;
    int num_elements;
    int front;
    int capacity;
};

int dequeue(struct queue *q) {
    if (q == NULL) {
        return 0;
    }

    if (q->num_elements == 0) {
        return 0;
    }

    int value = q->array[q->front];
    q->front=(q->front + 1) % q->capacity;
    q->num_elements--;

    return value;
}

// 4->6->1->2 | 3->6->1->2 = -
typedef struct node {
    int digit;
    struct node *next;
} node;

int compareTo(node *num1, node *num2) {
    if (num1 == NULL && num2 == NULL) {
        return 0;
    }
    if (num1 == NULL) {
        return -1;
    }
    if (num2 == NULL) {
        return 1;
    }

    int temp = compareTo(num1->next, num2->next);
    if (temp != 0) {
        return temp;
    }

    return num1->digit - num2->digit;
}

// circular queue review
typedef struct circular_queue {
    int *array;
    int head, tail, num_elements, size;
} circular_queue;

void init_queue(circular_queue *q, int max_size) {
    q->size = max_size;
    q->array = malloc(q->size * sizeof(int));
    q->num_elements = 0;
    q->head = 0;
    q->tail = 0;
}

int queue_empty(circular_queue *q) {
    if (q->num_elements == 0) {
        return 1;
    }
    return 0;
}

int queue_full(circular_queue *q) {
    if (q->num_elements == q->size) {
        return 1;
    }
    return 0;
}

void queue_destroy(circular_queue *q) {
    free(q->array);
}

void c_enqueue(circular_queue *q, int value) {
    if (queue_full(q)) {
        return;
    }

    q->array[q->tail] = value;
    q->num_elements++;
    q->tail = (q->tail + 1) % q->size;
}

int c_dequeue(circular_queue *q) {
    if (queue_empty(q)) {
        return 0;
    }

    int res = q->array[q->head];
    q->head = (q->head + 1) % q->size;
    q->num_elements--;
    
    return res;
}

void queue_free(circular_queue *q) {
    free(q->array);
}

int main(void) {
    circular_queue q;

    init_queue(&q, 5);

    c_enqueue(&q, 2);
    c_enqueue(&q, 5);
    c_enqueue(&q, 1);
    c_enqueue(&q, 4);
    c_enqueue(&q, 8);
    c_enqueue(&q, 9);

    int item;
    while ((item = c_dequeue(&q)) != 0) {
        printf("%d\n", item);
    }

    queue_free(&q);
}