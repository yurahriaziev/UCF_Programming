/*              COP 3502C PA 5
This program is written by: Yurii Hriaziev */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// given code
#define MAX_NAME 25 // max name of a cat
#define NUM_TRAITS 5 // number of total traits a cat has
typedef struct Cat {
    char *name; //dynamically allocate space for a cat’s name
    char *breed; //dynamically allocate space for a cat’s breed
    int charm; //unique charm score for each cat
    int traits[NUM_TRAITS]; //scores corresponding to each index in TRAIT_NAMES
} Cat;

typedef struct BST_Node {
    Cat *cat;
    struct BST_Node *left;
    struct BST_Node *right;
    int subtree_size;
} BST_Node;

const char *TRAIT_NAMES[NUM_TRAITS] = {"friendly", "grumpy", "playful", "lazy", "curious"};
// end given code

// function prototypes
Cat *createCat();
BST_Node *createBSTNode(Cat *cat);
BST_Node *findNode(BST_Node *root, char *name);
int countTraitsForCat(Cat *cat);

// createCat: function that will create a new cat with given name, breed, charm and traits
Cat *createCat() {
    Cat *newCat = malloc(sizeof(Cat));

    char tempName[MAX_NAME+1];
    char tempBreed[MAX_NAME+1];
    int charm;
    
    scanf("%s %s %d", tempName, tempBreed, &charm);

    newCat->name = malloc((strlen(tempName) + 1) * sizeof(char));
    strcpy(newCat->name, tempName);
    
    newCat->breed = malloc((strlen(tempBreed) + 1) * sizeof(char));
    strcpy(newCat->breed, tempBreed);

    newCat->charm = charm;

    for (int i=0; i<NUM_TRAITS; i++) {
        scanf("%d", &newCat->traits[i]);
    }

    return newCat;
}

// createBSTNode: function that creates a new BST Node for a given cat
BST_Node *createBSTNode(Cat *cat) {
    BST_Node *newNode = malloc(sizeof(BST_Node));

    newNode->cat = cat;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->subtree_size = 1;

    return newNode;
}

BST_Node *findNode(BST_Node *root, char *name) {
    if (root != NULL) {
        if (strcmp(root->cat->name, name) == 0) {
            return root;
        }

        if (strcmp(name, root->cat->name) < 0) {
            return findNode(root->left, name);
        } else {
            return findNode(root->right, name);
        }
    }

    return NULL;
}

int countTraitsForCat(Cat *cat) {
    int count = 0;

    if (cat == NULL) {
        return 0;
    }

    for (int i=0; i<NUM_TRAITS; i++) {
        if (cat->traits[i] == 1) {
            count+=1;
        }
    }

    return count;
}

int main() {
    return 0;
}