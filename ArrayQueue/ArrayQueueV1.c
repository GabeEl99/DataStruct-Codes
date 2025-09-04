#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct {
    int items[MAX];
    int count;
}List;


typedef struct {
    List list;
    int front;
    int rear;

}Queue; 

Queue Q;

