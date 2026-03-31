#ifndef LNODE_H_
#define LNODE_H_

/**
 ** @file
 ** @brief interface of a simple list element type
 **/

#include <stdbool.h>
#include <stddef.h>
#include "key_value.h"

typedef struct lnode lnode;

lnode* lnode_create(void);
lnode* lnode_delete(lnode* l);

/**
 ** @brief the size of the list starting at @a l
 **
 ** @memberof lnode
 **/
size_t lnode_size(lnode const* l, size_t size_max);


/**
 ** @brief push a key value pair in front of node @a l
 **
 ** @return the new node, which is now the head of the list
 **
 ** @memberof lnode
 **/
lnode* lnode_push(lnode* l, key * k, value *v);

/**
 ** @brief append a key value pair after node @a l
 **
 ** @return the new head of the list, which is @a l if it was not empty
 ** before, or the new node, otherwise
 **
 ** @memberof lnode
 **/
lnode* lnode_append(lnode* l, key* k, value* v);


/**
 ** @brief pop a key value pair from list @a l
 **
 ** @return the new head of the list
 **
 ** Previous key and value may be obtain through the arguments @a k
 ** and @a v. These are ignored if they are @c 0.
 **
 ** @memberof lnode
 **/
lnode* lnode_pop(lnode* l, key* k, value* v);

/**
 ** @brief remove the next element after @a l
 **
 ** @memberof lnode
 **/
void lnode_drop(lnode* l);

/**
 ** @brief find key in list @a l
 **
 ** @return a node that holds the @a k or @c 0 if it can't be found
 **
 ** If found, the value for the key is copied into @c *v.
 **
 ** @memberof lnode
 **/
lnode* lnode_find(lnode *l, key const *k, value* v);

/**
 ** @brief find key in list @a l
 **
 ** @return a node preceding the one that holds the @a k or @c 0 if
 ** the first element holds the key. If not found the last element of
 ** the list is returned.
 **
 ** @memberof lnode
 **/
lnode* lnode_find_prev(lnode *l, key const *k);


/**
 ** @brief remove key @a k in list @a l if it is not the first element
 **
 ** @return the predecessor of that node, if it exists. Otherwise, if
 ** @a k was not found return the last element of the list. If the
 ** first element of the list holds @a k return @c 0.
 **
 ** @memberof lnode
 **/
lnode* lnode_remove(lnode* l, key const* k);

#endif
