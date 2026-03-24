/*              COP 3502C PA1
This program is written by: Yurii Hriaziev */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// given structs
typedef struct Cat_s {
    int arrival;
    char *name;
    int duration;
} Cat;

typedef struct SLLNode_s {
    Cat *cat;
    struct SLLNode_s *next;
} SLLNode;

// strucks for a queue with front and back pointers and stack struct
typedef struct Queue {
    SLLNode *front;
    SLLNode *back;
} Queue;

typedef struct Stack {
    SLLNode *top;
} Stack;

// functions to be implemented
void readCatInput(Queue *q);
void freeCat(Cat *cat);
SLLNode *createNode(Cat *cat);
void freeNode(SLLNode *node);

// queue functions
void queueInit(Queue *q);
int isQueueEmpty(const Queue *q);
Cat *queuePeek(const Queue *q);
void queueEnqueueSorted(Queue *q, Cat *c);
Cat *queueDequeue(Queue *q);
void queueFree(Queue *q);

// stack functions
void stackInit(Stack *s);
int isStackEmpty(const Stack *s);
void stackPush(Stack *s, Cat *c);
Cat *stackPop(Stack *s);
void stackFree(Stack *s);

// queueInit: Function to initialize an empty queue with front and back pointers to NULL
void queueInit(Queue *q) {
    q->front = NULL;
    q->back = NULL;
}

// isQueueEmpty: Check if queue is empty. Return 1 if empty, 0 if not empty
int isQueueEmpty(const Queue *q) {
    if (q->front == NULL) {
        return 1;
    }
    return 0;
}

// createNode: Function that creates a new node with a given cat pointer and returns the new node
SLLNode *createNode(Cat *cat) {
    if (cat == NULL) {
        return NULL;
    }

    SLLNode *node = malloc(sizeof(SLLNode));
    if (node == NULL) {
        return NULL;
    }
    node->cat = cat;
    node->next = NULL;

    return node;
}

// freeNode: Function that will free the given node
void freeNode(SLLNode *node) {
    if (node != NULL) {
        free(node);
    }
}

// readCatInput:
//  Function to gather input on cats.
//  Will update the sorted queue right after getting one line of input
void readCatInput(Queue *q) {
    int arrivalTime;
    while (1) {
        if (scanf("%d", &arrivalTime) != 1) {
            break;
        }
        if (arrivalTime == -1) {
            break;
        }

        char tempName[26];
        int duration;
        if (scanf("%25s %d", tempName, &duration) != 2) {
            break;
        }

        if (duration == 0) {
            continue;
        }

        Cat *cat = malloc(sizeof(Cat));
        if (cat == NULL) {
            break;
        }

        cat->arrival = arrivalTime;
        cat->name = malloc((strlen(tempName) + 1) * sizeof(char));
        if (cat->name == NULL) {
            free(cat);
            break;
        }

        strcpy(cat->name, tempName);
        cat->duration = duration;

        queueEnqueueSorted(q, cat);
    }
}

// freeCat: Function that will free the name pointer of given cat and the given cat pointer itself
void freeCat(Cat *cat) {
    if (cat == NULL) {
        return;
    }

    free(cat->name);
    free(cat);
}

// queueEnqueueSorted: Function that will receive a new cat to add to the sorted queue
void queueEnqueueSorted(Queue *q, Cat *c) {
    if (q == NULL || c == NULL) {
        return;
    }

    if (isQueueEmpty(q)) {
        SLLNode *newNode = createNode(c);
        if (newNode == NULL) {
            freeCat(c);
            return;
        }
        
        q->front = newNode;
        q->back = newNode;
        return;
    }

    if (c->arrival < q->front->cat->arrival) {
        SLLNode *newNode = createNode(c);
        if (newNode == NULL) {
            freeCat(c);
            return;
        }

        newNode->next = q->front;
        q->front = newNode;
        return;
    }

    SLLNode *prev = q->front;
    SLLNode *curr = q->front->next;
    while (curr != NULL && curr->cat->arrival < c->arrival) {
        prev = curr;
        curr = curr->next;
    }
    SLLNode *newNode = createNode(c);
    if (newNode == NULL) {
        freeCat(c);
        return;
    }

    if (curr != NULL) {
        newNode->next = curr;
        prev->next = newNode;
    } else if (curr == NULL) {
        prev->next = newNode;
        newNode->next = NULL;
        q->back = newNode;
    }
}

