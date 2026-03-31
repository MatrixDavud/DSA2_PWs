/**
 * A tree data structure implementation with nodes containing a key,value pair
 *
 **/ 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "bstree.h"
#include "key_value.h"

/**
 * @brief maximum of 2 ints
 **/
int max(int a,int b) {
	  return(a>b ? a:b);
} 


/**
 ** @brief a simple DS for a tree node
 **/
/**
 ** @brief a simple DS for a tree node
 **/
struct node {
	key       *k;
	value     *v;
	node      *lchild;   /**< the left child */
	node      *rchild;   /**< the right child */
	node_type ntype;     /**< to handle special nodes */
	int       unbalance; /**< to handle unblance in AVL trees */
};
/* 
 * define a struct to store a pair of nodes.
 */
struct pair {
	node * node;
	node * parent;
};


node* node_init(node* n, key* key, value* value) {
  if (n) {
	    /* Initializes the whole structure. */
	    *n = (node){
			.k = key_create(key_string(key)),
			.v = value_create(value_string(value)),
			.lchild = 0,
			.rchild = 0,
		};
   }
   return n;
}

/**
 ** @brief create a new node with initial value @a val
 **/
node* node_create(key* const k, value* const v) {
	  node * ret = node_init(malloc(sizeof *ret), k, v);
	  return ret;
}



void node_delete(node* n) {
	  if (n) {
		    assert(!n->lchild);
		    assert(!n->rchild);
	  }
	  free(n);
}

/**
 * @brief copy the contents of node @a src into node @a dst.
 * @pre nodes src and dst must exist 
 * @
 * @return false if either src or dst do not exist, true otherwise.
*/
bool node_replace(node *src, node *dst, bool include_links) {
	if (!src || !dst) 
	  return false;
    dst->k = src->k;
    dst->v = src->v;
	if (include_links) {
    	dst->lchild = src->lchild;
		dst->rchild = src->rchild;
	} 
	return true;
}

node* node_insert(node *root, key* k, value *v, direction dir) {
	  assert(root);
	  node * ret = node_create(k,v);
	  if (dir == left) {
		    ret->lchild = root->lchild;
		    root->lchild = ret;
	  } else {
		    ret->rchild = root->rchild;
		    root->rchild = ret;
	  }
	  return ret;
}

bool node_isinner(node *n) {
	  assert(n);
	  return (n->lchild || n->rchild) ;
}

bool node_isleaf(node *n) {
	  assert(n);
	  return !node_isinner(n);
}


void tree_delete(node* n) {
	  if (n) {
		    tree_delete(n->lchild);
		    tree_delete(n->rchild);
		    n->lchild = 0;
		    n->rchild = 0;
		    node_delete(n);
	  };
}

size_t tree_height(node* root) {
	  size_t height = 0;
	  if (root) {
		    return max(1+tree_height(root->lchild),
				   1+tree_height(root->rchild));
	  }
	  return height;
}


size_t tree_size(node const* root) {
	  size_t size = 0;
	  if (root) {
		    size_t sl = tree_size(root->lchild);
		    size_t sr = tree_size(root->rchild);
		    size = sl + sr + 1;
	  }
	  return size;
}

/**
 ** @brief find the minimum key in a BST 
 **
 ** @param root the root of the BST to search
 ** @return *key the minimum key, or null if the passed BST was empty.
 **/
static 
key *tree_bst_min_key(node *root) {
	if (root) {
	  if (node_isleaf(root)) {
		return root->k;
	  }
	  key *mink = root->k;
	  if (root->lchild)
	  	mink = min_key(mink, tree_bst_min_key(root->lchild));
	  if (root->rchild)
	  	mink = min_key(mink, tree_bst_min_key(root->rchild));
	  return mink;
	}
	return 0;
}

/**
 * @brief given node root's key k, find node whose key k' has the lowest value greater than k
 * 
 * @param root the root of the searched tree
 * @return *node containing the min key k', or null if no such value k' can be found. 
 */
static
node *find_inorder_successor(node *root) {
	node *succ;
	if (root) {
		// we want the min key that is greater to k, search in right subtree
		key *mink = tree_bst_min_key(root->rchild);
		pair * p = malloc(sizeof(pair));
		*p = (pair) { .node = root->rchild, .parent = root}; 
		p = tree_bst_search_node(p, mink);
		succ = p->node;
		if (0==succ)
			return 0; // key was not found 
		// found node containing k, it's p->node
		return succ;
		free(p);
	}
	return 0;
}


/**
 ** @brief insert a key @k and value @v pair into a Binary Search Tree.
 **/
