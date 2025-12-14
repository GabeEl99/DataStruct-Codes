#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} Etype, *EPtr;

void initialize(EPtr L);
void insertPos(EPtr L, int data, int position);
void deletePos(EPtr L, int position);
void insertSorted(EPtr L, int data);
void display(EPtr L);
void makeNULL(EPtr L);
int locate(EPtr L, int data);
int retrieve(EPtr L, int position);


void initialize(EPtr L) {
    L->count = 0;
    printf("[INITIALIZE] List initialized with count = 0\n");
}


void insertPos(EPtr L, int data, int position) {
    
    if (position < 0 || position > L->count) {
        printf("[ERROR] Invalid position: %d (count: %d)\n", position, L->count);
        return;
    }
    
    
    if (L->count >= MAX) {
        printf("[ERROR] Array is full! Cannot insert.\n");
        return;
    }
    
   
    for (int i = L->count; i > position; i--) {
        L->elem[i] = L->elem[i - 1];
    }
    
    L->elem[position] = data;
    
    L->count++;
    printf("[INSERT POS] Inserted %d at position %d (new count: %d)\n", data, position, L->count);
}


void deletePos(EPtr L, int position) {
    
    if (position < 0 || position >= L->count) {
        printf("[ERROR] Invalid position: %d (count: %d)\n", position, L->count);
        return;
    }
    
    int deleted = L->elem[position];
    
   
    for (int i = position; i < L->count - 1; i++) {
        L->elem[i] = L->elem[i + 1];
    }
    
   
    L->count--;
    printf("[DELETE POS] Deleted %d from position %d (new count: %d)\n", deleted, position, L->count);
}


void insertSorted(EPtr L, int data) {
 
    if (L->count >= MAX) {
        printf("[ERROR] Array is full! Cannot insert.\n");
        return;
    }
    
   
    int position = 0;
    while (position < L->count && L->elem[position] < data) {
        position++;
    }
    
   
    for (int i = L->count; i > position; i--) {
        L->elem[i] = L->elem[i - 1];
    }
    
 
    L->elem[position] = data;
    L->count++;
    printf("[INSERT SORTED] Inserted %d at position %d (new count: %d)\n", data, position, L->count);
}


void display(EPtr L) {
    printf("[DISPLAY] elem: [ ");
    for (int i = 0; i < L->count; i++) {
        printf("%d ", L->elem[i]);
        if (i < L->count - 1) printf(", ");
    }
    printf("]\n");
    printf("          count: %d\n", L->count);
}


void makeNULL(EPtr L) {
    L->count = 0;
    printf("[MAKE NULL] List cleared (count: %d)\n", L->count);
}


int locate(EPtr L, int data) {
    for (int i = 0; i < L->count; i++) {
        if (L->elem[i] == data) {
            printf("[LOCATE] Found %d at position %d\n", data, i);
            return i;
        }
    }
    printf("[LOCATE] %d not found (return -1)\n", data);
    return -1;
}


int retrieve(EPtr L, int position) {
    if (position < 0 || position >= L->count) {
        printf("[ERROR] Invalid position: %d (count: %d)\n", position, L->count);
        return -1;
    }
    printf("[RETRIEVE] Retrieved %d from position %d\n", L->elem[position], position);
    return L->elem[position];
}


int main() {
    Etype myList;
    EPtr L = &myList;
    
    printf("=== DYNAMIC LIST OPERATIONS (Static Array - Variation 2) ===\n\n");
    

    initialize(L);
    display(L);
    printf("\n");
    

    printf("--- Testing insertPos() ---\n");
    insertPos(L, 1, 0);
    display(L);
    insertPos(L, 3, 1);
    display(L);
    insertPos(L, 5, 2);
    display(L);
    insertPos(L, 10, 3);
    display(L);
    printf("\n");
    
 
    printf("--- Testing insertSorted() ---\n");
    insertSorted(L, 8);
    display(L);
    printf("\n");
    
 
    printf("--- Testing locate() ---\n");
    locate(L, 5);
    locate(L, 8);
    locate(L, 100);
    printf("\n");
    

    printf("--- Testing retrieve() ---\n");
    retrieve(L, 0);
    retrieve(L, 4);
    retrieve(L, 10);
    printf("\n");
    
  
    printf("--- Testing deletePos() ---\n");
    deletePos(L, 1);
    display(L);
    deletePos(L, 0);
    display(L);
    printf("\n");
    

    printf("--- Testing makeNULL() ---\n");
    makeNULL(L);
    display(L);
    
    return 0;
}