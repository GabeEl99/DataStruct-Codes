#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List list;
    int front;
    int rear;
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
    q->list.count = 0;
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isFull(Queue *q){
    return q->list.count == MAX;
}

bool isEmpty(Queue *q){
    return q->list.count == 0;
}

bool enqueue(Queue *q, int value){
    if(isFull(q)){
        return false;
    }

    if(isEmpty(q)){
        q->front = 0;
        q->rear = 0;
    }else{
        q->rear = (q->rear + 1) % MAX;
    }

    q->list.items[q->rear] = value;
    q->list.count++;
    return true;
}

int dequeue(Queue *q, bool *ok){
    if(isEmpty(q)){
        if(ok) *ok = false;
        return -1;
    }

    int value = q->list.items[q->front];

    if(q->list.count == 1){
        q->front = -1;
        q->rear = -1;
    }else{
        q->front = (q->front + 1) % MAX;
    }

    q->list.count--;
    if(ok) *ok = true;
    return value;
}

int front(Queue *q, bool *ok){
    if(isEmpty(q)){
        if(ok) *ok = false;
        return -1;
    }
    if(ok) *ok = true;
    return q->list.items[q->front];
}

void display(Queue *q){
    if(isEmpty(q)){
        printf("Queue is empty\n");
        return;
    }

    int ndx = q->front;
    int printed = 0;

    while(printed < q->list.count){
        printf("%d ", q->list.items[ndx]);
        ndx = (ndx + 1) % MAX;
        printed++;
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
