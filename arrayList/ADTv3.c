#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

List initialize(List L);
void display(List L);
List resize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int  locate(List L, int data);
List insertSorted(List L, int data);

List initialize(List L) {
    L.elemPtr = (int *)malloc(LENGTH * sizeof(int));
    if (L.elemPtr == NULL) {
        printf("Memory allocation failed.\n");
        L.max = 0;
        L.count = 0;
        return L;
    }
    L.max = LENGTH;
    L.count = 0;
    return L;
}

void display(List L) {
    int i;
    printf("List: [ ");
    for (i = 0; i < L.count; i++) {
        printf("%d ", L.elemPtr[i]);
    }
    printf("]\n");
    printf("count: %d\n", L.count);
    printf("max: %d\n", L.max);
}

List resize(List L) {
    int newMax = (L.max == 0) ? LENGTH : L.max * 2;
    int *newArr = (int *)realloc(L.elemPtr, newMax * sizeof(int));
    if (newArr == NULL) {
        printf("Reallocation failed.\n");
        return L;
    }
    L.elemPtr = newArr;
    L.max = newMax;
    return L;
}

List insertPos(List L, int data, int position) {
    int i;

    if (position < 0 || position > L.count) {
        printf("Invalid position %d\n", position);
        return L;
    }

    if (L.count == L.max) {
        L = resize(L);
    }

    for (i = L.count; i > position; i--) {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }

    L.elemPtr[position] = data;
    L.count++;

    return L;
}

List deletePos(List L, int position) {
    int i;

    if (position < 0 || position >= L.count) {
        printf("Invalid position %d\n", position);
        return L;
    }

    for (i = position; i < L.count - 1; i++) {
        L.elemPtr[i] = L.elemPtr[i + 1];
    }

    L.count--;
    return L;
}

int locate(List L, int data) {
    int i;
    for (i = 0; i < L.count; i++) {
        if (L.elemPtr[i] == data) {
            return i;
        }
    }
    return -1;
}

List insertSorted(List L, int data) {
    int pos = 0;

    if (L.count == L.max) {
        L = resize(L);
    }

    while (pos < L.count && L.elemPtr[pos] < data) {
        pos++;
    }

    L = insertPos(L, data, pos);
    return L;
}

int main(void) {
    List L = {NULL, 0, 0};

    L = initialize(L);

    L = insertPos(L, 1, 0);
    L = insertPos(L, 3, 1);
    L = insertPos(L, 2, 1);
    L = insertPos(L, 5, 3);
    display(L);

    L = deletePos(L, 1);
    display(L);

    printf("locate 5: %d\n", locate(L, 5));
    printf("locate 8: %d\n", locate(L, 8));

    L = insertSorted(L, 4);
    L = insertSorted(L, 10);
    display(L);

    for (int i = 0; i < 20; i++) {
        L = insertPos(L, i + 100, L.count);
    }
    display(L);

    free(L.elemPtr);

    return 0;
}
