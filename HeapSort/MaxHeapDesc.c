#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
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

void buildMaxHeap(int arr[], int n) {
    int ndx;
    for (ndx = n / 2 - 1; ndx >= 0; ndx--) {
        downHeapifyMax(arr, n, ndx);
    }
}

void heapSortMaxDescending(int arr[], int n) {
    buildMaxHeap(arr, n);
    
    int sorted[100];
    int ndx;
    int size = n;
    
    for (ndx = 0; ndx < n; ndx++) {
        sorted[ndx] = arr[0];
        arr[0] = arr[size - 1];
        size--;
        downHeapifyMax(arr, size, 0);
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

    heapSortMaxDescending(arr, n);

    printf("Sorted (descending): ");
    display(arr, n);

    return 0;
}
