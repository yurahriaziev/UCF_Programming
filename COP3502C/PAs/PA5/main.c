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
BST_Node *insert(BST_Node *root, BST_Node *newNode, int depth);
void freeCat(Cat *cat);

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

// findNode: function that will find a return the BST node in the BST with a given key which is the name of the cat
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

// countTraitsForCat: helper function that will return the count of traits a cat has if a duplicate cat is being inserted
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

// insert: 
BST_Node *insert(BST_Node *root, BST_Node *newNode, int depth) {
    if (root == NULL) {
        printf("Insert: %d\n", depth);
        return newNode;
    }

    if (strcmp(newNode->cat->name, root->cat->name) == 0) {
        if (countTraitsForCat(newNode->cat) > countTraitsForCat(root->cat)) {
            freeCat(root->cat);

            root->cat = newNode->cat;
            free(newNode);

            printf("Replaced\n");
        } else {
            free(newNode->cat->name);
            free(newNode->cat->breed);
            free(newNode->cat);
            free(newNode);
        }
        return root;
    }

    if (strcmp(newNode->cat->name, root->cat->name) < 0) {
        root->left = insert(root->left, newNode, depth+1);
    } else {
        root->right = insert(root->right, newNode, depth+1);
    }

    root->subtree_size = 1;
    if (root->left != NULL) {
        root->subtree_size += root->left->subtree_size;
    }
    if (root->right != NULL) {
        root->subtree_size += root->right->subtree_size;
    }

    return root;
}

void freeCat(Cat *cat) {
    free(cat->name);
    free(cat->breed);
    free(cat);
}

int main() {
    BST_Node *root = NULL;
    int num_ops;
    int q;

    scanf("%d", &num_ops);

    for (int i=0; i<num_ops; i++) {
        scanf("%d", &q);

        if (q == 1) {
            Cat *newCat = createCat();
            BST_Node *newNode = createBSTNode(newCat);
            root = insert(root, newNode, 0);
        }
    }

    return 0;
}