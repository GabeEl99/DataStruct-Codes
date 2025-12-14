#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int field : 8;
} Set;

void initialize(Set *set){
    set->field = 0;
}

void insert(Set *set, int element){
    if(element < 0 || element > 7){
        return;
    }
    unsigned int mask = 1u << element;
    set->field |= mask;
}

void delete(Set *set, int element){
    if(element < 0 || element > 7){
        return;
    }
    unsigned int mask = 1u << element;
    mask = ~mask;
    set->field &= mask;
}

bool find(Set set, int element){
    if(element < 0 || element > 7){
        return false;
    }
    unsigned int mask = 1u << element;
    return (set.field & mask) != 0;
}

Set set_union(Set A, Set B){
    Set C;
    C.field = A.field | B.field;
    return C;
}

Set set_intersection(Set A, Set B){
    Set C;
    C.field = A.field & B.field;
    return C;
}

Set set_difference(Set A, Set B){
    Set C;
    C.field = A.field & (~B.field);
    return C;
}

void display(Set set){
    int first = 1;
    int ndx;
    printf("{");
    for(ndx = 0; ndx < 8; ndx++){
        if(find(set, ndx)){
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

    initialize(&A);
    initialize(&B);

    insert(&A, 0);
    insert(&A, 4);
    insert(&A, 5);

    insert(&B, 2);
    insert(&B, 5);

    printf("A = ");
    display(A);
    printf("B = ");
    display(B);

    C = set_union(A, B);
    printf("A union B = ");
    display(C);

    C = set_intersection(A, B);
    printf("A intersection B = ");
    display(C);

    C = set_difference(A, B);
    printf("A difference B = ");
    display(C);

    delete(&A, 5);
    delete(&A, 4);
    printf("A after deletions = ");
    display(A);

    return 0;
}
