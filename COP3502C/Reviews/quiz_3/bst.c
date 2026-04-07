#include <stdio.h>
#include <stdlib.h>

typedef struct bstNode {
    int data;
    struct bstNode *left;
    struct bstNode *right;
} bstNode;

// function to find minimum leaf in a bst
bstNode *find_min_leaf(bstNode *root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL && root->right == NULL) {
        return root;
    }

    if (root->left != NULL) {
        find_min_leaf(root->left);
    }

    return find_min_leaf(root->right);
}

void preorder(bstNode *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(bstNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(bstNode *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

bstNode *create_node(int val) {
    bstNode *tree_node = malloc(sizeof(bstNode));

    tree_node->data = val;
    tree_node->left = NULL;
    tree_node->right = NULL;

    return tree_node;
}

bstNode *insert_node(bstNode *root, bstNode *new_node) {
    if (root == NULL) {
        return new_node;
    } else {
        if (new_node->data > root->data) {
            if (root->right != NULL) {
                root->right = insert_node(root->right, new_node);
            } else {
                root->right = new_node;
            }
        } else {
            if (root->left != NULL) {
                root->left = insert_node(root->left, new_node);
            } else {
                root->left = new_node;
            }
        }
    }

    return root;
}

int sum_of_tree(bstNode *root) {
    if (root != NULL) {
        return root->data + add(root->left) + add(root->right);
    } else {
        return 0;
    }
}

int find(bstNode *root, int val) {
    if (root != NULL) {
        
    }
}