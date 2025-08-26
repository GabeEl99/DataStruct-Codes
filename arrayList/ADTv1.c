#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct{
    int elem[MAX];
    int count;
}List;

List L;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);


List initialize(List L){
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int position){
    if (L.count == MAX) {
        printf("Error: The List is Full!\n");
        return L;
    }

    if (position < 0 || position > L.count) {
        printf("Error: Position is Invalid.\n");
        return L;
    }

    for (int ndx = L.count; ndx > position; ndx--) {
        L.elem[ndx] = L.elem[ndx - 1];
    }
    L.elem[position] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position){
    if (L.count == 0) {
        printf("Error: List is Empty!\n");
        return L;
    }

    if (position < 0 || position >= L.count) {
        printf("Error: Position is Invalid!\n");
        return L;
    }

    for (int ndx = position; ndx < L.count - 1; ndx++) {
        L.elem[ndx] = L.elem[ndx + 1];
    }
    L.count--;
    return L;
}

int locate(List L, int data){
    int ndx;
    for(ndx=0; ndx<L.count && data != L.elem[ndx]; ndx++) {}

    return(ndx < L.count) ? ndx:-1;
}

List insertSorted(List L, int data){
    int ndx;

    if (L.count == MAX) {
        printf("Error: List is Full!\n");
        return L;
    }

    for (ndx = L.count - 1; ndx >= 0 && L.elem[ndx] > data; ndx--) {
        L.elem[ndx + 1] = L.elem[ndx];
    }
    L.elem[ndx + 1] = data;
    L.count++;
    return L;
}

void display(List L){
    int ndx;
    for(ndx = 0; ndx < L.count; ndx++){
        printf("%d", L.elem[ndx]);
    }
    printf("\n");
}

int main(){
    L = initialize(L);
    printf("Initialized List:\n");
    display(L);

    L = insertPos(L, 1, 0);  
    L = insertPos(L, 3, 1); 
    L = insertPos(L, 2, 1);  
    L = insertPos(L, 5, 3);  
    printf("After insertPos operations:\n");
    display(L);

    L = deletePos(L, 1);   
    printf("After deletePos at index 1:\n");
    display(L);

    int pos = locate(L, 5);
    printf("Locate 5: %d\n", pos);
    pos = locate(L, 7);
    printf("Locate 7: %d\n", pos);

    L = insertSorted(L, 4);  // [1,3,4,5]
    L = insertSorted(L, 8);  // [1,3,4,5,8]
    printf("After insertSorted operations:\n");
    display(L);

    return 0;
}



