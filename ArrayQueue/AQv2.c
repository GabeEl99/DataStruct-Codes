#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue* initialize();
bool isEmpty(Queue *q);
bool isFull(Queue *q);
bool enqueue(Queue *q, int value);
int dequeue(Queue *q, bool *ok);
int front(Queue *q, bool *ok);
void display(Queue *q);

Queue* initialize(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if(q == NULL){
        return NULL;
    }
    q->front = 1;
    q->rear = 0;
    return q;
}

bool isEmpty(Queue *q){
    return q->front == (q->rear + 1) % MAX;
}

bool isFull(Queue *q){
    return q->front == (q->rear + 2) % MAX;
}

bool enqueue(Queue *q, int value){
    if(isFull(q)){
        return false;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    return true;
}

int dequeue(Queue *q, bool *ok){
    if(isEmpty(q)){
        if(ok) *ok = false;
        return -1;
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    if(ok) *ok = true;
    return value;
}

int front(Queue *q, bool *ok){
    if(isEmpty(q)){
        if(ok) *ok = false;
        return -1;
    }
    if(ok) *ok = true;
    return q->items[q->front];
}

void display(Queue *q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }

    int ndx = q->front;
    while(ndx != (q->rear + 1) % MAX){
        printf("%d ", q->items[ndx]);
        ndx = (ndx + 1) % MAX;
    }
    printf("\n");
}

int main(){
    Queue *Q = initialize();
    bool ok;

    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 2);
    enqueue(Q, 5);
    display(Q);

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

    free(Q);
    return 0;
}
