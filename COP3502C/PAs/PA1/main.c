/*              COP 3502C PA1
This program is written by: Yurii Hriaziev */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// required data structires
typedef struct Cat {
    char *name;
    int age;
    float weight;
    char *breed;
    int status;
} Cat;

typedef struct Kennel {
    char *location;
    int occupancy;
    Cat **cats;
    int maxCapacity;
} Kennel;

typedef struct CatStore {
    int **capacities;
    int numKenels;
    Kennel *kennels;
} CatStore;

const char STATUS_CAT[3][20] = {"ADOPTED", "PENDING", "AVAILABLE"};

char **readBreeds(int *count);

char *getCharPtrByBreed(char **dictionary, char *breedName, int breedCount);

CatStore *createStore(int kennelCount, int breedCount, char **dictionary);

Kennel *createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary);

Cat **createCats(char **dictionary, int breedCount, int count);

Cat *createSingleCat(char **dictionary, int breedCount);

int canMoveTo(CatStore *s, char *location, char *breed, char **dictionary, int breedCount);

Kennel *getKennelByCat(CatStore *s, Cat *cat);

int getCatPosi(Kennel *home, Cat *cat);

Cat *getCatByName(CatStore *s, char *catName);

void removeCatFromKennel(Kennel *k, Cat *cat);

void runQueries(CatStore *s, char **dictionary, int breedCount, int numQueries);

void freeBreeds(char **dictionary, int breedCount);

void freeStore(int count, CatStore *store);

void printCatInfo(Cat *cat, char *location);

// function to read the breeds of cats and allocate appropriate amount of memory for each breed
// returns the dictionary
char **readBreeds(int *count) {
    scanf("%d", count);

    char **dictionary = malloc((*count) * sizeof(char *));

    for (int i=0; i<*count; i++) {
        char tempName[26];
        scanf("%s", tempName);

        int nameLen = strlen(tempName) + 1;
        dictionary[i] = malloc(nameLen * sizeof(char));
        strcpy(dictionary[i], tempName);
    }

    return dictionary;
}

// function that frees the main dictionary and each memory address inside that dictionary
void freeBreeds(char **dictionary, int breedCount) {
    for (int i=0; i<breedCount; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
}

// function the gets a breed pointer for a given breed name
// returns that pointer if found, otherwise returns a NULL pointer
char *getCharPtrByBreed(char **dictionary, char *breedName, int breedCount) {
    for (int i=0; i<breedCount; i++) {
        if (strcmp(dictionary[i], breedName) == 0) {
            return dictionary[i];
        }
    }

    return NULL;
}

// function that creates a single Cat pointer from input
// allocates appropriate space for the name and breed struct parameters
// saves a pointer to the breed based on the given breed from input
// returns the created cat pointer
Cat *createSingleCat(char **dictionary, int breedCount) {
    Cat *cat = malloc(sizeof(Cat));

    char tempName[26];
    char tempBreed[26];

    scanf("%s %d %f %s", tempName, &cat->age, &cat->weight, tempBreed);
    int nameLen = strlen(tempName) + 1;
    cat->name = malloc(nameLen * sizeof(char));
    strcpy(cat->name, tempName);

    cat->breed = getCharPtrByBreed(dictionary, tempBreed, breedCount);
    cat->status = 2;

    return cat;
}

// function to create an array of cat pointers from inputs, utilizes Cat *createSingleCat for cat creation
// returns the array of cat pointers
Cat **createCats(char **dictionary, int breedCount, int count) {
    Cat **cats = malloc(count * sizeof(Cat *));

    for (int i=0; i<count; i++) {
        cats[i] = createSingleCat(dictionary, breedCount);
    }
    return cats;
}

// function that creates kennelCount amount of kennels
// creates and allocates needed amount of memmory for an array of Kennels
// stores location with its appropriate memory, number of cats, array of cat pointers for every cat, and max capacity
// returns the created array of Kennels
Kennel *createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary) {
    Kennel *kennels = malloc(kennelCount * sizeof(Kennel));

    for (int i=0; i<kennelCount; i++) {
        char tempLoc[26];
        int numCats;

        scanf("%s %d", tempLoc, &numCats);
        int locLen = strlen(tempLoc) + 1;
        kennels[i].location = malloc(locLen * sizeof(char));
        strcpy(kennels[i].location, tempLoc);
        kennels[i].occupancy = numCats;

        if (numCats == 0) {
            kennels[i].cats = NULL;
        } else {
            kennels[i].cats = createCats(dictionary, breedCount, numCats);
        }

        int sum = 0;
        for (int j=0; j<breedCount; j++) {
            sum += constraints[i][j];
        }
        kennels[i].maxCapacity = sum;
    }

    return kennels;
}

