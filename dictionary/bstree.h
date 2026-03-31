#ifndef TREE_H
#define TREE_H

#include "key_value.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;
typedef struct pair pair;


enum  direction { left, right };
typedef enum direction direction;

enum node_type { normal, empty };
typedef enum node_type node_type;

enum order_type { prefix, infix, postfix };
typedef enum order_type order_type;

/**
 ** @brief initialize a node @a n with key @a key and value @a value
 **
 ** @return @a n
 **
 ** Initializes all other fields to @c 0.
 **/
node* node_init(node* n, key* key, value* value);


/**
 ** @brief create a new node with initial key @a key and value @a val
 **/
node* node_create(key* const k, value* const v);

/**
 ** @brief delete a node @a n
 **
 ** @pre both children must be empty
 **/
void node_delete(node* n);


/**
 ** @brief insert a new node at the @a dir side of @a root
 **
 ** If @a root already has a child @c x on that side, @c x becomes the
 ** child of the newly created node.
 **
 ** @return the newly created node.
 **/
node* node_insert(node *root, key *k, value *v, direction dir);

/**
 ** @brief detect if @a n has children
 **/
bool node_isinner(node *n);

/**
 ** @brief detect if @a n is a leaf
 **/
bool node_isleaf(node *n);



/**
 ** @brief delete the whole tree pending at @a root
 **/
void tree_delete(node* root);

/**
 ** @brief compute the height of a tree
 **
 ** definition: height is the number of nodes on the longest branch.
 ** height of an empty tree is 0.
 **/
size_t tree_height(node* root);

/**
 ** @brief compute the number of nodes in a tree
 **/
size_t tree_size(node const* root);


/**
 ** @brief insert a key @k and value @v pair into a Binary Search Tree.
 ** @return a pointer to the last inserted node.   
 **/
node *tree_bst_insert(node *n, key* const k, value* const v);


//key *tree_bst_min_key(node *root);

/**
 ** @brief search a key @a k in a Binary Search Tree and return the associated value
 ** if found, or null otherwise.
 **/
value *tree_bst_search(node *n, key* const k);

/**
 ** @brief search a key @a k in a Binary Search Tree and return 
 ** a pair (node, parent) where node contains k, and parent is 
 ** the parent of node.
 **/
static
pair *tree_bst_search_node(pair *p, key* const k);

/**
 ** @brief delete a node given its key @a k in a Binary Search Tree.
 ** @return the root of the tree after deletion (as it might have changed)
 **/
node *tree_bst_delete(node *root, key const *k);
/**
 ** @brief pretty print a tree
 **/
void tree_print(node* root);

/**
 ** @brief Performs a depthfirst visit of nodes (does no actual/useful action)
 **/
void tree_depthfirst_visit(node *n);

/**
 ** @brief Performs a infix visit of nodes 
 **/
void tree_infix_visit(node *n);

#endif
