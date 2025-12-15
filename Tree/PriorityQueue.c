#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void upHeapify(int arr[], int ndx) {
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

void downHeapify(int arr[], int n, int ndx) {
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

typedef struct {
    int data[100];
    int size;
} PriorityQueue;

void initPQ(PriorityQueue *pq) {
    pq->size = 0;
}

int isEmptyPQ(PriorityQueue *pq) {
    return pq->size == 0;
}

void enqueue(PriorityQueue *pq, int value) {
    pq->data[pq->size] = value;
    upHeapify(pq->data, pq->size);
    pq->size++;
}

int dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        return -1;
    }
    int top = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    downHeapify(pq->data, pq->size, 0);
    return top;
}

int peekPQ(PriorityQueue *pq) {
    if (pq->size == 0) {
        return -1;
    }
    return pq->data[0];
}

int main() {
    PriorityQueue pq;
    initPQ(&pq);

    enqueue(&pq, 5);
    enqueue(&pq, 2);
    enqueue(&pq, 8);
    enqueue(&pq, 3);
    enqueue(&pq, 6);

    int ndx;
    for (ndx = 0; ndx < pq.size; ndx++) {
        printf("%d ", pq.data[ndx]);
    }
    printf("\n");

    printf("Top: %d\n", peekPQ(&pq));

    printf("Dequeued: %d\n", dequeue(&pq));
    printf("Dequeued: %d\n", dequeue(&pq));

    for (ndx = 0; ndx < pq.size; ndx++) {
        printf("%d ", pq.data[ndx]);
    }
    printf("\n");

    return 0;
}
