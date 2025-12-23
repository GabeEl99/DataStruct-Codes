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

int countNodes(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return countNodes(root->left) + countNodes(root->right) + 1;
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

int sumNodes(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return root->data + sumNodes(root->left) + sumNodes(root->right);
}

Node *mirror(Node *root) {
    if (root == NULL) {
        return NULL;
    }
    
    Node *left = mirror(root->left);
    Node *right = mirror(root->right);
    
    root->left = right;
    root->right = left;
    
    return root;
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

    printf("Height: %d\n", height(root));
    printf("Total Nodes: %d\n", countNodes(root));
    printf("Leaf Nodes: %d\n", countLeaves(root));
    printf("Sum of Nodes: %d\n", sumNodes(root));

    mirror(root);
    printf("Inorder after Mirror: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
