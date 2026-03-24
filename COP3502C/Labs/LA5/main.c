#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

struct node *insert(struct node *list, int d);
struct node *del(struct node *list, int d);
void print(struct node *list);
void freeList(struct node *list);
void copy(struct node *q, struct node **s);

// function for the lab
struct node *insert(struct node *list, int d) {
    if (list == NULL) {
        node *newNode = malloc(sizeof(node));

        newNode->data = d;
        newNode->next = NULL;
        return newNode;
    }

    list->next = insert(list->next, d);
    return list;
}

void freeList(struct node *list) {
    if (list == NULL) {
        return;
    }

    freeList(list->next);
    free(list);
}

void print(struct node *list) {
    if (list == NULL) {
        return;
    }

    printf("%d", list->data);
    if (list->next != NULL) {
        printf("->");
        print(list->next);
    }
}

struct node *del(struct node *list, int d) {
    if (list == NULL) {
        return NULL;
    }

    if (list->data == d) {
        struct node *after = list->next;
        free(list);
        return after;
    }

    list->next = del(list->next, d);
    return list;
}

void copy(struct node *q, struct node **s) {
    if (q == NULL) {
        *s = NULL;
        return;
    }

    *s = malloc(sizeof(node));
    (*s)->data = q->data;
    copy(q->next, &((*s)->next));
}

int main() {
    int number = 0, choice = 0;
    struct node *pList = NULL;
    struct node *nList = NULL;

    while (choice != 4) {
        printf("\nDo you want to (1)insert, (2)delete, (3)Copy (4)quit.\n");
        scanf("%d", &choice);

        printf("Your choice is %d\n", choice);

        if (choice == 1) {
            printf("Enter the value to insert\n");
            scanf("%d", &number);
            pList = insert(pList, number);
            printf("Items in linked list: ");
            print(pList);
        } else if (choice == 2) {
            if (pList != NULL) {
                printf("Enter the value to delete.\n");
                scanf("%d", &number);
                pList = del(pList, number);
                printf("Items in linked list: ");
                print(pList);
            } else {
                printf("Your list is empty!");
            }
        } else if (choice == 3) {
            if (nList) {
                freeList(nList);
            }
            copy(pList, &nList);
            printf("Items in NEW linked list: ");
            print(nList);
        } else {
            break;
        }
    }

    freeList(nList);
    freeList(pList);
    printf("\nBye...\n");
    return 0;
}