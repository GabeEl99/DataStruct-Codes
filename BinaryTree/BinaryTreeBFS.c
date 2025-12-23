#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *arr[100];
    int front;
    int rear;
} Queue;

Node *createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Queue *createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = -1;
    return q;
}

void enqueue(Queue *q, Node *node) {
    q->arr[++q->rear] = node;
}

Node *dequeue(Queue *q) {
    return q->arr[q->front++];
}

int isEmpty(Queue *q) {
    return q->front > q->rear;
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

void bfs(Node *root) {
    if (root == NULL) {
        return;
    }
    
    Queue *q = createQueue();
    enqueue(q, root);
    
    while (!isEmpty(q)) {
        Node *node = dequeue(q);
        printf("%d ", node->data);
        
        if (node->left != NULL) {
            enqueue(q, node->left);
        }
        if (node->right != NULL) {
            enqueue(q, node->right);
        }
    }
    
    free(q);
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

    printf("BFS (Level-Order): ");
    bfs(root);
    printf("\n");

    freeTree(root);
    return 0;
}