node *tree_bst_insert(node *root, key* k, value* v) {
	// node *n=0; if we want to check the result from node_insert
    assert(root);  
	/* specific case: a node with (k=0,v=0) marks an initial node,
	 * replace its null values at first insertion.
	 * Might be set by a function e.g dict_create() 
	**/ 
	if (node_isleaf(root) && !root->k && !root->v) {
		root->k = key_create(key_string(k));
		root->v = value_create(value_string(v));
		return root;
	}
	 /* normal case */
	if (key_cmp(k,root->k) < 0) { /* k < root->k, take left branch */
	 	if (!root->lchild) /* no child on the left, make a leaf */ {
			node_insert(root,k,v,left);
		}
		else  /* there is a left child, take the branch */
			tree_bst_insert(root->lchild,k,v);
	}
	else { /* k > root->k, take right branch */
		if (!root->rchild)
			node_insert(root,k,v,right);
		else
			tree_bst_insert(root->rchild,k,v);
	}
	// k==root->k :the key's to insert was already in the tree
	return root; 
}


/**
 ** @brief search a key @a k in a Binary Search Tree and return the associated value.
 **/
value *tree_bst_search(node *root, key* const k) {
	  /* base case for the recurrence: node is empty */
	  if (0==root)
		return 0; 
	  signed diff = key_cmp(k,root->k);
	  /* base case: keys match */ 
	  if (0 == diff) {
	  	return root->v;
	  }
	  /* diff < 0 : left branch*/
	  if (diff < 0)
		return tree_bst_search(root->lchild,k);
	  /* diff > 0 : right branch*/
	  return tree_bst_search(root->rchild,k);
}




/**
 ** @brief search a key @a k in a Binary Search Tree and return 
 ** a pair (node, parent) where node contains k, and parent is 
 ** the parent of node.
 **/
static
pair *tree_bst_search_node(pair *p, key* const k) {
	/* base case for the recurrence: node is empty */
	if (0==p->node)
		return p; 
	signed diff = key_cmp(k,p->node->k);
	/* base case: keys match */ 
	if (0 == diff) {
	  	return p;
	}
	// update parent
	p->parent = p->node;
	if (diff < 0) 
		p->node = p->node->lchild;
	if (diff >0)
	    p->node = p->node->rchild;
	return tree_bst_search_node(p, k);
}
/**
 ** @brief delete a node given its key @a k in a Binary Search Tree.
 ** @return the root of the tree after deletion (as it might have changed)
 **/
node *tree_bst_delete(node *root, key const *k) {
	if (0==root) 
		return 0;
	// compare keys and branch left or right
	if (key_cmp(k,root->k) < 0) {
		// k lower that root->k, take left branch.
		root->lchild = tree_bst_delete(root->lchild, k);
	}
	else {
		if (key_cmp(k,root->k) > 0) {
			// k greater that root->k, take right branch.
			root->rchild = tree_bst_delete(root->rchild, k);
		}
		else { 	// equal, found the node with key. 
			if (node_isleaf(root)) {
				//printf("@case 1: %s is a leaf\n", key_string(root->k));
				node_delete(root); // root storage is freed but we still
				root = 0;          // have the pointer root to it, setting it to 0
				//return root;       // will correct linkage in back recursion
			}
			else { // Examine the 2 remaining cases :	
				size_t nbchild = 0;
				if (root->lchild !=0) nbchild++;
				if (root->rchild !=0) nbchild++;
				node *succ = 0;
				// case 2 : one child
				if (nbchild == 1) {
					succ = root->lchild !=0  ? root->lchild : root->rchild;
					// succ is to be deleted
					//printf("@case 2 : %s has only 1 child : %s\n", key_string(root->k), key_string(succ->k));
					// copy child node into the node to delete, including its links
					node_replace(succ, root, true);
					// delete child (must set its links to 0 first)
					succ->lchild=0; succ->rchild=0;
					node_delete(succ);
				}
				// case 3: two children
				if (nbchild ==2) {
					//printf("@case 3 : %s has 2 children\n", key_string(root->k));
					node *succ = find_inorder_successor(root);
					//printf("-> inorder successor=%s\n", key_string(succ->k));
					// copy succ node into the node to delete, keeping original links
					node_replace(succ, root, false);
					// now the problem reduces to delete the succesor
					root->rchild = tree_bst_delete(root->rchild, succ->k);
				}
			}
		}
	}
	return root;
}

static
void tree_print_rec(node* root, char const* pre) {
	  if (root) {
		    size_t depth = pre ? strlen(pre) : 0;
		    char npre[depth + 2];
		    if (pre) strcpy(npre, pre);
		    npre[depth + 1] = 0;

		    printf("%s(%s,%s)\n", pre, key_string(root->k), value_string(root->v));
		    if (depth) npre[depth - 1] = '-';
		    npre[depth] = '<';  // left symbol
		    tree_print_rec(root->lchild, npre);
		    npre[depth] = '>';  // right symbol
		    tree_print_rec(root->rchild, npre);
	  }
}

/**
 * @brief print the tree
 **/
void tree_print(node* root) {
	printf("[===tree===]\n");
	if (root==0)
		printf("(empty tree)\n");
	else
	  tree_print_rec(root, "");
	printf("[===/tree===]\n");

}

