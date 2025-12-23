#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *root;
} PriorityQueue;

Node *createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insertBST(Node *root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insertBST(root->left, key);
    } else if (key > root->key) {
        root->right = insertBST(root->right, key);
    }
    return root;
}

Node *findMax(Node *root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

Node *deleteBST(Node *root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    } else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = findMax(root->left);
        root->key = temp->key;
        root->left = deleteBST(root->left, temp->key);
    }
    return root;
}

void initPQ(PriorityQueue *pq) {
    pq->root = NULL;
}

void enqueue(PriorityQueue *pq, int value) {
    pq->root = insertBST(pq->root, value);
}

int dequeue(PriorityQueue *pq) {
    Node *maxNode = findMax(pq->root);
    if (maxNode == NULL) {
        return -1;
    }
    int maxVal = maxNode->key;
    pq->root = deleteBST(pq->root, maxVal);
    return maxVal;
}

int peek(PriorityQueue *pq) {
    Node *maxNode = findMax(pq->root);
    if (maxNode == NULL) {
        return -1;
    }
    return maxNode->key;
}

void inorder(Node *root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void display(PriorityQueue *pq) {
    inorder(pq->root);
    printf("\n");
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
    PriorityQueue pq;
    initPQ(&pq);

    enqueue(&pq, 15);
    enqueue(&pq, 10);
    enqueue(&pq, 20);
    enqueue(&pq, 8);
    enqueue(&pq, 5);

    printf("Tree (inorder): ");
    display(&pq);

    printf("Peek: %d\n", peek(&pq));

    printf("Dequeued: %d\n", dequeue(&pq));
    printf("Tree (inorder): ");
    display(&pq);

    printf("Dequeued: %d\n", dequeue(&pq));
    printf("Tree (inorder): ");
    display(&pq);

    freeTree(pq.root);
    return 0;
}
