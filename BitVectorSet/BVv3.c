#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 8

typedef bool Set[ARRAY_SIZE];

void initialize(Set set){
    int ndx;
    for(ndx = 0; ndx < ARRAY_SIZE; ndx++){
        set[ndx] = false;
    }
}

void insert(Set set, int element){
    if(element < 0 || element >= ARRAY_SIZE){
        return;
    }
    set[element] = true;
}

void delete(Set set, int element){
    if(element < 0 || element >= ARRAY_SIZE){
        return;
    }
    set[element] = false;
}

bool find(Set set, int element){
    if(element < 0 || element >= ARRAY_SIZE){
        return false;
    }
    return set[element];
}

void union_set(Set A, Set B, Set C){
    int ndx;
    for(ndx = 0; ndx < ARRAY_SIZE; ndx++){
        C[ndx] = A[ndx] || B[ndx];
    }
}

void intersection_set(Set A, Set B, Set C){
    int ndx;
    for(ndx = 0; ndx < ARRAY_SIZE; ndx++){
        C[ndx] = A[ndx] && B[ndx];
    }
}

void difference_set(Set A, Set B, Set C){
    int ndx;
    for(ndx = 0; ndx < ARRAY_SIZE; ndx++){
        C[ndx] = A[ndx] && !B[ndx];
    }
}

void display(Set set){
    int first = 1;
    int ndx;
    printf("{");
    for(ndx = 0; ndx < ARRAY_SIZE; ndx++){
        if(set[ndx]){
            if(!first){
                printf(", ");
            }
            printf("%d", ndx);
            first = 0;
        }
    }
    printf("}\n");
}

int main(){
    Set A, B, C;

    initialize(A);
    initialize(B);

    insert(A, 0);
    insert(A, 2);
    insert(A, 7);

    insert(B, 2);
    insert(B, 4);
    insert(B, 5);

    printf("A = ");
    display(A);
    printf("B = ");
    display(B);

    union_set(A, B, C);
    printf("A union B = ");
    display(C);

    intersection_set(A, B, C);
    printf("A intersection B = ");
    display(C);

    difference_set(A, B, C);
    printf("A difference B = ");
    display(C);

    delete(A, 0);
    delete(A, 7);
    printf("A after deletions = ");
    display(A);

    return 0;
}
