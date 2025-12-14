#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

Stack* initialize();
bool isFull(Stack *s);
bool isEmpty(Stack *s);
bool push(Stack *s, int value);
int pop(Stack *s, bool *ok);
int peek(Stack *s, bool *ok);
int top(Stack *s, bool *ok);
void display(Stack *s);

Stack* initialize(){
    Stack *s = (Stack*)malloc(sizeof(Stack));
    if(s == NULL){
        return NULL;
    }
    s->top = MAX;
    return s;
}

bool isFull(Stack *s){
    return s->top == 0;
}

bool isEmpty(Stack *s){
    return s->top == MAX;
}

bool push(Stack *s, int value){
    if(isFull(s)){
        return false;
    }
    s->top--;
    s->items[s->top] = value;
    return true;
}

int pop(Stack *s, bool *ok){
    if(isEmpty(s)){
        if(ok) *ok = false;
        return -1;
    }
    if(ok) *ok = true;
    int value = s->items[s->top];
    s->top++;
    return value;
}

int peek(Stack *s, bool *ok){
    if(isEmpty(s)){
        if(ok) *ok = false;
        return -1;
    }
    if(ok) *ok = true;
    return s->items[s->top];
}

int top(Stack *s, bool *ok){
    return peek(s, ok);
}

void display(Stack *s){
    if(isEmpty(s)){
        printf("Stack is empty\n");
        return;
    }

    int ndx;
    for(ndx = s->top; ndx < MAX; ndx++){
        printf("%d ", s->items[ndx]);
    }
    printf("\n");
}

int main(){
    Stack *S = initialize();
    bool ok;

    push(S, 1);
    push(S, 3);
    push(S, 2);
    push(S, 5);
    display(S);

    push(S, 4);
    display(S);

    int value = pop(S, &ok);
    if(ok){
        printf("popped: %d\n", value);
    }
    display(S);

    int t = top(S, &ok);
    if(ok){
        printf("top: %d\n", t);
    }

    int p = peek(S, &ok);
    if(ok){
        printf("peek: %d\n", p);
    }

    free(S);
    return 0;
}
