#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int isBalanced(Node *root) {
    if (root == NULL) {
        return 1;
    }
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    if (leftHeight - rightHeight > 1 || rightHeight - leftHeight > 1) {
        return 0;
    }
    
    return isBalanced(root->left) && isBalanced(root->right);
}

int isBalancedOptimal(Node *root, int *h) {
    if (root == NULL) {
        *h = 0;
        return 1;
    }
    
    int leftHeight = 0, rightHeight = 0;
    int leftBalanced = isBalancedOptimal(root->left, &leftHeight);
    int rightBalanced = isBalancedOptimal(root->right, &rightHeight);
    
    *h = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    
    if (leftHeight - rightHeight > 1 || rightHeight - leftHeight > 1) {
        return 0;
    }
    
    return leftBalanced && rightBalanced;
}

void inorder(Node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int count = sizeof(values) / sizeof(values[0]);
    int ndx;

    for (ndx = 0; ndx < count; ndx++) {
        root = insert(root, values[ndx]);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    if (isBalanced(root)) {
        printf("Tree is balanced\n");
    } else {
        printf("Tree is not balanced\n");
    }

    int h = 0;
    if (isBalancedOptimal(root, &h)) {
        printf("Tree is balanced (optimal check), height: %d\n", h);
    } else {
        printf("Tree is not balanced (optimal check)\n");
    }

    freeTree(root);
    return 0;
}
