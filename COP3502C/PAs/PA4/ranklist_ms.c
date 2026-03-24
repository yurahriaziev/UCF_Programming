/*              COP 3502C PA1
This program is written by: Yurii Hriaziev */

// this program implements the assignment using Merge Sort

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
void mergeSort(Cat **list, int n, int key);
void mergeSortRec(Cat **list, int low, int high, int key);
void merge(Cat **list, int low, int mid, int high, int key);
void insertionSort(Cat **list, int low, int high, int key);
Cat **readCats(int n);
void printRanks(Cat **list, int n, int key);
void freeCats(Cat **list, int n);

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

int main(void) {
    int n, key;

    scanf("%d", &n);
    Cat **list = readCats(n);
    scanf("%d", &key);

    printRanks(list, n, key);
    freeCats(list, n);

    return 0;
}