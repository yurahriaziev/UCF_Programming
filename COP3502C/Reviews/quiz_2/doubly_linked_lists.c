#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int info;
    struct node *prev, *next;
} node;

// traverse doubly linked list
void traverse(node *head) {
    if (head == NULL) {
        return;
    }

    node *current = head;
    while (current != NULL) {
        if (current->prev == NULL) {
            printf("NULL");
        } else {
            printf("%d", current->prev->info);
        }
        printf(" - %d\n", current->info);

        current = current->next;
    }
    printf("\n");
}

// free doubly linked list
void free_doubly_list(node *head) {
    node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// insert at beginning
node *insert_at_beginning(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;
    temp->prev = NULL;
    temp->next = head;

    if (head != NULL) {
        head->prev = temp;
    }
    head = temp;
    return head;
}

// insert at end 
node *insert_at_end(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;
    temp->next = NULL;

    node *t;

    if (head == NULL) {
        temp->prev = NULL;
        head = temp;
    } else {
        t = head;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = temp;
        temp->prev = t;
    }

    return head;
}

// insert to sorted doubly linked list
node *insert_sorted(node *head, int item) {
    node *temp = malloc(sizeof(node));

    temp->info = item;
    temp->prev = NULL;
    temp->next = NULL;

    // empty list
    if (head == NULL) {
        return temp;
    }

    node *t = head;
    
    // insert before head
    if (head->info >= item) {
        temp->next = head;
        head->prev = temp;
        return head;
    }

    while (t->next != NULL && t->next->info < item) {
        t = t->next;
    }

    temp->next = t->next;
    temp->prev = t;
    if (t->next != NULL) {
        t->next->prev = temp;
    }
    t->next = temp;
    return head;
}

// delete from doubly linked list
node *delete(node *head, int item) {
    node *temp;
    if (head == NULL) {
        return head;
    }
    if (head->info == item) {
        temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(temp);
        return head;
    }

    node *t = head;
    while (t->next != NULL && t->next->info != item) {
        t=t->next;
    }

    // item not found
    if (t->next == NULL) {
        return head; 
    }

    temp = t->next;
    t->next = t->next->next;
    if (t->next) {
        t->next->prev = t;
    }
    free(temp);
    return head;
}

int main() {
    node *head = malloc(sizeof(node));
    node *n1 = malloc(sizeof(node));
    node *n2 = malloc(sizeof(node));

    head->info = 1;
    head->prev = NULL;
    head->next = n1;

    n1->info = 2;
    n1->prev = head;
    n1->next = n2;

    n2->info = 3;
    n2->prev = n1;
    n2->next = NULL;

    traverse(head);

    head = insert_at_beginning(head, 0);
    traverse(head);

    head = insert_at_end(head, 4);
    traverse(head);

    head = insert_sorted(head, 3);
    traverse(head);

    head = delete(head, 2);
    traverse(head);

    free_doubly_list(head);
}