#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

static
unsigned const good[] = {
  31, 33, 37,
  /************ To be completed ***********************/
};

static
size_t const alter = sizeof good / sizeof *good; //< the number of bases in good

/**
 ** @brief a good family of hash functions
 **/
static
size_t hash_base(char const*s, size_t table_size, unsigned base) {
  size_t ret=0;
  /************ To be completed ***********************/
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
    /************ To be completed ***********************/
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
