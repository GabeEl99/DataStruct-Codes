#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 7

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int size;
} HashTable;

int hashFunction(int key, int size) {
    return key % size;
}

HashTable *createHashTable(int size) {
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (Node **)calloc(size, sizeof(Node *));
    return table;
}

void insert(HashTable *table, int key, int value) {
    int idx = hashFunction(key, table->size);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if (table->buckets[idx] == NULL) {
        table->buckets[idx] = newNode;
    } else {
        Node *temp = table->buckets[idx];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int search(HashTable *table, int key) {
    int idx = hashFunction(key, table->size);
    Node *temp = table->buckets[idx];

    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

int delete(HashTable *table, int key) {
    int idx = hashFunction(key, table->size);
    Node *temp = table->buckets[idx];
    Node *prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL) {
                table->buckets[idx] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

void display(HashTable *table) {
    int ndx;
    for (ndx = 0; ndx < table->size; ndx++) {
        printf("Bucket %d: ", ndx);
        Node *temp = table->buckets[ndx];
        while (temp != NULL) {
            printf("(%d, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freeHashTable(HashTable *table) {
    int ndx;
    for (ndx = 0; ndx < table->size; ndx++) {
        Node *temp = table->buckets[ndx];
        while (temp != NULL) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(table->buckets);
    free(table);
}

int main() {
    HashTable *table = createHashTable(HASH_SIZE);

    insert(table, 12, 100);
    insert(table, 25, 200);
    insert(table, 37, 300);
    insert(table, 19, 150);
    insert(table, 26, 250);
    insert(table, 5, 50);

    display(table);

    printf("Search 25: %d\n", search(table, 25));
    printf("Search 37: %d\n", search(table, 37));
    printf("Search 99: %d\n", search(table, 99));

    delete(table, 25);
    printf("\nAfter delete 25:\n");
    display(table);

    freeHashTable(table);
    return 0;
}
