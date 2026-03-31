#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "list.h"
#include "lnode.h"

/**
 ** @file
 ** @brief implementation for list.h
 **/

struct list {
  lnode* top;
  lnode* bot;
  size_t size;
};

list* list_init(list* l) {
  if (l) {
    *l = (list){ 0 };
  }
  return l;
}

list* list_create(void) {
  list* ret = list_init(malloc(sizeof *ret));
  return ret;
}

list* list_delete(list* l) {
  if (l) {
    while (l->top) l->top = lnode_pop(l->top, 0, 0);
    free(l);
  }
  return 0;
}

size_t list_size(list const* l) {
  return l ? l->size : 0;
}


list* list_push(list* l, key* k, value* v) {
  if (l) {
    l->top = lnode_push(l->top, k, v);
    if (!l->bot) l->bot = l->top;
    ++l->size;
  }
  return l;
}

list* list_pop(list* l, key* k, value* v) {
  if (l->top) {
    l->top = lnode_pop(l->top, k, v);
    if (!l->top) l->bot = l->top;
    --l->size;
  }
  return l;
}

list* list_append(list* l, key* k, value* v) {
  if (l) {
    lnode* prev = l->bot;
    l->bot = lnode_append(prev, k, v);
    if (!prev) {
      l->top = l->bot;
    }
    ++l->size;
  }
  return l;
}

bool list_find(list const* l, key const* k, value* v) {
  if (l) {
    lnode* el = lnode_find(l->top, k, v);
    return el;
  }
  return false;
}

list* list_remove(list* l, key const* k) {
  if (l && l->top) {
    lnode* prev = lnode_find_prev(l->top, k);
    // This was not a removal of the first element
    if (prev) {
      // test if we are at the last element
      if (lnode_size(prev, 2) < 2) l->bot = prev;
      else {
        lnode_drop(prev);
        --l->size;
      }
    } else {
      // the element is the top
      l->top = lnode_pop(l->top, 0, 0);
      // if this was the last element update bot
      if (!l->top) l->bot = 0;
      --l->size;
    }
  }
  return l;
}
