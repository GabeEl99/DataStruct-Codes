#include <stdio.h>
#include <stdbool.h>

void initialize(unsigned char *set){
    *set = 0;
}

void insert(unsigned char *set, int element){
    if(element < 0 || element > 7){
        return;
    }
    unsigned char mask = 1 << element;
    *set |= mask;
}

void delete(unsigned char *set, int element){
    if(element < 0 || element > 7){
        return;
    }
    unsigned char mask = 1 << element;
    mask = ~mask;
    *set &= mask;
}

bool find(unsigned char set, int element){
    if(element < 0 || element > 7){
        return false;
    }
    unsigned char mask = 1 << element;
    return (set & mask) != 0;
}

unsigned char set_union(unsigned char A, unsigned char B){
    return A | B;
}

unsigned char set_intersection(unsigned char A, unsigned char B){
    return A & B;
}

unsigned char set_difference(unsigned char A, unsigned char B){
    return A & (~B);
}

void display(unsigned char set){
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
    unsigned char A, B, C;

    initialize(&A);
    initialize(&B);

    insert(&A, 1);
    insert(&A, 6);
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 7);

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

    delete(&A, 6);
    printf("A after delete 6 = ");
    display(A);

    return 0;
}
