#include <stdlib.h>
#include <stdio.h>
#define EMPTY -1
#define INIT_SIZE 10

// START circular queue implementation
typedef struct queue {
    int *elements;
    int front;
    int num_elements;
    int size;
} queue;

void init(queue *q);
int enqueue(queue *q, int val);
int dequeue_circular(queue *q);
int is_empty(queue *q);
int peek(queue *q);
void display_queue(queue *q);

void init(queue *q) {
    q->elements = malloc(INIT_SIZE * sizeof(int));
    q->front = 0;
    q->num_elements = 0;
    q->size = INIT_SIZE;
}

int enqueue(queue *q, int val) {
    if (q->num_elements != q->size) {
        q->elements[(q->front + q->num_elements) % q->size] = val;
        q->num_elements++;

        return 1;
    }
}

int dequeue_circular(queue *q) {
    if (q->num_elements == 0) {
        return EMPTY;
    }

    int return_val = q->elements[q->front];
    q->front = (q->front + 1) % q->size;;
    q->num_elements--;

    return return_val;
}

int is_empty(queue *q) {
    return q->num_elements == 0;
}

int peek(queue *q) {
    if (q->num_elements != 0) {
        return q->elements[q->front];
    }
    return EMPTY;
}
// END circular queue implement

// START array based queue implement

#define MAX 50
int queue_array[MAX];
int rear = 0;
int front = 0;

void enqueue_linear(int item);
int dequeue_linear();
void display();

void enqueue_linear(int item) {
    if (rear < MAX) {
        queue_array[rear] = item;
        rear += 1;
    }
}

int dequeue_linear() {
    if (front == rear) {
        printf("Empty\n");
        return EMPTY;
    }
    return queue_array[front++];
}

// END array based queue implement

// START linked list queue implement

typedef struct node {
    int data;
    struct node *next;
} node;
typedef struct ll_queue {
    struct node *front;
    struct node *back;
} ll_queue;

void init_ll_q(ll_queue *q);
int ll_enqueue(ll_queue *q, int val);
int ll_dequeue(ll_queue *q);
int peek_ll_q(ll_queue *q);
int empty(ll_queue *q);

int empty(ll_queue *q) {
    return q->back == NULL && q->front == NULL;
}

void init_ll_q(ll_queue *q) {
    q->front = NULL;
    q->back = NULL;
}

int ll_enqueue(ll_queue *q, int val) {
    node *temp = malloc(sizeof(node));
    temp->data = val;
    temp->next = NULL;

    if (empty(q)) {
        q->front = temp;
        q->back = temp;
    } else {
        q->back->next = temp;
        q->back = temp;
    }

    return 1;
}

int ll_dequeue(ll_queue *q) {
    if (empty(q)) {
        return EMPTY;
    }

    node *temp = q->front;
    int return_val = temp->data;

    q->front = temp->next;
    
    if (q->front == NULL) {
        q->back = NULL;
    }

    free(temp);
    return return_val;
}

int peek_ll_q(ll_queue *q) {
    if (empty(q)) {
        return EMPTY;
    }

    return q->front->data;
}

// END linked list queue implement