#include "string.h";

int addItem(driver_t *driver, const item_t *newItem) {
    if (driver == NULL) return 0;

    if (driver->itemCount == 3) return 0;

    if (driver->itemCount == 0) {
        driver->items = malloc(sizeof(item_t));
    } else {
        item_t *newList = realloc(driver->items, sizeof(item_t) * (driver->itemCount + 1));
        if (newList == NULL) return 0;
        driver->items = newList;
    }

    driver->items[driver->itemCount] = newItem;
    driver->itemCount++;
    return 1;
}

// one pass of bubble sort
for (int i=0; i<n-1; i++) {
    if (array[i] > array[i+1]) {
        int temp = array[i];
        array[i] = array[i+1];
        array[i+1] = temp;
    }
}

// recursive bubble sort
void bubbleSortRec(int *array, n) {
    if (n == 1) {
        return;
    }

    for (int i=0; i<n-1; i++) {
        if (array[i] > array[i+1]) {
            int temp = array[i];
            array[i] = array[i+1];
            array[i+1] = temp;
        }
    }

    bubbleSortRec(array, n-1);
}

int compareTo(node *num1, node *num2) {
    if (num1 == NULL && num2 == NULL) {
        return 0;
    }
    if (num1 == NULL) return -1;
    if (num2 == NULL) return 1;

    int comp = compareTo(num1->next, num2->next);
    if (comp != 0) {
        return comp;
    }
    return num1->digit - num2->digit;
}

int maxpowLTE(int base, int ans) {
    if (base > ans) return 0;

    return 1 + maxpowLTE(base * base, ans);
}

int greaterThan(competition *ptrA, competition *ptrB) {
    if (ptrA->probSolved > ptrB->probSolved) return 1;
    if (ptrA->probSolved < ptrB->probSolved) return 0;

    if (ptrA->totalTime < ptrB->totalTime) return 1;
    if (ptrA->totalTime > ptrB->totalTime) return 0;

    if (ptrA->difficulty > ptrB->difficulty) return 1;
    return 0;
}

account_t * mergeAccounts (account_t * acct1, account_t * acct2) {
    account_t *merged = malloc(sizeof(account_t));

    merged->id = acct2->id;
    merged->amount = acct1->amount + acct2->amount;

    int len1 = strlen(acct1->name);
    int len2 = strlen(acct2->name);
    int size = len1 + len2 + 6;

    merged->name = malloc(size * sizeof(char));

    strcpy(merged->name, acct1->name);
    strcat(merged->name, " and ");
    strcat(merged->name, acct2->name);

    return merged;
}

void battleGame(queue_t *gameQ) {
    if (size(gameQ) == 1) {
        printf("%s", front(gameQ)->name);
        return;
    }

    while (size(gameQ) > 1) {
        player_t *p1 = dequeue(gameQ);
        player_t *p2 = dequeue(gameQ);

        if (p1->hp > p2->hp) {
            enqueue(gameQ, p1);
        } else if (p1->hp < p2->hp) {
            enqueue(gameQ, p2);
        } else {
            enqueue(gameQ, p2);
        }
    }

    player_t *winner = front(gameQ);
    printf("%s", winner->name);
}

int sumData(treenode *root) {
    if (root==NULL) return 0;

    return root->data + sumData(root->left) + sumData(root->right);
}

if (!inbounds(r, c, numR, numC) || grid[r][c] == 'B') return;

grid[r][c] = 'M';

for (int i=0; i<NUMDIR; i++) {
    mistRect(grid, DR[i], DC[i], numR, numC);
}