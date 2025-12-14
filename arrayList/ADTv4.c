#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

void initialize(List *L);
void display(List *L);
void resize(List *L);
void insertPos(List *L, int data, int position);
void deletePos(List *L, int position);
int  locate(List *L, int data);
int  retrieve(List *L, int position);
void insertSorted(List *L, int data);
void makeNULL(List *L);

void initialize(List *L) {
    L->elemPtr = (int *)malloc(LENGTH * sizeof(int));
    if (L->elemPtr == NULL) {
        printf("Memory allocation failed.\n");
        L->max = 0;
        L->count = 0;
        return;
    }
    L->max = LENGTH;
    L->count = 0;
}

void display(List *L) {
    int ndx;
    printf("elem: [ ");
    for (ndx = 0; ndx < L->count; ndx++) {
        printf("%d ", L->elemPtr[ndx]);
    }
    printf("]\n");
    printf("count: %d\n", L->count);
    printf("max: %d\n", L->max);
}

void resize(List *L) {
    int newMax = (L->max == 0) ? LENGTH : L->max * 2;
    int *newArr = (int *)realloc(L->elemPtr, newMax * sizeof(int));
    if (newArr == NULL) {
        printf("Reallocation failed.\n");
        return;
    }
    L->elemPtr = newArr;
    L->max = newMax;
}

void insertPos(List *L, int data, int position) {
    int ndx;

    if (position < 0 || position > L->count) {
        printf("Invalid position %d\n", position);
        return;
    }

    if (L->count == L->max) {
        resize(L);
    }

    for (ndx = L->count; ndx > position; ndx--) {
        L->elemPtr[ndx] = L->elemPtr[ndx - 1];
    }

    L->elemPtr[position] = data;
    L->count++;
}

void deletePos(List *L, int position) {
    int ndx;

    if (position < 0 || position >= L->count) {
        printf("Invalid position %d\n", position);
        return;
    }

    for (ndx = position; ndx < L->count - 1; ndx++) {
        L->elemPtr[ndx] = L->elemPtr[ndx + 1];
    }

    L->count--;
}

int locate(List *L, int data) {
    int ndx;
    for (ndx = 0; ndx < L->count; ndx++) {
        if (L->elemPtr[ndx] == data) {
            return ndx;
        }
    }
    return -1;
}

int retrieve(List *L, int position) {
    if (position < 0 || position >= L->count) {
        printf("Invalid position %d\n", position);
        return -1;
    }
    return L->elemPtr[position];
}

void insertSorted(List *L, int data) {
    int pos = 0;

    if (L->count == L->max) {
        resize(L);
    }

    while (pos < L->count && L->elemPtr[pos] < data) {
        pos++;
    }

    insertPos(L, data, pos);
}

void makeNULL(List *L) {
    free(L->elemPtr);
    L->elemPtr = NULL;
    L->count = 0;
    L->max = 0;
}

int main(void) {
    List L;
    initialize(&L);

    insertPos(&L, 1, 0);
    insertPos(&L, 3, 1);
    insertPos(&L, 2, 1);
    insertPos(&L, 5, 3);
    display(&L);

    deletePos(&L, 1);
    display(&L);

    printf("locate 5: %d\n", locate(&L, 5));
    printf("locate 8: %d\n", locate(&L, 8));

    printf("retrieve position 1: %d\n", retrieve(&L, 1));

    insertSorted(&L, 4);
    insertSorted(&L, 10);
    insertSorted(&L, 8);
    display(&L);

    for (int ndx = 0; ndx < 20; ndx++) {
        insertPos(&L, ndx + 100, L.count);
    }
    display(&L);

    makeNULL(&L);

    return 0;
}
