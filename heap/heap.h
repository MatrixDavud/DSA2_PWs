#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
 
// define the struct heap
typedef struct heap heap;
 
/**
 * @brief Return the current heap size (number of elements)
 */
size_t heap_size(heap *h);

/**
 * @brief correct a max-heap violation in subtree rooted in index.
 */
void max_heapify(heap* h, const int index);

/**
 * @brief build a max-heap from an array
 */
heap* heap_build_max_heap(size_t capacity, int *arr);

/**
 * @brief return the node with the maximum key and remove it 
 * from the heap while maintaining the max-heap property.
 * 
 * @param h a non-empty heap.
 * @return int the returned node.
 */
int heap_extract_max(heap *h);

/**
 * @brief increase the key of a node identified by its index.
 * 
 * @param h an array representing a heap.
 * @param i  an array index.
 * @param key a new key greater than h[i].
 * @param return h still representing a heap where the key of h[i] 
 * @pre key > h[i]
 * was increased to key.
 * Running Time: O(log n) where n is the heap size.
 */
void heap_increase_key(heap *h, int i, int key);

/**
 * @brief insert into a max-heap
 *
 * @param h the heap to insert an element into
 * @param key the value of the key to insert
 * Running Time: O(log n) where n is the heap size.
 */
void heap_insert(heap* h, int key);

/**
 * @brief return the max value from heap, leave heap unchanged.
 */
int heap_find_max(heap *h);

int heap_get_key(heap* h, int index);

/**
 * @brief Sort an array using heap sort.
 * 
 * @param len the number of elements in array @a arr
 * @param arr an array (possibily unordered) 
 * @return a sorted array
 */
int* heap_sort(size_t len, int* arr);

void heap_free(heap* h);

void heap_print(heap* h);
