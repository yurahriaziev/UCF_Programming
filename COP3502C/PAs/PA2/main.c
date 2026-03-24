/*              COP 3502C PA1
This program is written by: Yurii Hriaziev */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../memtrack/src/memtrack.c"

// given global vars and structs
#define MAX_SCORES 5
#define MAX_STR 25

const float POSITION_BONUS[10] = {3.0, 5.0, 4.0, 6.0, 7.0, 2.0, 8.0, 1.0, 9.0, 1.5};

typedef struct Cat {
    char *name;
    char *breed;
    int scores[MAX_SCORES];
    int baseScore;
} Cat;

typedef struct Rivals {
    Cat *cat1;
    Cat *cat2;
} Rivals;

Cat *cats;
Rivals *rivals;
float bestPermScore;
int **tracker;

// helper funcs
int findCatIndexByName(const char *name, int totalCats);
void readInput(int *n, int *c, int *r);
void createTracker(int n, int c);
void updateTrackerFromPerm(const int *perm, int n, int c);
float scoreTeam(const int *perm, int teamIndex, int n, int c, int r);
float scorePermutation(const int *perm, int n, int c, int r);
int countHighPerformersTraits(const int *perm, int teamStart, int c, int catOffset, int traitOffset);
int synergyBonusApplies(const int *perm, int teamStart, int c, int catOffset);
int rivalPenaltyApplies(const int *perm, int teamStart, int c, int pos, int r, int rivalIndex);
void permuteUsed(int depth, int totalCats, int *perm, int *used, int n, int c, int r);
void printBest(int n, int c, int r);
void freeAll(int n, int c, int r);

