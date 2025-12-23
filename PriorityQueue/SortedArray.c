#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[100];
    int size;
} PriorityQueue;

void initPQ(PriorityQueue *pq) {
    pq->size = 0;
}

void enqueue(PriorityQueue *pq, int value) {
    int ndx = pq->size - 1;
    
    while (ndx >= 0 && pq->data[ndx] > value) {
        pq->data[ndx + 1] = pq->data[ndx];
        ndx--;
    }
    
    pq->data[ndx + 1] = value;
    pq->size++;
}

int dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        return -1;
    }
    int top = pq->data[pq->size - 1];
    pq->size--;
    return top;
}

int peek(PriorityQueue *pq) {
    if (pq->size == 0) {
        return -1;
    }
    return pq->data[pq->size - 1];
}

void display(PriorityQueue *pq) {
    int ndx;
    for (ndx = 0; ndx < pq->size; ndx++) {
        printf("%d ", pq->data[ndx]);
    }
    printf("\n");
}

int main() {
    PriorityQueue pq;
    initPQ(&pq);

    enqueue(&pq, 15);
    enqueue(&pq, 10);
    enqueue(&pq, 20);
    enqueue(&pq, 8);
    enqueue(&pq, 5);

    printf("Array: ");
    display(&pq);

    printf("Peek: %d\n", peek(&pq));

    printf("Dequeued: %d\n", dequeue(&pq));
    printf("Array: ");
    display(&pq);

    printf("Dequeued: %d\n", dequeue(&pq));
    printf("Array: ");
    display(&pq);

    return 0;
}