// function to create a store pointer with appropriate memory size
// create all kennels of appropriate size
// creates all cats and updates other store statistics such as kennel count, capacities and actual kennels
// returns the store pointer
CatStore *createStore(int kennelCount, int breedCount, char **dictionary) {
    CatStore *store = malloc(sizeof(CatStore));

    store->numKenels = kennelCount;
    store->capacities = malloc(kennelCount * sizeof(int *));
    for (int i=0; i<kennelCount; i++) {
        store->capacities[i] = malloc(breedCount * sizeof(int));
        for (int j=0; j<breedCount; j++) {
            scanf("%d", &store->capacities[i][j]);
        }
        
    }
    store->kennels = createKennels(store->capacities, kennelCount, breedCount, dictionary);

    return store;
}

// function that returns the index of a given cat pointer from a given kennel pointer
// return -1 if kennel is undefined or cat pointer not found
// return the index of the found cat pointer
int getCatPosi(Kennel *home, Cat *cat) {
    if (home == NULL) {
        return -1;
    }

    for (int i=0; i<home->occupancy; i++) {
        if (home->cats[i] == cat) {
            return i;
        }
    }

    return -1;
}

// function that finds the pointer to a kennel from a given cat pointer
// return the address of that kennel if cat found
// return NULL if cat not found
Kennel *getKennelByCat(CatStore *s, Cat *cat) {
    if (s == NULL || cat == NULL) {
        return NULL;
    }

    for (int i=0; i<s->numKenels; i++) {
        if (getCatPosi(&s->kennels[i], cat) != -1) {
            return &s->kennels[i];
        }
    }

    return NULL;
}

// function to find a pointer to a cat with the given cat name
// return the pointer to that found cat if found
// return NULL if cat now found
Cat *getCatByName(CatStore *s, char *catName) {
    if (s == NULL || catName == NULL) {
        return NULL;
    }
    for (int i=0; i<s->numKenels; i++) {
        for (int j=0; j<s->kennels[i].occupancy; j++) {
            if (strcmp(s->kennels[i].cats[j]->name, catName) == 0) {
                return s->kennels[i].cats[j];
            }
        }
    }

    return NULL;
}

// function to remove a given cat from a given kennel
// find the index of that cat from that kennel
// starts looping from that index and shifts the remaining cats to fill the gap
// decreases occupancy of that given kennel
// if the occupancy becomes 0, free the memory of cats list in the given kennel
// otherwise resize the memory of the cats list for the given kennel to new occupancy
void removeCatFromKennel(Kennel *k, Cat *cat) {
    if (k == NULL || cat == NULL) {
        return;
    }

    int catIndex = getCatPosi(k, cat);
    if (catIndex == -1) {
        return;
    }

    for (int i=catIndex; i<k->occupancy - 1; i++) {
        k->cats[i] = k->cats[i + 1];
    }

    k->occupancy -= 1;

    if (k->occupancy == 0) {
        free(k->cats);
        k->cats = NULL;
    } else {
        k->cats = realloc(k->cats, k->occupancy * sizeof(Cat *));
    }
}

// function to check if a cat of given breed can be moved to another location
// 1. find the pointer to the destination kennel and save its index
// 1a. return 0 if the pointer to the destination kennel not found
// 2. check if that kennel has space for an extra cat
// 2a. return 0 if kennel is full
// 3. find the breed the breed that is being moved to that new location from dictonary
// 3a. return 0 if breed is not found, even though it is guaranteed to be found
// 4. cound and store all cats of the given breed in a variable
// 4a. return 0 if the count of that breed + 1 exceeds the store's capacity for that breed in that kennel
// return 1 since all checks were passed and cat can successfully be relocated to the new kennel location
int canMoveTo(CatStore *s, char *location, char *breed, char **dictionary, int breedCount) {
    if (s == NULL || location == NULL || breed == NULL) {
        return 0;
    }

    Kennel *destKennel = NULL;
    int kennelIndex = -1;
    for (int i=0; i<s->numKenels; i++) {
        if (strcmp(s->kennels[i].location, location) == 0) {
            destKennel = &s->kennels[i];
            kennelIndex = i;
            break;
        }
    }

    if (destKennel == NULL) {
        return 0;
    }

    if (destKennel->occupancy+1 > destKennel->maxCapacity) {
        return 0;
    }

    int breedIndex = -1;
    for (int i=0; i<breedCount; i++) {
        if (strcmp(dictionary[i], breed) == 0) {
            breedIndex = i;
            break;
        }
    }
    if (breedIndex == -1) {
        return 0;
    }

    int breedCountInKennel = 0;
    for (int i=0; i<destKennel->occupancy; i++) {
        if (destKennel->cats[i]->breed == dictionary[breedIndex]) {
            breedCountInKennel += 1;
        }
    }

    if (breedCountInKennel + 1 > s->capacities[kennelIndex][breedIndex]) {
        return 0;
    }

    return 1;
}

