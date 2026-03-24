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
void quickSort(Cat **list, int n, int key);
void quickSortRec(Cat **list, int low, int high, int key);