/*              COP 3502C PA1
This program is written by: Yurii Hriaziev */

// this program implements the assignment using Quick Sort

// given code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 12
#define NUMTRAITS 7
#define TOTAL 6
#define BASECASESIZE 30

const char TRAITS[NUMTRAITS][MAXSIZE+1] = 
{
    "Cuteness", "Fluffiness", "Agility",
    "Friendliness", "Intelligence", "Laziness", "Total"
};

typedef struct Cat {
    char *name;
    int scores[NUMTRAITS];
} Cat;

// function prototypes
int compareTo(Cat *ptrC1, Cat *ptrC2, int key);
void insertionSort(Cat **list, int low, int high, int key);
Cat **readCats(int n);
void printRanks(Cat **list, int n, int key);
void freeCats(Cat **list, int n);
void quickSort(Cat **list, int n, int key);
void quickSortRec(Cat **list, int low, int high, int key);
void swap(Cat **catA, Cat **catB);
int partition(Cat **list, int low, int high, int key);

// compareTo: function that takes in two pointers ptrC1, ptrC2 to Cat structs
// - returns -1 if ptrC1 cat comes before ptrC2 cat
// - returns 0 if both cats are identical
// - returns 1 if ptrC2 cat comes before ptrC1 cat
// - if cat scores are tied, rank names alphabetically
int compareTo(Cat *ptrC1, Cat *ptrC2, int key) {
    if (ptrC1->scores[key] > ptrC2->scores[key]) {
        return -1;
    }
    if (ptrC1->scores[key] < ptrC2->scores[key]) {
        return 1;
    }

    return strcmp(ptrC1->name, ptrC2->name);
}

// insertionSort: function that will use compareTo function to check if current cat's score is higher than next ones
// if so, shift elements and insert the item in the correct position
void insertionSort(Cat **list, int low, int high, int key) {
    int i, j;
    Cat *item;

    for (i=low+1; i<=high; i++) {
        item = list[i];

        for (j=i-1; j>=low; j--) {
            if (compareTo(list[j], item, key) > 0) {
                list[j+1] = list[j];
            } else {
                break;
            }
        }
        list[j+1] = item;
    }
}

// readCats: function that will create a pointer to a list of Cat pointers
// - returns a list of pointers of size n for the amount of cats
Cat **readCats(int n) {
    Cat **list = malloc(n * sizeof(Cat *));

    for (int i=0; i<n; i++) {
        Cat *newCat = malloc(sizeof(Cat));

        char tempName[MAXSIZE+1];
        int cuteScore;
        int fluffScore;
        int agileScore;
        int friendlyScore;
        int smartScore;
        int lazyScore;

        scanf("%s %d %d %d %d %d %d", tempName, &cuteScore, &fluffScore, &agileScore, &friendlyScore, &smartScore, &lazyScore);

        newCat->name = malloc((strlen(tempName) + 1) * sizeof(char));
        strcpy(newCat->name, tempName);
        newCat->scores[0] = cuteScore;
        newCat->scores[1] = fluffScore;
        newCat->scores[2] = agileScore;
        newCat->scores[3] = friendlyScore;
        newCat->scores[4] = smartScore;
        newCat->scores[5] = lazyScore;
        newCat->scores[6] = cuteScore + fluffScore + agileScore + friendlyScore + smartScore + lazyScore;

        list[i] = newCat;
    }

    return list;
}

// printRanks: function that will print each cat in the given print format
void printRanks(Cat **list, int n, int key) {
    if (list == NULL) {
        return;
    }

    printf("%s Ranklist\n", TRAITS[key]);
    for (int i=0; i<n; i++) {
        printf("%d. %-15s %d\n", i+1, list[i]->name, list[i]->scores[key]);
    }
}

// freeCats: function that will free all cat structs and the cat list too
void freeCats(Cat **list, int n) {
    if (list == NULL) {
        return;
    }

    for (int i=0; i<n; i++) {
        free(list[i]->name);
        free(list[i]);
    }

    free(list);
}

// swap: function that will swap the two cat pointers
void swap(Cat **catA, Cat **catB) {
    Cat *t = *catA;
    *catA = *catB;
    *catB = t;
}

// partition: function that picks a random pivot point and move it to front
// then arranges all cats that come left of pivot and cats that come after the pivot on the right
// returns pivot index
int partition(Cat **list, int low, int high, int key) {
    int i = low + rand()%(high - low + 1);
    swap(&list[low], &list[i]);

    int lowpos = low;
    low++;

    while(low<=high) {
        while (low<=high && (compareTo(list[low], list[lowpos], key) <= 0)) {
            low++;
        }

        while (high>=low && (compareTo(list[high], list[lowpos], key) > 0)) {
            high--;
        }

        if (low<high) {
            swap(&list[low], &list[high]);
        }
    }

    swap(&list[lowpos], &list[high]);

    return high;
}

// quickSortRec: function that recursively sorts subarrays of list[low...split-1] and list[split+1...high]
void quickSortRec(Cat **list, int low, int high, int key) {
    
    if (low < high) {
        if ((high - low + 1) <= BASECASESIZE) {
            insertionSort(list, low, high, key);
            return;
        }

        int split = partition(list, low, high, key);
        quickSortRec(list, low, split-1, key);
        quickSortRec(list, split+1, high, key);
    }
}

// quickSort: wrapper function that will call quickSortRec
void quickSort(Cat **list, int n, int key) {
    if (list == NULL) {
        return;
    }

    if (n <= 1) {
        return;
    }

    quickSortRec(list, 0, n-1, key);
}

int main(void) {
    int n, key;

    scanf("%d", &n);
    Cat **list = readCats(n);
    scanf("%d", &key);

    quickSort(list, n, key);

    printRanks(list, n, key);
    freeCats(list, n);

    return 0;
}