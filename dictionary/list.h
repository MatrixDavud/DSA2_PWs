#ifndef LIST_H_
#define LIST_H_

/**
 ** @file
 ** @brief implement a FIFO/LIFO list type
 **/

#include <stdbool.h>
#include <stdlib.h>
#include "key_value.h"

typedef struct list list;

list* list_create(void);

list* list_delete(list* l);

size_t list_size(list const* l);

/**
 ** @brief Insert a new key value pair on top.
 ** @memberof list
 **/
list* list_push(list* l, key* k, value* v);

/**
 ** @brief Pop the value pair from the top.
 ** @memberof list
 **/
list* list_pop(list* l, key *k, value *v);

/**
 ** @brief Insert a new key value pair at bottom.
 ** @memberof list
 **/
list* list_append(list* l, key* k, value* v);

/**
 ** @brief Find the key in the list.
 **
 ** @return true if the key was found and copy the value into @c
 ** *v. Otherwise return @c false.
 **
 ** @memberof list
 **/
bool list_find(list const* l, key const* k, value * v);

/**
 ** @brief Remove the key from the list.
 **
 ** @return true if the key was found and copy the value into @c
 ** *v. Otherwise return @c false.
 **
 ** @memberof list
 **/
list* list_remove(list* l, key const* k);

#endif
