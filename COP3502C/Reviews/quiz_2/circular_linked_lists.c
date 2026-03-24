#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node *prev, *next;
} node;

static node *make_node(int item) {
    node *n = malloc(sizeof(node));
    n->info = item;
    n->prev = NULL;
    n->next = NULL;

    return n;
}

void traverse(node *head) {
    if (head == NULL) {
        return;
    }

    node *t = head;
    do {
        if (t->prev == NULL) {
            printf("NULL");
        } else {
            printf("%d", t->prev->info);
        }
        printf(" - %d\n", t->info);
        t = t->next;
    } while (t != head);

    printf("\n");
}

void free_circular_list(node *head) {
    if (head == NULL) {
        return;
    }

    node *current = head->next;
    while (current != head) {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    free(head);
}

// insert at beginning of circular linked list
node *insert_at_beginning(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;
    
    // emty list
    if (head == NULL) {
        temp->next = temp;
        temp->prev = temp;
        return temp;
    }

    node *tail = head->prev;

    temp->next = head;
    temp->prev = tail;

    tail->next = temp;
    head->prev = temp;

    return temp;
}

// insert at end of circular linked list
node *insert_at_end(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;

    // empty list
    if (head == NULL) {
        temp->next = temp;
        temp->prev = temp;
        return temp;
    }

    node *tail = head->prev;

    temp->next = head;
    temp->prev = tail;

    tail->next = temp;
    head->prev = temp;

    return head; 
}

node *insert_sorted(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;

    // empty list
    if (head == NULL) {
        temp->next = temp;
        temp->prev = temp;
        return temp;
    }

    // insert at beginning: given item is less than current head
    if (head->info >= item) {
        node *tail = head->prev;

        temp->next = head;
        temp->prev = tail;

        tail->next = temp;
        head->prev = temp;

        return temp;
    }

    node *t = head;
    while (t->next != NULL & t->info < item) {
        t = t->next;
    }

    node *before = t->prev;

    temp->next = t;
    temp->prev = before;

    before->next = temp;
    t->prev = temp;

    return head;
}

// delete from circular linked list
node *delete_item(node *head, int item) {
    if (head == NULL) {
        return NULL;
    }

    node *t = head;
    do {
        if (t->info == item) {
            break;
        }
        t = t->next;
    } while (t != head);

    // not found -- return head
    if (t->info != item) {
        return head;
    }

    node *before = t->prev;
    node *after = t->next;

    before->next = after;
    after->prev = before;

    if (t == head) {
        head = after;
    }

    free(t);
    return head;
}

void traverse_rec(node *head, node *start) {
    if (head == NULL) {
        return;
    }

    printf("%d ", head->info);
    if (head->next == start) {
        return;
    }

    traverse_rec(head-> next, start);
}

int main() {
    node *head = NULL;

    head = insert_at_end(head, 1);
    head = insert_at_end(head, 2);
    head = insert_at_end(head, 3);
    traverse(head);

    head = insert_at_beginning(head, 0);
    traverse(head);

    head = insert_sorted(head, 3);
    traverse(head);

    head = delete_item(head, 2);
    traverse(head);

    traverse_rec(head, head);

    free_circular_list(head);
}