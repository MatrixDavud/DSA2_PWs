#include <stdio.h>
#include "heap.h"

void array_print(int *arr, size_t len, char *msg) {
	printf("%s:\t", msg);
	fflush(stdout);
	for (size_t i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}


int main()
{
	int arr[10] = {4,1,3,2,16,9,10,14,8,7};
	size_t arr_size = sizeof(arr)/sizeof(arr[0]);

	heap* h = heap_build_max_heap(arr_size, arr);

	printf("\n> Build a max heap from values\n");
	array_print(arr, arr_size, "values");
	heap_print(h);
	
	printf("\n> Extract max from heap\n");
	int deleted = heap_extract_max(h);
	printf("-> key:%d deleted\n", deleted);
	heap_print(h);

    size_t index=arr_size/2-2;
    int k=42;
	printf("\n> Increase key of A[%zu]=%d to key=%d\n", index, heap_get_key(h,index), k);
	heap_increase_key(h, index, k);
	heap_print(h);

    int keys[] = {11,5,19,25};
    for (size_t i=0; i< sizeof(keys)/sizeof(*keys);i++) {
	   printf("\n> Insert key=%d\n", keys[i]);
	   heap_insert(h, keys[i]);
	   heap_print(h);
    }

	// after demo on heap h, we do not need it anymore.
	heap_free(h);

    // heap-sort demo.
	printf("\n> Heap Sort of %zu elements\n", arr_size);
	array_print(arr, arr_size, "unsorted");
	int *res = heap_sort(arr_size, arr);
	array_print(res, arr_size, "sorted");

	free(res);
	return 0;
}
