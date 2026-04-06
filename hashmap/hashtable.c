#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

static
unsigned const good[] = {
  31, 33, 37, 41, 47, 51, 53, 61, 67, 71,
  131, 133, 137, 141, 547, 551, 553, 561, 567, 571,
  2131, 3133, 4137, 5141, 6547, 7551, 8553, 9561, 11567, 12571,
  3031, 3033, 3037, 3041, 3047, 3051, 3053, 3061, 3067, 3071,
  331, 333, 337, 341, 347, 351, 353, 361, 367, 371,
};

static
size_t const alter = sizeof good / sizeof *good; //< the number of bases in good

/**
 ** @brief a good family of hash functions
 **/
static
size_t hash_base(char const*s, size_t table_size, unsigned base) {
  size_t ret = 0;
  size_t len = strlen(s);
  unsigned long power = 1;
  
  for (int i = len - 1; i >= 0; --i) {
    ret = (ret + ((unsigned char)s[i] * power) % table_size) % table_size;
    power = (power * base) % table_size;
  }
  
  return ret;
}

static
char* duplicate(char const* s) {
  return strcpy(malloc(1+strlen(s)), s);
}

/**
 ** @brief return a hash table of size @a size
 **/
hashtable* hashtable_create(size_t size) {
  hashtable* ret = malloc(sizeof *ret);
  if (ret) {
    ret->size = size;
    ret->key = calloc(size, sizeof *ret->key);
    ret->value = calloc(size, sizeof *ret->value);
  }
  return ret;
}

/**
 ** @brief delete hashtable
 **/
void hashtable_delete(hashtable* h) {
  for (size_t i = 0; i < h->size; ++i)
    free((void*)h->key[i]);
  free(h->key);
  for (size_t i = 0; i < h->size; ++i)
    free((void*)h->value[i]);
  free(h->value);
  free(h);
}

/**
 ** @brief return the position of key in the table
 **/
size_t hashtable_position(hashtable* h, char const* key) {
  for (size_t f = 0; f < alter; ++f) {
    size_t pos = hash_base(key, h->size, good[f]);
    
    // If position is empty, we found a free slot
    if (h->key[pos] == 0) {
      h->key[pos] = duplicate(key);
      return pos;
    }
    
    // If position is occupied, check if it's the same key
    if (strcmp(h->key[pos], key) == 0) {
      return pos;
    }
    // Otherwise, continue to next hash function
  }
  fprintf(stderr, "no valid hash postion found for %s after %zu tries\n", key, alter);
  exit(1);
}

void hashtable_set(hashtable* h, char const* key, char const* val){
  size_t pos = hashtable_position(h, key);
  if (h->value[pos] && val && strcmp(h->value[pos], val))
    free((void*)h->value[pos]);
  h->value[pos] = duplicate(val);
}

char* hashtable_get(hashtable* h, char const* key){
  size_t pos = hashtable_position(h, key);
  return (h->value[pos])
    ? duplicate(h->value[pos])
    : 0;
}
