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



int main(void) {
    int n, key;

    scanf("%d", &n);
    Cat **list = readCats(n);
    scanf("%d", key);



    printRanks(list, n, key);
    freeCats(list, n);

    return 0;
}