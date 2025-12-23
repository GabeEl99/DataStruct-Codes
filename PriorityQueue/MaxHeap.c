#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[100];
    int size;
} PriorityQueue;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void upHeapifyMax(int arr[], int ndx) {
    while (ndx > 0) {
        int parent = (ndx - 1) / 2;
        if (arr[parent] < arr[ndx]) {
            swap(&arr[parent], &arr[ndx]);
            ndx = parent;
        } else {
            break;
        }
    }
}

void downHeapifyMax(int arr[], int n, int ndx) {
    while (1) {
        int left = 2 * ndx + 1;
        int right = 2 * ndx + 2;
        int largest = ndx;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != ndx) {
            swap(&arr[ndx], &arr[largest]);
            ndx = largest;
        } else {
            break;
        }
    }
}

void initPQ(PriorityQueue *pq) {
    pq->size = 0;
}

void enqueue(PriorityQueue *pq, int value) {
    pq->data[pq->size] = value;
    upHeapifyMax(pq->data, pq->size);
    pq->size++;
}

int dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        return -1;
    }
    int top = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    downHeapifyMax(pq->data, pq->size, 0);
    return top;
}

int peek(PriorityQueue *pq) {
    if (pq->size == 0) {
        return -1;
    }
    return pq->data[0];
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

    printf("Heap: ");
    display(&pq);

    printf("Peek: %d\n", peek(&pq));

    printf("Dequeued: %d\n", dequeue(&pq));
    printf("Heap: ");
    display(&pq);

    printf("Dequeued: %d\n", dequeue(&pq));
    printf("Heap: ");
    display(&pq);

    return 0;
}
