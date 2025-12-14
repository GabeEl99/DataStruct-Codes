#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack* initialize();
bool isFull(Stack *s);
bool isEmpty(Stack *s);
bool push(Stack *s, int value);
int pop(Stack *s, bool *ok);
int peek(Stack *s, bool *ok);
void display(Stack *s);

Stack* initialize(){
    Stack *s = (Stack*)malloc(sizeof(Stack));
    if(s == NULL){
        return NULL;
    }
    s->top = NULL;
    return s;
}

bool isFull(Stack *s){
    return false;
}

bool isEmpty(Stack *s){
    return s->top == NULL;
}

bool push(Stack *s, int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        return false;
    }

    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    return true;
}

int pop(Stack *s, bool *ok){
    if(isEmpty(s)){
        if(ok) *ok = false;
        return -1;
    }

    Node *temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);

    if(ok) *ok = true;
    return value;
}

int peek(Stack *s, bool *ok){
    if(isEmpty(s)){
        if(ok) *ok = false;
        return -1;
    }
    if(ok) *ok = true;
    return s->top->data;
}

void display(Stack *s){
    if(isEmpty(s)){
        printf("Stack is empty\n");
        return;
    }

    Node *current = s->top;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(){
    Stack *S = initialize();
    bool ok;

    push(S, 1);
    push(S, 3);
    push(S, 5);
    push(S, 7);
    display(S);

    push(S, 4);
    display(S);

    int value = pop(S, &ok);
    if(ok){
        printf("popped: %d\n", value);
    }
    display(S);

    int t = peek(S, &ok);
    if(ok){
        printf("top: %d\n", t);
    }

    while(!isEmpty(S)){
        pop(S, &ok);
    }
    display(S);

    free(S);
    return 0;
}
