#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct {
int elem[MAX];
int count;
}Etype, *EPtr;

EPtr L;

void initialize(EPtr L);
void insertPos(EPtr L, int data, int position);

void initialize(EPtr L){
L->count = 0;
}

void insertPos(EPtr L, int data, int position){
if (L->count == MAX) {
printf("Error: The List is full!\n");
}

if (position < 0 || position > L->count){
printf("Error: Position is Invalid.\n");
}

for (int ndx = L->count; ndx > position; ndx--){
L->elem[ndx] = L.elem[ndx - 1];
}
L->elem[position] = data;
L->count++;
}


//Position must be valid (less than or equal to count)
//The array must not be full (count should not be equal to max)
//Insert the element into the specified position
//Shift elements right to make space for the position if necessary
//Increment count



//Position must be valid (less than or equal to count)
//The array must not be full (count should not be equal to max)
//Insert the element into the specified position
//Shift elements right to make space for the position if necessary
//Increment count
//Return modified List