// queuePeek: Function to only return the cat that is at the front of the queue
Cat *queuePeek(const Queue *q) {
    if (q == NULL || isQueueEmpty(q)) {
        return NULL;
    }

    return q->front->cat;
}

// queueDequeue: Function to remove and return the cat that is at the front of the queue
Cat *queueDequeue(Queue *q) {
    if (q == NULL || isQueueEmpty(q)) {
        return NULL;
    }

    SLLNode *frontNode = q->front;
    q->front = frontNode->next;
    Cat *frontCat = frontNode->cat;
    
    if (q->front == NULL) {
        q->back = NULL;
    }
    
    freeNode(frontNode);
    return frontCat;
}

// stackInit: Function to initialize the stack and set top to null
void stackInit(Stack *s) {
    if (s == NULL) {
        return;
    }
    s->top = NULL;
}

// isStackEmpty: Check if stack is empty. Return 1 if empty, 0 if not empty
int isStackEmpty(const Stack *s) {
    if (s == NULL || s->top == NULL) {
        return 1;
    }

    return 0;
}

// stackPush: Function to push new node to the top of the stack
void stackPush(Stack *s, Cat *c) {
    if (s == NULL || c == NULL) {
        return;
    }

    SLLNode *newNode = createNode(c);
    if (newNode == NULL) {
        freeCat(c);
        return;
    }

    newNode->next = s->top;
    s->top = newNode;
}

// stackPop: Function to remove and return the top node of the stack
Cat *stackPop(Stack *s) {
    if (s == NULL || isStackEmpty(s)) {
        return NULL;
    }
    
    SLLNode *topNode = s->top;
    s->top = topNode->next;
    Cat *topCat = topNode->cat;
    freeNode(topNode);
    return topCat;
}

// queueFree: Function to free al nodes and cats in the queue
void queueFree(Queue *q) {
    if (q == NULL) {
        return;
    }

    while (!isQueueEmpty(q)) {
        Cat *cat = queueDequeue(q);
        freeCat(cat);
    }

    queueInit(q);
}

// stackFree: Function to free all nodes and cats in the stack
void stackFree(Stack *s) {
    if (s == NULL) {
        return;
    }

    while (!isStackEmpty(s)) {
        Cat *cat = stackPop(s);
        freeCat(cat);
    }

    stackInit(s);
}

// max: function to find if doctor can start working on cat with given cat arrival time
int max(int doctorTime, int catArrival) {
    if (doctorTime > catArrival) {
        return doctorTime;
    }

    return catArrival;
}

// simulate: function that will take queue and stack and simulate the order of cats
void simulate(Queue *q, Stack *s) {
    if (q == NULL || s == NULL) {
        return;
    }

    int unoFree = 0;
    int dosFree = 0;

    while (!isQueueEmpty(q)) {
        Cat *cat = queueDequeue(q);
        if (cat == NULL) {
            continue;
        }

        int startUno = max(unoFree, cat->arrival);
        int startDos = max(dosFree, cat->arrival);

        int chosenDoctor;
        int chosenStart;

        if (startUno < startDos) {
            chosenDoctor = 0;
            chosenStart = startUno;
        } else if (startDos < startUno) {
            chosenDoctor = 1;
            chosenStart = startDos;
        } else {
            chosenDoctor = 0;
            chosenStart = startUno;
        }

        if (chosenStart + cat->duration > 480) {
            printf("Cannot accommodate %s\n", cat->name);
            freeCat(cat);
            continue;
        }

        if (chosenDoctor == 0) {
            printf("Doctor Uno treated %s at %d\n", cat->name, chosenStart);
            unoFree = chosenStart + cat->duration;
            freeCat(cat);
        } else {
            printf("Doctor Dos treated %s at %d\n", cat->name, chosenStart);
            dosFree = chosenStart + cat->duration;
            stackPush(s, cat);
        }
    }

    if (isStackEmpty(s)) {
        printf("No Exposed Cats\n");
    } else {
        printf("Exposed Cats\n");
        while (!isStackEmpty(s)) {
            Cat *cat = stackPop(s);
            printf("%s\n", cat->name);
            freeCat(cat);
        }
    }
}

// main: Function that will run everything. Create queue and stack.
void main(void) {
    Queue q;
    Stack s;

    queueInit(&q);
    stackInit(&s);

    readCatInput(&q);

    simulate(&q, &s);

    queueFree(&q);
    stackFree(&s);
    return 0;
}