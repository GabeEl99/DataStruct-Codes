#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
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

void buildMinHeap(int arr[], int n) {
    int ndx;
    for (ndx = n / 2 - 1; ndx >= 0; ndx--) {
        downHeapifyMin(arr, n, ndx);
    }
}

void heapSortMinAscending(int arr[], int n) {
    buildMinHeap(arr, n);
    
    int sorted[100];
    int ndx;
    int size = n;
    
    for (ndx = 0; ndx < n; ndx++) {
        sorted[ndx] = arr[0];
        arr[0] = arr[size - 1];
        size--;
        downHeapifyMin(arr, size, 0);
    }
    
    for (ndx = 0; ndx < n; ndx++) {
        arr[ndx] = sorted[ndx];
    }
}

void display(int arr[], int n) {
    int ndx;
    for (ndx = 0; ndx < n; ndx++) {
        printf("%d ", arr[ndx]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original: ");
    display(arr, n);

    heapSortMinAscending(arr, n);

    printf("Sorted (ascending): ");
    display(arr, n);

    return 0;
}