// findCatIndexByName: function that will find the exact index of cat given its name
int findCatIndexByName(const char *name, int totalCats) {
    for (int i=0; i<totalCats; i++) {
        if (strcmp(cats[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

// readInput: function that will read all input, create Cats, scores, and Rivals
void readInput(int *n, int *c, int *r) {
    scanf("%d %d", n, c);
    int totalCats = (*n) * (*c);

    cats = MT_MALLOC(totalCats * sizeof(Cat));
    for (int i=0; i<totalCats; i++) {
        char tempName[MAX_STR+1];
        char tempBreed[MAX_STR+1];
        scanf("%25s %25s", tempName, tempBreed);

        cats[i].name = MT_MALLOC((strlen(tempName)+1) * sizeof(char));
        cats[i].breed = MT_MALLOC((strlen(tempBreed)+1) * sizeof(char));

        strcpy(cats[i].name, tempName);
        strcpy(cats[i].breed, tempBreed);

        int sum = 0;
        for (int s=0; s < MAX_SCORES; s++) {
            scanf("%d", &cats[i].scores[s]);
            sum += cats[i].scores[s];
        }
        cats[i].baseScore = sum;
    }
    
    scanf("%d", r);
    rivals = NULL;
    if (*r>0) {
        rivals = MT_MALLOC(*r * sizeof(Rivals));

        for (int i=0; i<*r; i++) {
            char rivalOne[MAX_STR + 1];
            char rivalTwo[MAX_STR + 1];

            scanf("%25s %25s", rivalOne, rivalTwo);
            int indexOne = findCatIndexByName(rivalOne, totalCats);
            int indexTwo = findCatIndexByName(rivalTwo, totalCats);

            rivals[i].cat1 = &cats[indexOne];
            rivals[i].cat2 = &cats[indexTwo];
        }
    }
}

// createTracker: function that creates a dynamic 2d array to store the permutations
void createTracker(int n, int c) {
    tracker = MT_MALLOC(n * sizeof(int *));

    for (int i=0; i<n; i++) {
        tracker[i] = MT_MALLOC(c * sizeof(int));
    }
}

// updateTracker: function that will update a tracker to the given permutation
void updateTrackerFromPerm(const int *perm, int n, int c) {
    int k = 0;
    for (int team=0; team<n; team++) {
        for (int pos=0; pos<c; pos++) {
            tracker[team][pos] = perm[k++];
        }
    }
}

// permuteUsed: function that will recursively create permutations and update bestPermScore
void permuteUsed(int depth, int totalCats, int *perm, int *used, int n, int c, int r) {
    if (depth == totalCats) {
        float current = scorePermutation(perm, n, c, r);
        if (current > bestPermScore) {
            bestPermScore = current;
            updateTrackerFromPerm(perm, n, c);
        }
        return;
    }

    for (int i=0; i<totalCats; i++) {
        if (!used[i]) {
            used[i] = 1;
            perm[depth] = i;
            permuteUsed(depth+1, totalCats, perm, used, n, c, r);

            used[i] = 0;
        }
    }
}

// scorePermutation: function that return the total score of a given team permutation
float scorePermutation(const int *perm, int n, int c, int r) {
    float total = 0.0f;

    for (int i=0; i<n; i++) {
        total += scoreTeam(perm, i, n, c, r);
    }

    return total;
}

// scoreTeam: function that will return the total score of a given permutation team after all bonuses and penalties
float scoreTeam(const int *perm, int teamIndex, int n, int c, int r) {
    int teamStart = teamIndex * c;

    float baseSum = 0.0f;
    for (int i=0; i<c; i++) {
        int index = perm[teamStart+i];
        baseSum += (float)cats[index].baseScore;
    }
    float score = baseSum / (float)c;

    int highTraitCount = countHighPerformersTraits(perm, teamStart, c, 0, 0);
    score += (float)(highTraitCount * 5);

    if (synergyBonusApplies(perm, teamStart, c, 0)) {
        score += 30.0f;
    }

    int allDifferent = 1;
    for (int i=0; i<c && allDifferent; i++) {
        int index = perm[teamStart + i];
        for (int j=i+1; j<c; j++) {
            int indexJ = perm[teamStart + j];
            if (strcmp(cats[index].breed, cats[indexJ].breed) == 0) {
                allDifferent = 0;
                break;
            }
        }
    }
    if (allDifferent) {
        score += 10.0f;
    }

    for (int pos=0; pos<c; pos++) {
        int index = perm[teamStart + pos];
        score += (float)cats[index].baseScore * (POSITION_BONUS[pos] / 100.0f);
    }

    int rivalAdjCount = rivalPenaltyApplies(perm, teamStart, c, 0, r, 0);
    score -= (float)(25 * rivalAdjCount);

    if (!allDifferent) {
        score -= 15.0f;
    }

    return score;
}

// countHighPermormersTraits: function that will count and return the total number of traits in a given permutation team that are greater than 90
int countHighPerformersTraits(const int *perm, int teamStart, int c, int catOffset, int traitOffset) {
    if (catOffset == c) {
        return 0;
    }

    if (traitOffset == MAX_SCORES) {
        return countHighPerformersTraits(perm, teamStart, c, catOffset + 1, 0);
    }

    int catIndex = perm[teamStart + catOffset];

    int add = 0;
    if (cats[catIndex].scores[traitOffset] >= 90) {
        add = 1;
    }

    return add + countHighPerformersTraits(perm, teamStart, c, catOffset, traitOffset + 1);
}

// synergyBonusApplies: function that will return 1 if all cats have at least one trait score of 85 or higher, return 0 if not
int synergyBonusApplies(const int *perm, int teamStart, int c, int catOffset) {
    if (catOffset == c) {
        return 1;
    }

    int catIndex = perm[teamStart + catOffset];
    int pass = 0;
    for (int i=0; i<MAX_SCORES; i++) {
        if (cats[catIndex].scores[i] >= 85) {
            pass = 1;
            break;
        }
    }

    if (!pass) {
        return 0;
    }

    return synergyBonusApplies(perm, teamStart, c, catOffset + 1);
}

// rivalPenaltyApplies: function that will determine the count of any neighboring team members that are rivals
int rivalPenaltyApplies(const int *perm, int teamStart, int c, int pos, int r, int rivalIndex) {
    if (pos >= c-1) {
        return 0;
    }

    int catIndex1 = perm[teamStart + pos];
    Cat *cat1 = &cats[catIndex1];
    int catIndex2 = perm[teamStart + pos + 1];
    Cat *cat2 = &cats[catIndex2];

    if (rivalIndex >= r) {
        return rivalPenaltyApplies(perm, teamStart, c, pos+1, r, 0);
    }

    int areRivals = 0;
    if ((rivals[rivalIndex].cat1 == cat1 && rivals[rivalIndex].cat2 == cat2) || (rivals[rivalIndex].cat1 == cat2 && rivals[rivalIndex].cat2 == cat1)) {
        areRivals = 1;
    }

    return areRivals + rivalPenaltyApplies(perm, teamStart, c, pos, r, rivalIndex + 1);
}

// printBest: function that will print the bestPermScore, the teams, team scores, and best candidate
void printBest(int n, int c, int r) {
    int totalCats = n * c;

    int *bestPerm = MT_MALLOC(totalCats * sizeof(int));

    int k = 0;
    for (int team=0; team<n; team++) {
        for (int pos=0; pos<c; pos++) {
            bestPerm[k++] = tracker[team][pos];
        }
    }

    printf("Best Teams Grouping score: %.2f\n", bestPermScore);

    int bestTeamIndex = 0;
    float bestTeamScore = scoreTeam(bestPerm, 0, n, c, r);

    for (int team=0; team<n; team++) {
        float teamScore = scoreTeam(bestPerm, team, n, c, r);

        printf("Team %d: ", team + 1);
        for (int pos=0; pos<c; pos++) {
            int index = tracker[team][pos];
            printf("%s", cats[index].name);

            if (pos < c-1) {
                printf(" ");
            }
        }

        printf(" %.2f\n", teamScore);

        if (team == 0 || teamScore > bestTeamScore) {
            bestTeamScore = teamScore;
            bestTeamIndex = team;
        }
    }

    printf("Best Candidate: ");
    for (int pos=0; pos<c; pos++) {
        int index = tracker[bestTeamIndex][pos];
        printf("%s ", cats[index].name);
    }
    printf("\n");

    MT_FREE(bestPerm);
}

// freeAll: function that will free all dynamically allocated memory
void freeAll(int n, int c, int r) {
    int totalCats = n * c;

    if (cats != NULL) {
        for (int i=0; i<totalCats; i++) {
            MT_FREE(cats[i].name);
            MT_FREE(cats[i].breed);
        }
        MT_FREE(cats);
        cats = NULL;
    }

    if (rivals != NULL) {
        MT_FREE(rivals);
        rivals = NULL;
    }

    if (tracker != NULL) {
        for (int i=0; i<n; i++) {
            MT_FREE(tracker[i]);
        }
        MT_FREE(tracker);
        tracker = NULL;
    }
}

int main(void) {
    // initialize the tool
    mt_init();

    int n, c, r;
    bestPermScore = 0;
    readInput(&n, &c, &r);
    createTracker(n, c);

    int totalCats = n*c;
    // use tool's MT_MALLOC to allocate memory
    int *perm = MT_MALLOC(totalCats * sizeof(int));
    int *used = calloc(totalCats, sizeof(int));

    permuteUsed(0, totalCats, perm, used, n, c, r);
    printBest(n, c, r);

    // use tool's MT_FREE to free memory allocated
    // with MT_MALLOC function
    MT_FREE(perm);
    free(used);
    freeAll(n, c, r);
    mt_shutdown();// <-- shutdown the tool and show stats

    return 0;
}
