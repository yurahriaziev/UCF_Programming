#include <stdio.h>
#include "main.h"

// Yurii Hriaziev - COP3502C
// --> January 20, 2026

// func: readData(empty list of cat structs, pointer to int) -> None
// Reads input on how many cats there are in total
// Runs a loop for that many cats and creates a new cat struct every run
// Every run populates all cat parameters from given input and calculates average
// Appends that new cat to the empty list of cats
void readData(struct cat *cats, int *c) {
    scanf("%d", c);

    for (int i=0; i<*c; i++) {
        struct cat newCat;
        int scoreSum = 0;

        scanf("%d %10s %d %d %d", &newCat.cat_ID, newCat.name, &newCat.score1, &newCat.score2, &newCat.score3);

        scoreSum += newCat.score1 + newCat.score2 + newCat.score3;
        newCat.average = (float)scoreSum / 3;

        cats[i] = newCat;
    }
}

// func: getCutestCat(list of cat structs, length of that list) -> int
// Initializes maxScore -> int | cutestIndex -> int
// Runs a loop for the length of the list of cats
// Checks if the average score of the i-th cat is higher than maxScore
// If higher: reasign the value of maxScore to current cat's average and reasign cutestIndex to current i
// Else: nothing
// returns cutestIndex
int getCutestCat(struct cat *cats, int n) {
    float maxScore = 0;
    int cutestIndex = 0;
    
    for (int i=0; i<n; i++) {
        if (cats[i].average > maxScore) {
            maxScore = cats[i].average;
            cutestIndex = i;
        }
    }

    return cutestIndex;
}

// func: main(void) -> int
// Runs both functions written above
// Reads value from input
// Find the cutest cat
// Figures out the alphabet stats
int main(void) {
    // Initial empty cat list and number of cats
    struct cat cats[MAXCATS];
    int numCats = 0;

    readData(cats, &numCats);

    // Input validation
    if (numCats < 1) {
        return 1;
    }
    
    // Display each cat's info
    for (int i=0; i<numCats; i++) {
        printf("%d %s %d %d %d %.2f\n", cats[i].cat_ID, cats[i].name, cats[i].score1, cats[i].score2, cats[i].score3, cats[i].average);
    }

    // Dislay cutest cat
    int cutestCatIndex = getCutestCat(cats, numCats);
    printf("Cutest cat is %s\n", cats[cutestCatIndex].name);

    // alphabet stats
    // -- Create list of counts 26 0s
    int counts[26] = {0};
    // -- Count each first letter occurance and increment the number at that index by 1
    for (int i=0; i<numCats; i++) {
        char firstChar = cats[i].name[0];
        counts[firstChar - 'A']++;
    }

    // -- Run for length of alphabet and calculate percentage of cats that begin with that letter
    for (int i=0; i<26; i++) {
        float percent = ((float)counts[i] / numCats) * 100;
        printf("%c: %d %.2f%%\n", 'A'+i, counts[i], percent);
    }

    return 0;
}