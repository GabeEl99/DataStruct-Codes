#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef struct {
    int elem;
    int next;
} Cell;

typedef struct {
    Cell HeapSpace[MAX];
    int avail;
} VHeap;

typedef int List;

void initialize(VHeap *V){
    int ndx;
    V->avail = 0;
    for(ndx = 0; ndx < MAX - 1; ndx++){
        V->HeapSpace[ndx].next = ndx + 1;
    }
    V->HeapSpace[MAX - 1].next = -1;
}

int allocSpace(VHeap *V){
    int index = V->avail;
    if(index != -1){
        V->avail = V->HeapSpace[index].next;
    }
    return index;
}

void deallocSpace(VHeap *V, int index){
    V->HeapSpace[index].next = V->avail;
    V->avail = index;
}

void insertFirst(List *L, VHeap *V, int elem){
    int idx = allocSpace(V);
    if(idx == -1){
        return;
    }
    V->HeapSpace[idx].elem = elem;
    V->HeapSpace[idx].next = *L;
    *L = idx;
}

void insertLast(List *L, VHeap *V, int elem){
    int idx = allocSpace(V);
    if(idx == -1){
        return;
    }
    V->HeapSpace[idx].elem = elem;
    V->HeapSpace[idx].next = -1;

    if(*L == -1){
        *L = idx;
    }else{
        int curr = *L;
        while(V->HeapSpace[curr].next != -1){
            curr = V->HeapSpace[curr].next;
        }
        V->HeapSpace[curr].next = idx;
    }
}

void insertPos(List *L, VHeap *V, int elem, int pos){
    int idx = allocSpace(V);
    if(idx == -1){
        return;
    }
    V->HeapSpace[idx].elem = elem;

    if(pos == 0 || *L == -1){
        V->HeapSpace[idx].next = *L;
        *L = idx;
        return;
    }

    int curr = *L;
    int ndx;
    for(ndx = 0; ndx < pos - 1 && V->HeapSpace[curr].next != -1; ndx++){
        curr = V->HeapSpace[curr].next;
    }

    V->HeapSpace[idx].next = V->HeapSpace[curr].next;
    V->HeapSpace[curr].next = idx;
}

void insertSorted(List *L, VHeap *V, int elem){
    int idx = allocSpace(V);
    if(idx == -1){
        return;
    }
    V->HeapSpace[idx].elem = elem;

    if(*L == -1 || V->HeapSpace[*L].elem >= elem){
        V->HeapSpace[idx].next = *L;
        *L = idx;
        return;
    }

    int curr = *L;
    while(V->HeapSpace[curr].next != -1 &&
          V->HeapSpace[V->HeapSpace[curr].next].elem < elem){
        curr = V->HeapSpace[curr].next;
    }

    V->HeapSpace[idx].next = V->HeapSpace[curr].next;
    V->HeapSpace[curr].next = idx;
}

void deleteElem(List *L, VHeap *V, int elem){
    int curr = *L;
    int prev = -1;

    while(curr != -1 && V->HeapSpace[curr].elem != elem){
        prev = curr;
        curr = V->HeapSpace[curr].next;
    }

    if(curr == -1){
        return;
    }

    if(prev == -1){
        *L = V->HeapSpace[curr].next;
    }else{
        V->HeapSpace[prev].next = V->HeapSpace[curr].next;
    }

    deallocSpace(V, curr);
}

void deleteAllOccurrence(List *L, VHeap *V, int elem){
    int curr = *L;
    int prev = -1;

    while(curr != -1){
        if(V->HeapSpace[curr].elem == elem){
            int toDelete = curr;
            if(prev == -1){
                *L = V->HeapSpace[curr].next;
                curr = *L;
            }else{
                V->HeapSpace[prev].next = V->HeapSpace[curr].next;
                curr = V->HeapSpace[prev].next;
            }
            deallocSpace(V, toDelete);
        }else{
            prev = curr;
            curr = V->HeapSpace[curr].next;
        }
    }
}

void display(int L, VHeap V){
    int curr = L;
    while(curr != -1){
        printf("%d ", V.HeapSpace[curr].elem);
        curr = V.HeapSpace[curr].next;
    }
    printf("\n");
}

int main(){
    VHeap V;
    List L = -1;

    initialize(&V);

    insertFirst(&L, &V, 3);
    insertFirst(&L, &V, 1);
    insertLast(&L, &V, 5);
    display(L, V);

    insertPos(&L, &V, 4, 2);
    display(L, V);

    insertSorted(&L, &V, 2);
    display(L, V);

    deleteElem(&L, &V, 4);
    display(L, V);

    deleteAllOccurrence(&L, &V, 3);
    display(L, V);

    return 0;
}
