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

void insertMaxHeap(int arr[], int *n, int value) {
    arr[*n] = value;
    upHeapify(arr, *n);
    (*n)++;
}

int extractMax(int arr[], int *n) {
    if (*n == 0) {
        return -1;
    }
    int maxVal = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    downHeapify(arr, *n, 0);
    return maxVal;
}

void buildMaxHeap(int arr[], int n) {
    int ndx;
    for (ndx = n / 2 - 1; ndx >= 0; ndx--) {
        downHeapify(arr, n, ndx);
    }
}

int main() {
    int heap[100];
    int n = 0;

    insertMaxHeap(heap, &n, 5);
    insertMaxHeap(heap, &n, 2);
    insertMaxHeap(heap, &n, 8);
    insertMaxHeap(heap, &n, 3);
    insertMaxHeap(heap, &n, 6);

    int ndx;
    for (ndx = 0; ndx < n; ndx++) {
        printf("%d ", heap[ndx]);
    }
    printf("\n");

    int maxVal = extractMax(heap, &n);
    printf("Extracted max: %d\n", maxVal);

    for (ndx = 0; ndx < n; ndx++) {
        printf("%d ", heap[ndx]);
    }
    printf("\n");

    return 0;
}
