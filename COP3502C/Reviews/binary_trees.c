#include <stdio.h>

typedef struct tree_node {
    struct tree_node *left;
    struct tree_node *right;
    int data;
} tree_node;

// void preorder(tree_node *root) {
//     if (root != NULL) {
//         printf("%d ", root->data);
//         preorder(root->left);
//         preorder(root->right);
//     }
// }

// void postorder(tree_node *root) {
//     if (root != NULL) {
//         preorder(root->left);
//         preorder(root->right);
//         printf("%d ", root->data);
//     }
// }

tree_node *create_node(int data) {
    
}

int main() {

    return 0;
}