#include <stddef.h>

typedef struct hashtable hashtable;

struct hashtable {
  size_t size;             // size of the table
  char const** key;         // table of size keys
  char const** value;       // table of size values
};

/**
 ** @brief return a hash table of size @a size
 **/
hashtable* hashtable_create(size_t size);

/**
 ** @brief return a hash table of size @a size
 **/
void hashtable_delete(hashtable* h);

/**
 ** @brief return the position of key in the table
 **
 ** This function uses a family of hash functions that are tried one
 ** after another until either @a key is found in the position, or to
 ** position is empty. In the later case, @a key is entered at the
 ** position.
 **/
size_t hashtable_position(hashtable* h, char const* key);

/**
 ** @brief insert @a value at position @a key
 **/
void hashtable_set(hashtable* h, char const* key, char const* val);

/**
 ** @brief insert @a value at position @a key
 **
 ** @return A copy of the value stored at that position
 **/
char* hashtable_get(hashtable* h, char const* key);
