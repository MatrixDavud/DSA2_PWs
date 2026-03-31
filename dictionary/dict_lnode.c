#include <stdint.h>
#include "lnode.h"  

/**
 ** @file
 ** @brief implementation for dict.h with simple lists
 **/

/**
 ** @brief Interface for dictionary.
 **
 ** In this implementation the dictionary is just defined by simple
 ** text replacement to be an ::lnode.
 **/
#define dict lnode

#include "dict.h"

dict* dict_create(void) {
  return lnode_create();
}

dict* dict_delete(dict* d) {
  return lnode_delete(d);
}

size_t dict_size(dict const* d) {
  return lnode_size(d, SIZE_MAX);
}


dict* dict_insert(dict * d, dict_key* const c, dict_value* const v) {
  return lnode_push(d, c, v);
}

bool dict_search(dict * d, dict_key* const c, dict_value *v) {
  return lnode_find(d, c, v);
}

dict* dict_remove(dict * d, dict_key* const c) {
  if (!d) return 0;

  lnode* target = lnode_find(d, c, 0);
  if (!target) return d; // not found

  if (target == d) {
    return lnode_pop(d, 0, 0);
  }

  lnode* prev = lnode_find_prev(d, c);
  if (prev) lnode_drop(prev);
  return d;
}
