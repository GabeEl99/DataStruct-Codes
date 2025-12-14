#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

List* initialize();
void empty(List *list);
void insertFirst(List *list, int data);
void insertLast(List *list, int data);
void insertPos(List *list, int data, int index);
void deleteStart(List *list);
void deleteLast(List *list);
void deletePos(List *list, int index);
int  retrieve(List *list, int index);
int  locate(List *list, int data);
void display(List *list);

List* initialize(){
    List *newList = (List*)malloc(sizeof(List));
    if(newList == NULL){
        return NULL;
    }
    newList->head = NULL;
    newList->count = 0;
    return newList;
}

void empty(List *list){
    if(list == NULL){
        return;
    }

    Node *current = list->head;
    Node *nextNode;

    while(current != NULL){
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data){
    if(list == NULL){
        return;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        return;
    }

    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

void insertLast(List *list, int data){
    if(list == NULL){
        return;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if(list->head == NULL){
        list->head = newNode;
    }else{
        Node *current = list->head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }

    list->count++;
}

void insertPos(List *list, int data, int index){
    if(list == NULL){
        return;
    }

    if(index < 0 || index > list->count){
        return;
    }

    if(index == 0){
        insertFirst(list, data);
    }else if(index == list->count){
        insertLast(list, data);
    }else{
        Node *newNode = (Node*)malloc(sizeof(Node));
        if(newNode == NULL){
            return;
        }

        newNode->data = data;

        Node *current = list->head;
        int ndx;
        for(ndx = 0; ndx < index - 1; ndx++){
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        list->count++;
    }
}

void deleteStart(List *list){
    if(list == NULL || list->head == NULL){
        return;
    }

    Node *current = list->head;
    list->head = current->next;
    free(current);
    list->count--;
}

void deleteLast(List *list){
    if(list == NULL || list->head == NULL){
        return;
    }

    if(list->head->next == NULL){
        free(list->head);
        list->head = NULL;
        list->count--;
        return;
    }

    Node *current = list->head;
    int ndx;
    for(ndx = 0; ndx < list->count - 2; ndx++){
        current = current->next;
    }

    Node *last = current->next;
    current->next = NULL;
    free(last);
    list->count--;
}

void deletePos(List *list, int index){
    if(list == NULL || list->head == NULL){
        return;
    }

    if(index < 0 || index >= list->count){
        return;
    }

    if(index == 0){
        deleteStart(list);
    }else{
        Node *current = list->head;
        int ndx;
        for(ndx = 0; ndx < index - 1; ndx++){
            current = current->next;
        }

        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
        list->count--;
    }
}

int retrieve(List *list, int index){
    if(list == NULL || index < 0 || index >= list->count){
        return -1;
    }

    Node *current = list->head;
    int ndx;
    for(ndx = 0; ndx < index; ndx++){
        current = current->next;
    }

    return current->data;
}

int locate(List *list, int data){
    if(list == NULL || list->head == NULL){
        return -1;
    }

    Node *current = list->head;
    int index = 0;

    while(current != NULL){
        if(current->data == data){
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

void display(List *list){
    if(list == NULL){
        return;
    }

    Node *current = list->head;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(){
    List *L = initialize();

    insertFirst(L, 5);
    insertFirst(L, 6);
    insertFirst(L, 2);
    insertLast(L, 7);
    display(L);

    insertPos(L, 7, 2);
    display(L);

    deleteStart(L);
    display(L);

    deleteLast(L);
    display(L);

    deletePos(L, 1);
    display(L);

    printf("retrieve index 0: %d\n", retrieve(L, 0));
    printf("locate value 5: %d\n", locate(L, 5));

    empty(L);
    free(L);

    return 0;
}