// helper function to print the result of query type 1
void printCatInfo(Cat *cat, char *location) {
    printf("%s %.2f %d %s %s\n", cat->name, cat->weight, cat->age, location, STATUS_CAT[cat->status]);
}

// function that will run queries based on their type (1, 2, 3)
void runQueries(CatStore *s, char **dictionary, int breedCount, int numQueries) {
    if (s == NULL || dictionary == NULL) {
        return;
    }

    for (int i=0; i<numQueries; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            char tempBreed[26];
            scanf("%s", tempBreed);

            int found = 0;
            char *breedPtr = getCharPtrByBreed(dictionary, tempBreed, breedCount);
            for (int j=0; j<s->numKenels; j++) {
                for (int k=0; k<s->kennels[j].occupancy; k++) {
                    Cat *cat = s->kennels[j].cats[k];
                    if (cat->breed == breedPtr) {
                        printCatInfo(cat, s->kennels[j].location);
                        found = 1;
                    }
                }
            }
            
            if (found == 0) {
                printf("No cat with breed %s\n", tempBreed);
            }
        } else if (type == 2) {
            int newStatus;
            char tempName[26];
            scanf("%d %s", &newStatus, tempName);

            Cat *cat = getCatByName(s, tempName);
            if (cat == NULL) {
                continue;
            }
            cat->status = newStatus;
            printf("%s is now %s!\n", cat->name, STATUS_CAT[cat->status]);

            if (cat->status == 0) {
                Kennel *catKennel = getKennelByCat(s, cat);
                if (catKennel != NULL) {
                    removeCatFromKennel(catKennel, cat);
                }

                free(cat->name);
                free(cat);
            }
        } else if (type == 3) {
            char catName[26];
            char destLoc[26];
            scanf("%s %s", catName, destLoc);

            Cat *cat = getCatByName(s, catName);
            if (cat == NULL) {
                continue;
            }

            if (!canMoveTo(s, destLoc, cat->breed, dictionary, breedCount)) {
                printf("%s cannot take a %s cat!\n", destLoc, cat->breed);
                continue;
            }

            Kennel *catKennel = getKennelByCat(s, cat);
            if (catKennel != NULL) {
                removeCatFromKennel(catKennel, cat);
            }

            Kennel *destKennel = NULL;
            for (int j=0; j<s->numKenels; j++) {
                if (strcmp(s->kennels[j].location, destLoc) == 0) {
                    destKennel = &s->kennels[j];
                    break;
                }
            }

            if (destKennel != NULL) {
                destKennel->cats = realloc(destKennel->cats, (destKennel->occupancy+1) * sizeof(Cat *));
                destKennel->cats[destKennel->occupancy] = cat;
                destKennel->occupancy += 1;
            }

            printf("%s moved successfully to %s\n", cat->name, destLoc);
        }
    }
}

// function to free the entire store
// checks if there are any cats, kennels, locations and any other allocated memory that can be freed and frees it
void freeStore(int count, CatStore *store) {
    if (store == NULL) {
        return;
    }

    if (store->kennels != NULL) {
        for (int i=0; i<count; i++) {
            if (store->kennels[i].cats != NULL) {
                for (int j=0; j<store->kennels[i].occupancy; j++) {
                    Cat *cat = store->kennels[i].cats[j];
                    if (cat != NULL) {
                        free(cat->name);
                        free(cat);
                    }
                }

                free(store->kennels[i].cats);
                store->kennels[i].cats = NULL;
            }

            free(store->kennels[i].location);
            store->kennels[i].location = NULL;
        }

        free(store->kennels);
        store->kennels = NULL;
    }

    if (store->capacities != NULL) {
        for (int i=0; i<count; i++) {
            free(store->capacities[i]);
            store->capacities[i] = NULL;
        }
        free(store->capacities);
        store->capacities = NULL;
    }

    free(store);
}

// main function that create the store
// tests the store with different queries
int main(void) {
    char **dictionary;
    int breedCount;

    dictionary = readBreeds(&breedCount);

    int kennelCount;
    scanf("%d", &kennelCount);

    CatStore *store = createStore(kennelCount, breedCount, dictionary);

    int numQueries;
    scanf("%d", &numQueries);

    runQueries(store, dictionary, breedCount, numQueries);

    freeStore(kennelCount, store);
    freeBreeds(dictionary, breedCount);

    return 0;
}