#include <stdlib.h>
#include "bstree.h"

/**
 ** @file
 ** @brief implementation for dict.h with binary search trees
 **/

/**
 ** @brief Interface for dictionary.
 **
 ** Here the dictionary is represented by the tree node type.
 **/
#define dict node

#include "dict.h"

dict* dict_create(void) {
  return 0; // empty tree
}

dict* dict_delete(dict* d) {
  tree_delete(d);
  return 0;
}

size_t dict_size(dict const* d) {
  return tree_size(d);
}

dict* dict_insert(dict *d, dict_key* const k, dict_value* const v) {
  if (!d) return node_create(k, v);
  return tree_bst_insert(d, k, v);
}

bool dict_search(dict *d, dict_key* const k, dict_value *v) {
  if (!d) return false;
  value* found = tree_bst_search(d, k);
  if (found && v) *v = *found;
  return found;
}

dict* dict_remove(dict *d, dict_key* const k) {
  return tree_bst_delete(d, k);
}
