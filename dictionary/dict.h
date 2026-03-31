#ifndef DICT_H_
#define DICT_H_

/**
 ** @file dict.h
 ** @brief Interface for dictionary
 **/

#include <stdbool.h>
#include <stddef.h>
#include "key_value.h"

/**
 ** @struct dict
 ** @brief Abstract interface for dictionary.
 **
 ** This is thought to be used as opaque type for different
 ** implementations of the same set of functions.
 **
 ** In the module that implements this abstract interface, this can
 ** either be implemented as a proper <code>struct dict</code> or the
 ** token @c dict may just be redefined to another appropriate @c
 ** struct type.
 **/

#ifndef dict
typedef struct dict dict;
#endif

typedef key dict_key;
typedef value dict_value;

/**
 ** @brief create an empty dictionary
 **
 ** @memberof dict
 **/
dict* dict_create(void);

/**
 ** @brief delete the whole dictionary
 **
 ** May be called with empty or already deleted dictionary.
 **
 ** @memberof dict
 **/
dict* dict_delete(dict* d);

/**
 ** @brief compute the size of the dictionary
 **
 ** @memberof dict
 **/
size_t dict_size(dict const* d);

/**
 ** @brief insert key @a k with value @a v in dictionary @a d
 **
 ** @a v is copied in the dictonary
 **
 ** @return the modified dictionary.
 **
 ** May be called with empty or already deleted dictionary.
 **
 ** @memberof dict
 **/
dict* dict_insert(dict *d, dict_key* const k, dict_value* const v);

/**
 ** @brief search for key @a k in dictionary @a d
 **
 ** Returns @c true if @a k is found and copies @a k's value into @a
 ** *v.
 **
 ** May be called with empty or already deleted dictionary.
 **
 ** @memberof dict
 **/
bool dict_search(dict *d, dict_key* const k, dict_value* v);

/**
 ** @brief remove key @a k in dictionary @a d
 **
 ** @return the modified dictionary.
 **
 ** May be called with empty or already deleted dictionary.
 **
 ** @memberof dict
 **/
dict* dict_remove(dict *d, dict_key* const k);


#endif
