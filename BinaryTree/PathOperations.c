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

int search(Node *root, int data, int path[], int *ndx) {
    if (root == NULL) {
        return 0;
    }
    
    path[*ndx] = root->data;
    (*ndx)++;
    
    if (root->data == data) {
        return 1;
    }
    
    if (search(root->left, data, path, ndx) || search(root->right, data, path, ndx)) {
        return 1;
    }
    
    (*ndx)--;
    return 0;
}

void printPath(int path[], int len) {
    int ndx;
    for (ndx = 0; ndx < len; ndx++) {
        printf("%d ", path[ndx]);
        if (ndx < len - 1) {
            printf("-> ");
        }
    }
    printf("\n");
}

Node *findLCA(Node *root, int a, int b) {
    if (root == NULL) {
        return NULL;
    }
    
    if ((a < root->data && b > root->data) || (a > root->data && b < root->data)) {
        return root;
    }
    
    if (a < root->data && b < root->data) {
        return findLCA(root->left, a, b);
    }
    
    if (a > root->data && b > root->data) {
        return findLCA(root->right, a, b);
    }
    
    return root;
}

void rootToLeafPaths(Node *root, int path[], int *ndx) {
    if (root == NULL) {
        return;
    }
    
    path[*ndx] = root->data;
    (*ndx)++;
    
    if (root->left == NULL && root->right == NULL) {
        printPath(path, *ndx);
    } else {
        rootToLeafPaths(root->left, path, ndx);
        rootToLeafPaths(root->right, path, ndx);
    }
    
    (*ndx)--;
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

    int path[100];
    int pathLen = 0;
    if (search(root, 40, path, &pathLen)) {
        printf("Path to 40: ");
        printPath(path, pathLen);
    }

    pathLen = 0;
    if (search(root, 60, path, &pathLen)) {
        printf("Path to 60: ");
        printPath(path, pathLen);
    }

    Node *lca = findLCA(root, 20, 40);
    if (lca != NULL) {
        printf("LCA of 20 and 40: %d\n", lca->data);
    }

    printf("Root to Leaf Paths:\n");
    pathLen = 0;
    rootToLeafPaths(root, path, &pathLen);

    freeTree(root);
    return 0;
}
