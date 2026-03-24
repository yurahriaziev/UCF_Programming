#include <stdio.h>
#include <stdlib.h>

// creating a node for linked list
typedef struct node {
    int info;
    struct node *next;
} node;

// traverse a linked list
void traverse(node *head) {
    if (head == NULL) {
        return;
    }

    while (head != NULL) {
        printf("%d\n", head->info);
        head = head->next;
    }
    printf("\n");
}

// free linked list
void free_linked_list(node *head) {
    node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// insert item at beginning of linked list
node *insert_at_beggining(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        temp->next = head;
        head = temp;
    }

    return head;
}

// insert item at the end of linked list
node *insert_at_end(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;
    temp->next = NULL;

    node *t;

    if (head == NULL) {
        head = temp;
    } else {
        t = head;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = temp;
    }

    return head;
}

// insert to SORTED linked list
node *insert_sorted(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->info = item;
    temp->next = NULL;

    node *t;

    if (head == NULL || head->info >= item) {
        temp->next = head;
        head = temp;
    } else {
        t = head;
        while (t->next != NULL && t->next->info < item) {
            t = t->next;
        }
        temp->next = t->next;
        t->next = temp;
    }

    return head;
}

// delete from linked list
node *delete(node *head, int item) {
    if (head == NULL) {
        return NULL;
    }

    node *temp;
    if (head->info == item) {
        temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    node *t;
    t = head;
    while (t->next != NULL && t->next->info != item) {
        t=t->next;
    }
    // item not found
    if (t->next == NULL) {
        return head;
    }

    temp = t->next;
    t->next = t->next->next;
    free(temp);
    return head;
}

// recursive traverse
void traverse_rec(node *head) {
    if (head == NULL) {
        return;
    }
    printf("%d ", head->info);
    traverse_rec(head->next);
}

// count number of elements in linked list recursively
int count_rec(node *head) {
    if (head == NULL) {
        return 0;
    }
    return 1 + count_rec(head->next);
}

// check if element exists in linked list recursively
int search(node *head, int key) {
    if (head == NULL) {
        return 0;
    }

    if (head->info == key) {
        return 1;
    }

    return search(head->next, key);
}

// reverse linked list recursively
node *reverse(node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    node *rest = reverse(head->next);
    head->next->next = head;
    head->next = NULL;

    return rest;
}

// insert at end recursively
node *insert_at_end_rec(node *head, int item) {
    if (head == NULL) {
        node *temp = malloc(sizeof(node));
        temp->info = item;
        temp->next = NULL;
        return temp;
    }

    head->next = insert_at_end_rec(head->next, item);
    return head;
}

// delete item recursively
node *delete_item_rec(node *head, int item) {
    if (head == NULL) {
        return NULL;
    }

    if (head->info == item) {
        node *temp = head->next;
        free(head);
        return temp;
    }

    head->next = delete_item_rec(head->next, item);
    return head;
}

int main() {
    node *head = malloc(sizeof(node));
    head->info = 2;

    node *n1 = malloc(sizeof(node));
    n1->info = 4;
    head->next = n1;

    node *n2 = malloc(sizeof(node));
    n2->info = 6;
    n1->next = n2;

    node *n3 = malloc(sizeof(node));
    n3->info = 8;
    n2->next = n3;

    node *n4 = malloc(sizeof(node));
    n4->info = 10;
    n3->next = n4;
    n4->next = NULL;

    // traverse linked list and print all values
    // traverse(head);

    // head = insert_at_beggining(head, 0);
    // traverse(head);

    // head = insert_at_end(head, 12);
    // traverse(head);

    head = insert_sorted(head, 3);
    traverse(head);

    head = delete(head, 4);
    traverse(head);

    head = reverse(head);
    traverse(head);

    head = delete_item_rec(head, 10);
    traverse(head);

    // free linked list
    free_linked_list(head);
}