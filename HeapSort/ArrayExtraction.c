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

void heapSortExtraction(int arr[], int n, int sorted[]) {
    int temp[100];
    int ndx;
    
    for (ndx = 0; ndx < n; ndx++) {
        temp[ndx] = arr[ndx];
    }
    
    buildMaxHeap(temp, n);
    
    int size = n;
    for (ndx = 0; ndx < n; ndx++) {
        sorted[ndx] = temp[0];
        temp[0] = temp[size - 1];
        size--;
        downHeapifyMax(temp, size, 0);
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
    int sorted[100];

    printf("Original: ");
    display(arr, n);

    heapSortExtraction(arr, n, sorted);

    printf("Sorted (descending): ");
    display(sorted, n);

    return 0;
}
