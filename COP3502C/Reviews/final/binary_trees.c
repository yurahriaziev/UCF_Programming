#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct heapStruct {
    int *heapArray;
    int cap;
    int size;
} heapStruct;

Node *createNode(int value);
void inorder(Node *root);
void preorder(Node *root);
void postorder(Node *root);
int height(Node *root);
int countNodes(Node *root);
int countLeaves(Node *root);
struct Node* parent( Node *root,  Node *node);
struct Node* minVal( Node *root);
struct Node* maxVal( Node *root);
int isLeaf( Node *node);
int hasOnlyLeftChild( Node *node);
int hasOnlyRightChild( Node *node);

// Binary Search Tree funcss
Node *insert(Node *root, int val);
Node *search(Node *root, int val);
Node *delete(Node *root, int val);
Node *findMin(Node *root);
Node *findMax(Node *root);

// Heap funcs
void percolateDown(heapStruct *h, int index);
void percolateUp(heapStruct *h, int index);

// DELETION
// 3 cases:
// 1. No children → delete node
// 2. One child → replace node with child
// 3. Two children → replace with inorder successor

// The inorder successor is the minimum node on the right subtree

// Runtime analysis
// For BST:
// Average case: O(log n)
// Worst case: O(n)

// function implementation
Node *createNode(int value) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        return NULL;
        // mem allocation failed
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void inorder(Node *root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node *root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int countNodes(Node *root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(Node *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return countLeaves(root->left) + countLeaves(root->right);
}

Node *insert(Node *root, int val) {
    if (root == NULL) {
        return createNode(val);
    }

    if (val > root->data) {
        if (root->right != NULL) {
            root->right = insert(root->right, val);
        } else {
            root->right = createNode(val);
        }
    } else {
        if (root->left != NULL) {
            root->left = insert(root->left, val);
        } else {
            root->left = createNode(val);
        }
    }

    return root;
}

Node *search(Node *root, int val) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == val) {
        return root;
    }

    if (val > root->data) {
        return search(root->right, val);
    } else {
        return search(root->left, val);
    }
}

Node *findMin(Node *root) {
    if (root->left == NULL) {
        return root;
    }
    return findMin(root->left);
}

int add(Node *root) {
    if (root != NULL) {
        return root->data + add(root->left) + add(root->right);
    } else {
        return 0;
    }
}

Node *parent(Node *root, Node *node) {
    
}

// Returns indexa if a < b, and returns indexb otherwise.
int minimum(int a, int indexa, int b, int indexb) {
    // Return the value associated with a.
    if (a < b)
        return indexa;
        // Return the value associated with b.
    else
        return indexb;
}

void percolateDown(heapStruct *h, int index) {
    int min;

    if ((2*index+1) <= h->size) {
        min = minimum(h->heapArray[2*index], 2*index, h->heapArray[2*index+1], 2*index+1);

        if (h->heapArray[index] > h->heapArray[min]) {
            swap(h, index, min);
            percolateDown(h, min);
        }
    } else if (h->size == 2*index) {
        if (h->heapArray[index] > h->heapArray[2*index]) {
            swap(h, index, 2*index);
        }
    }
}

void percolateUp(heapStruct *h, int index) {
    if (index > 1) {
        if (h->heapArray[index/2] < h->heapArray[index]) {
            swap(h, index, index/2);
            percolateUp(h, index/2);
        }
    }
}

void swap(heapStruct *h, int indexA, int indexB) {
    int temp = h->heapArray[indexA];
    h->heapArray[indexA] = h->heapArray[indexB];
    h->heapArray[indexB] = temp;
}

int main() {
    Node *root = createNode(10);

    printf("%d\n", root->data);

    free(root);
    return 0;
}