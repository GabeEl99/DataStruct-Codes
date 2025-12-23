#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10
#define EMPTY -1
#define DELETED -2

typedef struct {
    int key;
    int value;
    int status;
} Entry;

typedef struct {
    Entry *table;
    int size;
} HashTable;

int hashFunction(int key, int size) {
    return key % size;
}

HashTable *createHashTable(int size) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (Entry *)malloc(size * sizeof(Entry));
    int ndx;
    for (ndx = 0; ndx < size; ndx++) {
        ht->table[ndx].key = EMPTY;
        ht->table[ndx].value = -1;
        ht->table[ndx].status = EMPTY;
    }
    return ht;
}

int insert(HashTable *ht, int key, int value) {
    int idx = hashFunction(key, ht->size);
    int ndx = idx;

    while (ht->table[ndx].status != EMPTY) {
        if (ht->table[ndx].key == key && ht->table[ndx].status == 0) {
            ht->table[ndx].value = value;
            return 1;
        }
        ndx = (ndx + 1) % ht->size;
        if (ndx == idx) {
            return 0;
        }
    }

    ht->table[ndx].key = key;
    ht->table[ndx].value = value;
    ht->table[ndx].status = 0;
    return 1;
}

int search(HashTable *ht, int key) {
    int idx = hashFunction(key, ht->size);
    int ndx = idx;

    while (ht->table[ndx].status != EMPTY) {
        if (ht->table[ndx].key == key && ht->table[ndx].status == 0) {
            return ht->table[ndx].value;
        }
        ndx = (ndx + 1) % ht->size;
        if (ndx == idx) {
            break;
        }
    }
    return -1;
}

int delete(HashTable *ht, int key) {
    int idx = hashFunction(key, ht->size);
    int ndx = idx;

    while (ht->table[ndx].status != EMPTY) {
        if (ht->table[ndx].key == key && ht->table[ndx].status == 0) {
            ht->table[ndx].status = DELETED;
            return 1;
        }
        ndx = (ndx + 1) % ht->size;
        if (ndx == idx) {
            break;
        }
    }
    return 0;
}

void display(HashTable *ht) {
    int ndx;
    for (ndx = 0; ndx < ht->size; ndx++) {
        if (ht->table[ndx].status == 0) {
            printf("Index %d: Key=%d, Value=%d\n", ndx, ht->table[ndx].key, ht->table[ndx].value);
        } else if (ht->table[ndx].status == DELETED) {
            printf("Index %d: DELETED\n", ndx);
        } else {
            printf("Index %d: EMPTY\n", ndx);
        }
    }
}

void freeHashTable(HashTable *ht) {
    free(ht->table);
    free(ht);
}

int main() {
    HashTable *ht = createHashTable(HASH_SIZE);

    insert(ht, 12, 100);
    insert(ht, 25, 200);
    insert(ht, 37, 300);
    insert(ht, 19, 150);
    insert(ht, 26, 250);
    insert(ht, 5, 50);

    display(ht);

    printf("\nSearch 25: %d\n", search(ht, 25));
    printf("Search 37: %d\n", search(ht, 37));
    printf("Search 99: %d\n", search(ht, 99));

    delete(ht, 25);
    printf("\nAfter delete 25:\n");
    display(ht);

    freeHashTable(ht);
    return 0;
}
