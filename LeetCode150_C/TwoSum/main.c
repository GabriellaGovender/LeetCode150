#include <stdio.h>
#include <stdlib.h>

/*
    TWO SUM
    Given an array of integers, return indices of two numbers
    such that they add up to a target. \
    Assume only one ansewr exists.

*/

/*
    INPUT
        array of integers: N
        target: T

    OUTPUT
        indices: [x, y]
        where: N[x] + N[y] = T

*/

#include <stdio.h>
#include <stdlib.h>

#define HASH_MAP_SIZE 100

// Structure for a hashmap entry
typedef struct HashMapEntry {
    int key;
    int value;
    struct HashMapEntry* next;
} HashMapEntry;

// Structure for the hashmap
typedef struct {
    HashMapEntry** buckets;
} HashMap;

// Hash function
unsigned int hash(int key) {
    return key % HASH_MAP_SIZE;
}

// Create a new hashmap
HashMap* createHashMap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->buckets = (HashMapEntry**)malloc(sizeof(HashMapEntry*) * HASH_MAP_SIZE);
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        map->buckets[i] = NULL;
    }
    return map;
}

// Create a new entry
HashMapEntry* createEntry(int key, int value) {
    HashMapEntry* entry = (HashMapEntry*)malloc(sizeof(HashMapEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

// Insert a key-value pair into the hashmap
void insert(HashMap* map, int key, int value) {
    unsigned int index = hash(key);
    HashMapEntry* newEntry = createEntry(key, value);

    if (map->buckets[index] == NULL) {
        map->buckets[index] = newEntry;
    } else {
        HashMapEntry* current = map->buckets[index];
        while (current->next != NULL && current->key != key) {
            current = current->next;
        }
        if (current->key == key) {
            current->value = value;
            free(newEntry);
        } else {
            current->next = newEntry;
        }
    }
}

// Retrieve a value by key from the hashmap
int get(HashMap* map, int key) {
    unsigned int index = hash(key);
    HashMapEntry* current = map->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Return -1 if key not found
}

// Delete a key-value pair from the hashmap
void delete(HashMap* map, int key) {
    unsigned int index = hash(key);
    HashMapEntry* current = map->buckets[index];
    HashMapEntry* prev = NULL;

    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        // Key not found
        return;
    }

    if (prev == NULL) {
        // Remove the first entry in the bucket
        map->buckets[index] = current->next;
    } else {
        // Remove the entry from the linked list
        prev->next = current->next;
    }

    free(current);
}

// Check if a value is in the hashmap
int containsValue(HashMap* map, int value) {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashMapEntry* current = map->buckets[i];
        while (current != NULL) {
            if (current->value == value) {
                return 1; // Return 1 if value is found
            }
            current = current->next;
        }
    }
    return 0; // Return 0 if value is not found
}

// Find the key for a given value
int findKeyOfValue(HashMap* map, int value) {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashMapEntry* current = map->buckets[i];
        while (current != NULL) {
            if (current->value == value) {
                return current->key; // Return the key if value is found
            }
            current = current->next;
        }
    }
    return -1; // Return -1 if value is not found
}

// Free the entire hashmap
void freeHashMap(HashMap* map) {
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashMapEntry* current = map->buckets[i];
        while (current != NULL) {
            HashMapEntry* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

/*
// Main function to demonstrate the usage
int main() {
    HashMap* map = createHashMap();

    insert(map, 1, 42);
    insert(map, 2, 84);
    insert(map, 3, 126);

    printf("Value for key 1: %d\n", get(map, 1));
    printf("Value for key 2: %d\n", get(map, 2));
    printf("Value for key 3: %d\n", get(map, 3));

    delete(map, 2);
    printf("Value for key 2 after deletion: %d\n", get(map, 2));

    freeHashMap(map);
    return 0;
}
*/

//BRUTE FORCE: linear search
int* bruteForceTwoSum(int N[], int T, int sizeN)
{
    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < sizeN; i++){
        for (int j = i + 1; j < sizeN; j++){
            if (N[i] + N[j] == T){
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }

    result[0] = -1;
    result[1] = -1;
    return result;
}
// Time Complexity = O(N^2)
// Memory Complexity = O(1)

// Use Hashmap
int* hashmapTwoSum(int N[], int T, int sizeN)
{
    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    HashMap* map = createHashMap();

    for (int i = 0; i < sizeN; i++){
        int x = T - N[i];
        if (containsValue(map, x) == 1) {
            result[1] = i;
            result[0] = findKeyOfValue(map, x);
            return result;
        }
        insert(map, i, N[i]);
    }
    result[0] = -1;
    result[1] = -1;
    return result;
}
// Time Complexity = O(n)
// Memory Complexity = O(n)

int main()
{
    int N[] = {2, 1, 5, 3};
    int T = 4;
    int size = sizeof(N)/sizeof(N[0]);
    int* answer = hashmapTwoSum(N, T, size);
    printf("[ %d, %d]\n", answer[0], answer[1]);
    return 0;
}
