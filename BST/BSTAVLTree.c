#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

AVLNode *createNode(int key) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode *insertAVL(AVLNode *node, int key) {
    if (node == NULL) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    } else if (key > node->key) {
        node->right = insertAVL(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(AVLNode *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(AVLNode *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(AVLNode *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

void freeAVL(AVLNode *root) {
    if (root == NULL) {
        return;
    }
    freeAVL(root->left);
    freeAVL(root->right);
    free(root);
}

int main() {
    AVLNode *root = NULL;
    int values[] = {30, 20, 40, 10, 25, 35, 50, 5, 15};
    int count = sizeof(values) / sizeof(values[0]);
    int ndx;

    for (ndx = 0; ndx < count; ndx++) {
        root = insertAVL(root, values[ndx]);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    freeAVL(root);
    return 0;
}
