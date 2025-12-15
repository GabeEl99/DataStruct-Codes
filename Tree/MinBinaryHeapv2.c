#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void upHeapifyMin(int arr[], int ndx) {
    while (ndx > 0) {
        int parent = (ndx - 1) / 2;
        if (arr[parent] > arr[ndx]) {
            swap(&arr[parent], &arr[ndx]);
            ndx = parent;
        } else {
            break;
        }
    }
}

void downHeapifyMin(int arr[], int n, int ndx) {
    while (1) {
        int left = 2 * ndx + 1;
        int right = 2 * ndx + 2;
        int smallest = ndx;

        if (left < n && arr[left] < arr[smallest]) {
            smallest = left;
        }
        if (right < n && arr[right] < arr[smallest]) {
            smallest = right;
        }
        if (smallest != ndx) {
            swap(&arr[ndx], &arr[smallest]);
            ndx = smallest;
        } else {
            break;
        }
    }
}

void insertMinHeap(int arr[], int *n, int value) {
    arr[*n] = value;
    upHeapifyMin(arr, *n);
    (*n)++;
}

int extractMin(int arr[], int *n) {
    if (*n == 0) {
        return -1;
    }
    int minVal = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    downHeapifyMin(arr, *n, 0);
    return minVal;
}

void buildMinHeap(int arr[], int n) {
    int ndx;
    for (ndx = n / 2 - 1; ndx >= 0; ndx--) {
        downHeapifyMin(arr, n, ndx);
    }
}

int main() {
    int heap[100];
    int n = 0;

    insertMinHeap(heap, &n, 52);
    insertMinHeap(heap, &n, 36);
    insertMinHeap(heap, &n, 12);
    insertMinHeap(heap, &n, 68);
    insertMinHeap(heap, &n, 48);

    int ndx;
    for (ndx = 0; ndx < n; ndx++) {
        printf("%d ", heap[ndx]);
    }
    printf("\n");

    int minVal = extractMin(heap, &n);
    printf("Extracted min: %d\n", minVal);

    for (ndx = 0; ndx < n; ndx++) {
        printf("%d ", heap[ndx]);
    }
    printf("\n");

    return 0;
}
