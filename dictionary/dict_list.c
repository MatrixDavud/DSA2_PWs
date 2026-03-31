#include <stdint.h>
#include "list.h"

/**
 ** @file
 ** @brief implementation for dict.h with enhanced lists
 **/

/**
 ** @brief Interface for dictionary.
 **
 ** In this implementation the dictionary maps directly to ::list.
 **/
#define dict list

#include "dict.h"

dict* dict_create(void) {
  return list_create();
}

dict* dict_delete(dict* d) {
  return list_delete(d);
}

size_t dict_size(dict const* d) {
  return list_size(d);
}

dict* dict_insert(dict *d, dict_key* const k, dict_value* const v) {
  return list_push(d, k, v);
}

bool dict_search(dict *d, dict_key* const k, dict_value *v) {
  return list_find(d, k, v);
}

dict* dict_remove(dict *d, dict_key* const k) {
  return list_remove(d, k);
}

