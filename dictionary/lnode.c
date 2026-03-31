#include <stdlib.h>
//#include <stdio.h>
#include "lnode.h"

/**
 ** @file
 ** @brief implementation for lnode.h
 **/

struct lnode {
  key *k;
  value *v;
  lnode* next;
};

lnode* lnode_create(void) {
  return 0;
}

lnode* lnode_delete(lnode* l) {
  lnode *p=l;

  while (p) {
    lnode* next = p->next;
    free(p);
    p = next;
  }
  return 0;
}

size_t lnode_size(lnode const* l, size_t size_max) {
  size_t ret = 0;
  while (l && ret < size_max) {
    ++ret;
    l = l->next;
  }
  return ret;
}

lnode* lnode_init(lnode* l, key *k, value *v, lnode* next) {
  if (l) {
    l->k = key_create(key_string(k));
    l->v = value_create(value_string(v));
    l->next = next;
  }
  return l;
}

lnode* lnode_push(lnode* l, key *k, value * v) {
  lnode* ret
    = lnode_init(malloc(sizeof *ret), k, v, l);
  return ret;
}

lnode* lnode_append(lnode* l, key* k, value* v) {
  lnode* next = (l ? l->next : 0);
  lnode* ret = lnode_init(malloc(sizeof *ret), k, v, next);
  if (l) {
    l->next = ret;
  }
  return ret;
}

lnode* lnode_pop(lnode* l, key* k, value* v) {
  if (!l) return 0;
  lnode* n = l->next;
  if (k) *k = *(l->k);
  if (v) *v = *(l->v);
  free(l);
  return n;
}

void lnode_drop(lnode* l) {
  if (l) l->next = lnode_pop(l->next, 0, 0);
}

lnode* lnode_find(lnode *l, key const *k, value* v) {
  lnode *ll;
  ll = l;
  while (ll) {
    if (!key_cmp(ll->k, k)) {
      if (v) 
	 *v = *(ll->v);
      return ll;
    }
    ll = ll->next;
  }
  return 0;
}

lnode* lnode_find_prev(lnode *l, key const *k) {
  lnode* prev = 0;
  for (lnode* p = l; p; p = p->next) {
    if (!key_cmp(p->k, k)) break;
    prev = p;
  }
  return prev;
}

lnode* lnode_remove(lnode* l, key const *k) {
  lnode* prev = lnode_find_prev(l, k);
  if (prev) {
    /* char const* name = key_string(&prev->k); */
    /* char const* nname = prev->next ? key_string(&prev->next->k) : "<none>"; */
    /* printf("prev %s, next %s\n", name, nname); */
    prev->next = lnode_pop(prev->next, 0, 0);
    /* nname = prev->next ? key_string(&prev->next->k) : "<none>"; */
    /* printf("prev %s, next %s\n", name, nname); */
  }
  return prev;
}

