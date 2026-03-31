#ifndef KEY_VALUE_H_
#define KEY_VALUE_H_

/**
 ** @file key_value.h
 **
 ** @brief Implement the key-value pairs needed for the dictionary
 ** example.
 **/

enum {
  key_size = 30,    /**< The max size of dictonary keys **/
};

/**
 ** @brief The key of the dictionary implementation.
 **
 ** @warning ::key_size must also account for the trailing @c 0 character
 **/
typedef struct key key;

struct key {
  char key[key_size];
};

/**
 ** @brief compare two keys lexicographically
 **
 ** @return a value negative, @c 0 or positive if @a a is less than,
 ** equal to or greater than @a b.
 **
 ** @memberof key
 **/
signed key_cmp(key const* a, key const* b);

key* min_key(key* k1, key* k2);



/**
 ** @brief initialize a ::key with a string
 **
 ** Copies the data to its own storage.
 **
 ** @memberof key
 **/
key* key_init(key* k, char const* s);


/**
 ** @brief create a new key with initial value @a s
 ** 
 ** Creates a key and assign @a s to it.
 **
 ** @memberof key
 **/
key *key_create(char* const s);


/**
 ** @brief obtain the string that is stored in a ::key
 **
 ** @memberof key
 **/
char* const key_string(key* const a);

enum {
  value_size = 128, /**< The max size of dictonary values **/
};

/**
 ** @brief The value of the dictionary implementation.
 **
 ** @warning ::value_size must also account for the trailing 0 character
 **/
typedef struct value value;

struct value {
  char value[value_size];
};

/**
 ** @brief initialize a ::value with a string
 **
 ** Copies the data to its own storage.
 **
 ** @memberof value
 **/
value* value_init(value* v, char* const s);

/**
 ** @brief create a new value  with initial value @a s
 ** 
 ** Creates a value  and assign @a s to it.
 **
 ** @memberof value
 **/
value * value_create(char* s);


/**
 ** @brief obtain the string that is stored in a ::value
 **
 ** @memberof value
 **/
char* value_string(value* const v);


#endif
