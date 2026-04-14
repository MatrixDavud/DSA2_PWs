/**
 * A tree data structure implementation with nodes containing a key,value pair
 *
 **/ 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include "heap.h"

// Declare a heap structure
struct heap {
	int* arr;
	size_t size;    //< number of elements present in the heap.
	size_t capacity;//< how many elements can be stored in the heap.
};

// Macros for tree navigation
#define HEAP_PARENT(i) ((i - 1) / 2)
#define HEAP_LEFT(i) (2 * i + 1)
#define HEAP_RIGHT(i) (2 * i + 2)


/**
 * @brief swap elements at indices inx1 and inx2 in a heap h.
 */
void heap_swap_elements(heap *h, size_t inx1, size_t inx2) {
	assert(inx1 >=0 && inx1< h->size && inx2 >=0 && inx2 < h->size); 
    int tmp = h->arr[inx2];
	h->arr[inx2] = h->arr[inx1];
	h->arr[inx1] = tmp;
	
}

size_t heap_size(heap* h) { 
	if (0==h) return 0;
	return h->size;
}

/**
 * @brief correct a max-heap violation in subtree rooted in index
 */
void max_heapify(heap* h, const int index) {
    int largest = index;
    int left = HEAP_LEFT(index);
    int right = HEAP_RIGHT(index);
    
    // Find the largest among node, left child, and right child
    if (left < (int)h->size && h->arr[left] > h->arr[largest])
        largest = left;
    if (right < (int)h->size && h->arr[right] > h->arr[largest])
        largest = right;
    
    // If largest is not the node itself, swap and recurse
    if (largest != index) {
        heap_swap_elements(h, index, largest);
        max_heapify(h, largest);
    }
}

/**
 * @brief build a max-heap from an array
 * 
 * @param capacity the max number of elements
 * @param arr the array of elements
 * @return heap* the max-heap
 */
heap* heap_build_max_heap(size_t capacity, int * arr) {
	// Allocate memory for one struct heap.
	heap* h = malloc(sizeof(heap));

	if (0 == h) {
		perror("cannot allocate memory.");
		return 0;
	}
	// set the values to size and capacity
	h->size = capacity;
	h->capacity = capacity;
	// Allocate memory to store the array
	h->arr = (int*)malloc(capacity * sizeof(*arr));
	if (h->arr == 0) {
		perror("cannot allocate memory.");
		return 0;
	}
	
    // Copy array elements into heap
    for (size_t i = 0; i < capacity; i++) {
        h->arr[i] = arr[i];
    }
    
    // Build max-heap by heapifying non-leaf nodes in reverse order
    for (int i = (int)capacity / 2 - 1; i >= 0; i--) {
        max_heapify(h, i);
    }

	return h;
}

/**
 * @brief insert into a max-heap
 * 
 * @param h the heap to insert an element into
 * @param key the value to insert
 */
void heap_insert(heap* h, int key) {

    // heap_size is going to grow by 1, check if we need to realloc
    if (h->size+1 > h->capacity) {
       h->arr = realloc (h->arr, (h->size + 1) * sizeof (*(h->arr)));
       assert(h->arr);
    }
    h->size += 1;                  // we have a new free leaf
    h->arr[h->size-1] = INT_MIN;  // set it to -infinity, so that 
    heap_increase_key(h, h->size-1, key);  // we can set it to desired value
}


int heap_extract_max(heap* h) {
    int max = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    max_heapify(h, 0);
    return max;
}

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
void heap_increase_key(heap *h, int i, int key) {
	assert(key > h->arr[i]); // new key must be larger than current key
	h->arr[i]= key;
	while (i > 0 && h->arr[HEAP_PARENT(i)] < h->arr[i]) {
		heap_swap_elements(h, i,HEAP_PARENT(i)); 
		i = HEAP_PARENT(i);
	}
}


int heap_find_max(heap *h) {
	return h->arr[0];
}


int* heap_sort(size_t len, int* arr) {
	// 1. build a max-heap from the array
	heap* h = heap_build_max_heap(len, arr);
	int *res = malloc(h->size * sizeof(int)); // this is the result array
	size_t res_index = 0;
	while (h->size > 0) {
		// Notice: first element has the maximum value.
		// 2. Swap first and last elems :
		heap_swap_elements(h, 0, h->size - 1);
		//    Now max elem is at the end of the array
		// 3. Discard last elem from heap (by decrementing heap-size variable)
		//    (and we store this element into the result array.)
		res[res_index++] = h->arr[h->size - 1];
		h->size--;
		// 4. New  root may violate max heap property, but its children 
		// are max heaps. Run max_heapify to fix this.
		if (h->size > 0)
			max_heapify(h, 0);
	}
	heap_free(h); // we do not need the working heap anymore
	return res;
}

int heap_get_key(heap* h, int index) {
    assert(index < h->size);
    return h->arr[index];
}


void heap_free(heap* h) {
	if (h) {
		free(h->arr);
		free(h);
	}
}

void heap_print(heap* h) {
	printf("[heap]\t");
	for (int i = 0; i < h->size; i++) {
		printf("%d ", h->arr[i]);
	}
	printf("\n");
}
