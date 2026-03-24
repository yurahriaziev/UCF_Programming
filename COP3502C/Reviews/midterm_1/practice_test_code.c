#include <stdio.h>
#include <stdlib.h>

int f(int n) {
    if (n <= 1) {
        return 1;
    }
    if (n == 2) {
        return 3;
    }
    return 2 * f(n-1) + f(n-2) - 1;
}

typedef struct node {
    int data;
    struct node *next;
} node;

int insertAt(node *head, int x, int p) {
    if (head == NULL) {
        return -1;
    }

    node *newN = malloc(sizeof(node));
    newN->data = x;

    node *temp = head;
    int pos = 1;

    while (temp->next != NULL) {
        if (pos == p-1) {
            newN->next = temp->next;
            temp->next = newN;
            temp = temp->next->next;
        } else {
            temp = temp->next;
        }
        pos += 1;
    }
    if (p > pos) {
        temp->next = newN;
        newN->next = NULL;
    }

    return pos + 1;
}

void traverse(node *head) {
    if (head == NULL) {
        return;
    }

    while (head != NULL) {
        printf("%d->", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    // printf("%d\n", f(5));

    node *head = malloc(sizeof(node));
    head->data = 10;

    node *n1 = malloc(sizeof(node));
    n1->data = 20;

    node *n2 = malloc(sizeof(node));
    n2->data = 30;

    node *n3 = malloc(sizeof(node));
    n3->data = 7;
    
    node *n4 = malloc(sizeof(node));
    n4->data = 4;
    
    node *n5 = malloc(sizeof(node));
    n5->data = 8;
    
    head->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = NULL;

    traverse(head);

    int numElements = insertAt(head, 9, 3);

    traverse(head);
    printf("%d", numElements);

    return 0;
}