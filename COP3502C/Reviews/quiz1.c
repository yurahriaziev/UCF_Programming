#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct StringType {
    char *string;
    int length;
} StringType;

typedef struct Employee {
    StringType *ename;
    double salary;
} Employee;

Employee *createEmployees(char names[][50], double *salaries, int empCount) {
    Employee *emps = malloc(empCount * sizeof(Employee));

    for (int i=0; i<empCount; i++) {
        emps[i].ename = malloc(sizeof(StringType));
        int nameLen = strlen(names[i]) + 1; // account for null terminator

        emps[i].ename->string = malloc(nameLen * sizeof(char));
        strcpy(emps[i].ename->string, names[i]);

        emps[i].ename->length = nameLen - 1;
        emps[i].salary = salaries[i];
    }

    return emps;
}

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void insertAfterN(Node *head, int M, int N) {
    // linear approach
    // while (head != NULL) {
    //     if (head->data == N) {
    //         Node *temp = malloc(sizeof(Node));
    //         temp->data = M;
    //         temp->next = head->next;
    //         head->next = temp;

    //         head = temp->next;
    //     } else {
    //         head = head->next;
    //     }
    // }

    // recursive approach
    if (head == NULL) {
        return;
    }

    if (head->data == N) {
        Node *temp = malloc(sizeof(Node));
        temp->data = M;
        temp->next = head->next;
        head->next = temp;

        return insertAfterN(temp->next, M, N);
    } else {
        return insertAfterN(head->next, M, N);
    }
}

Node *something(Node *head) {
    Node *t = head;

    if (t == NULL || t->next == NULL) return t;
    while (t->next->next != NULL) {
        t=t->next;
    }

    t->next->next = head;
    head = t->next;
    t->next = NULL;

    return head;
}

void printLinkList(Node *head) {
    if (head == NULL) {
        return;
    }

    printf("%d ", head->data);
    printLinkList(head->next);
}

#define NUMDIR 3
const int DR[3] = {1,1,1};
const int DC[3] = {-1, 0, 1};

void mistRec(char **grid, int r, int c, int numR, int numC) {
    // if (!inbounds()) {
        
    // }
}

int inbounds(int myr, int myc, int numR, int numC) {
    return myr >= 0 && myr < numR && myc >= 0 && myc < numC;
}

// insert to beginning of linked list
Node *insert_beginning(Node *head, int item) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    } else {
        temp->next = head;
        head = temp;
    }

    return head;
}

// insert at the end
Node *insert_end(Node *head, int item) {
    Node *t;
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = NULL;

    // check if there is no head
    if (head == NULL) {
        head = temp;
    } else {
        t = head;
        while (t->next!=NULL) {
            t=t->next;
        }
        t->next = temp;
    }
    return head;
}

// insert to a sorted linked list
Node *sortedInsert(Node *head, int item) {
    Node *t;

    Node *temp = malloc(sizeof(Node));
    temp->data = item;
    temp->next = NULL;

    if (head == NULL || head->data >= item) {
        temp->next = head;
        head = temp;
    } else {
        t = head;
        while (t->next != NULL && t->next->data < item) {
            t=t->next;
        }
        temp->next = t->next;
        t->next = temp;
    }

    return head;
}

// delete node
Node *delNode(Node *head, int item) {
    Node *t;
    Node *temp;

    if (head == NULL) {
        return head;
    }

    if (head->data == item) {
        temp = head;
        head = head->next;
        free(temp);
        return head;
    } 

    t = head;
    while (t->next != NULL && t->next->data != item) {
        t=t->next;
    }
    if (t->next == NULL) {
        return head;
    }
    temp=t->next;
    t->next = t->next->next;
    free(temp);
    return head;
}

#define SIZE 10
void display_grid(char grid[][SIZE], int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void flood_fill(char grid[][SIZE], int x, int y, char new_ch, char old_ch) {
    if (x<0 || y<0 || y>=SIZE || x>=SIZE) {
        return;
    }

    if (grid[x][y] != old_ch) {
        return;
    }

    grid[x][y] = new_ch;
    flood_fill(grid, x+1, y, new_ch, old_ch);
    flood_fill(grid, x-1, y, new_ch, old_ch);
    flood_fill(grid, x, y+1, new_ch, old_ch);
    flood_fill(grid, x+1, y-1, new_ch, old_ch);
}

int main(void) {
    Node *head = malloc(sizeof(Node));
    Node *n1 = malloc(sizeof(Node));
    Node *n2 = malloc(sizeof(Node));
    Node *n3 = malloc(sizeof(Node));
    Node *n4 = malloc(sizeof(Node));
    Node *n5 = malloc(sizeof(Node));

    head->data = 1;
    head->next = n1;

    n1->data = 9;
    n1->next = n2;

    n2->data = 6;
    n2->next = n3;

    n3->data = 7;
    n3->next = n4;

    n4->data = 4;
    n4->next = n5;

    n5->data = 8;

    // printLinkList(head);

    // head = something(head);

    // printf("\n");
    // printLinkList(head);

    // printLinkList(head);
    // head = insert_beginning(head, 3);
    // printf("\n");
    // printLinkList(head);
    
    // head = insert_end(head, 10);
    // printf("\n");
    // printLinkList(head);

    Node *headSorted = malloc(sizeof(Node));
    Node *s1 = malloc(sizeof(Node));
    Node *s2 = malloc(sizeof(Node));
    Node *s3 = malloc(sizeof(Node));

    headSorted->data = 2;
    headSorted->next = s1;

    s1->data = 3;
    s1->next = s2;

    s2->data = 5;
    s2->next = s3;

    s3->data = 6;
    s3->next = NULL;

    // printLinkList(headSorted);
    // headSorted = sortedInsert(headSorted, 1);

    // printf("\n");
    // printLinkList(headSorted);

    char grid[SIZE][SIZE] = {
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*',' ',' ',' ','*','*',' ',' ',' ','*'},
        {'*',' ',' ',' ','*','*',' ',' ',' ','*'},
        {'*',' ',' ',' ',' ',' ',' ',' ',' ','*'},
        {'*',' ',' ',' ','*','*',' ',' ',' ','*'},
        {'*',' ',' ',' ','*','*',' ',' ',' ','*'},
        {'*',' ',' ',' ','*','*',' ',' ',' ','*'},
        {'*',' ',' ',' ','*','*',' ',' ',' ','*'},
        {'*',' ',' ',' ','*','*',' ',' ',' ','*'},
        {'*','*','*','*','*','*','*','*','*','*'}
    };

    printf("Before:\n");
    display_grid(grid, SIZE, SIZE);
    printf("\n");

    flood_fill(grid, 3, 3, '~', grid[3][3]);

    printf("After Flood Fill:\n");
    display_grid(grid, SIZE, SIZE);

    return 0;
}