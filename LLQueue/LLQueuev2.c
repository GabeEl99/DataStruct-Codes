#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *front;  /* points to last node */
    Node *rear;   /* points to first node */
} Queue;

Queue* initialize();
bool isFull(Queue *q);
bool isEmpty(Queue *q);
bool enqueue(Queue *q, int value);
int dequeue(Queue *q, bool *ok);
int front(Queue *q, bool *ok);
void display(Queue *q);

Queue* initialize(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL){
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isFull(Queue *q){
    return false;
}

bool isEmpty(Queue *q){
    return q->rear == NULL;
}

bool enqueue(Queue *q, int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        return false;
    }

    newNode->data = value;
    newNode->next = NULL;

    if(isEmpty(q)){
        q->rear = newNode;
        q->front = newNode;
    }else{
        newNode->next = q->rear;
        q->rear = newNode;
    }

    return true;
}

int dequeue(Queue *q, bool *ok){
    if(isEmpty(q)){
        if(ok) *ok = false;
        return -1;
    }

    Node *prev = NULL;
    Node *curr = q->rear;

    while(curr->next != NULL){
        prev = curr;
        curr = curr->next;
    }

    int value = curr->data;

    if(prev == NULL){
        q->rear = NULL;
        q->front = NULL;
    }else{
        prev->next = NULL;
        q->front = prev;
    }

    free(curr);

    if(ok) *ok = true;
    return value;
}

int front(Queue *q, bool *ok){
    if(isEmpty(q)){
        if(ok) *ok = false;
        return -1;
    }
    if(ok) *ok = true;
    return q->front->data;
}

void display(Queue *q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }

    Node *current = q->rear;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(){
    Queue *Q = initialize();
    bool ok;

    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 5);
    enqueue(Q, 4);
    display(Q);

    int value = dequeue(Q, &ok);
    if(ok){
        printf("dequeued: %d\n", value);
    }
    display(Q);

    int f = front(Q, &ok);
    if(ok){
        printf("front: %d\n", f);
    }

    while(!isEmpty(Q)){
        dequeue(Q, &ok);
    }
    display(Q);

    free(Q);
    return 0;
}
