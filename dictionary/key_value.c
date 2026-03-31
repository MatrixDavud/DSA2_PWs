#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "key_value.h"

/**
 ** @file
 ** @brief implementation for key_value.h
 **/

signed key_cmp(key const* a, key const* b) {
  if (a == b) return 0;
  if (!a) return -1;
  if (!b) return 1;
  return strcmp(a->key, b->key);
}

key* min_key(key* k1, key* k2) {
  assert(k1 || k2);
  if (k1 && !k2) return k1;
  if (!k1 && k2) return k2;
  // k1 and k2 are not null
  if (key_cmp(k1, k2) < 0) 
    return k1;
  else
    return k2;
}



key* key_init(key* k, char const* s) {
  if (k) {
	 if (s) strncpy(k->key, s, key_size);
	 else return 0;
  }
  return k;
}

/**
 ** @brief create a new key with initial value @a s
 **/
key* key_create(char * const s) {
    key * ret = key_init(malloc(sizeof *ret), s);
    return ret;
}


char* const key_string(key* const k) {
  return k ? k->key : 0;
}

value* value_init(value* const v, char* s) {
  if (v) {
	 if (s) strncpy(v->value, s, value_size);
       else return 0;
  }
  return v;
}

/**
 ** @brief create a new node with initial value @a val
 **/
value* value_create(char* s) {
      value* ret = value_init(malloc(sizeof *ret), s);
	return ret;
}

char* value_string(value* const v) {
  return v ? v->value : 0;
}
