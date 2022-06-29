/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* bst = malloc(sizeof(bst));
  bst->root = NULL;
  return bst;
}







void bst_node_free(struct bst_node* node);
/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  bst_node_free(bst->root);
  free(bst);
  return;
}

void bst_node_free(struct bst_node* node) {
  if(node == NULL) {
    return;
  }
  bst_node_free(node->left);
  bst_node_free(node->right);
  free(node);
  return;
}

int bst_increment_nodes(struct bst_node* node);
/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  return bst_increment_nodes(bst->root);
}

int bst_increment_nodes(struct bst_node* node) {
  int sum = 0;
  if(node->left != NULL) {
    sum += bst_increment_nodes(node->left);
  }
  if(node->right != NULL) {
    sum += bst_increment_nodes(node->right);
  }

  return sum + 1;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  struct bst_node* next = bst->root;

  struct bst_node* new = malloc(sizeof(struct bst_node));
  new->key = key;
  new->value = value;
  new->right = NULL;
  new->left = NULL;

  if(next == NULL) {
    bst->root = new;
    return;
  }

  while(next != NULL) {
    if(key >= next->key) {
      if(next->right == NULL) {
        next->right = new;
        return;
      } else{
        next = next->right;
      }
    } else {
      if(next->left == NULL) {
        next->left = new;
        return;
      } else{
        next = next->left;
      }
    }
  }

  //THIS SHOULD NEVER BE REACHED
  printf("Failed to insert");
  return;
}


struct bst_node* bst_findNodeParent(struct bst* bst, int key);
struct bst_node* bst_followLeftParent(struct bst_node* node);
/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  struct bst_node* node = bst->root;
  struct bst_node* parent;
  int noParent = 0;
  int isRight = 1;
  
  if(node->key == key) {
    //Yes this is incredibly redundant but it makes it much more readable
    node = node;
    noParent = 1;
  } else {
    //Find Node
    parent = bst_findNodeParent(bst, key);
    if(key < parent->key) {
      node = parent->left;
      isRight = 0;
    } else{
      node = parent->right;
      isRight = 1;
    }
  }

  //Act
  if(node->left == NULL && node->right == NULL) {
    //No Children
    if(noParent == 1) {
      bst->root = NULL;
      free(node);
      return;
    }

    if(isRight == 1) {
      parent->right = NULL;
      free(node);
      return;
    } else{
      parent->left = NULL;
      free(node);
      return;
    }

  } else if(node->left != NULL && node->right == NULL) {
    //Left Child
    if(noParent == 1) {
      bst->root = node->left;
      free(node);
      return;
    }

    if(isRight == 1) {
      parent->right = node->left;
      free(node);
      return;
    } else{
      parent->left = node->left;
      free(node);
      return;
    }

  } else if(node->left == NULL && node->right != NULL){
    //Right Child
    if(noParent == 1) {
      bst->root = node->right;
      free(node);
      return;
    }

    if(isRight == 1) {
      parent->right = node->right;
      free(node);
      return;
    } else{
      parent->left = node->right;
      free(node);
      return;
    }

  } else{
    //Two Children
    struct bst_node* inOrderSuccessorParent = node;
    struct bst_node* inOrderSuccessor = node->right;
    while (inOrderSuccessor->left != NULL) {
        inOrderSuccessorParent = inOrderSuccessor;
        inOrderSuccessor = inOrderSuccessor->left;
    }
    if (inOrderSuccessorParent != node) {
        inOrderSuccessorParent->left = inOrderSuccessor->right;
    }
    else {
        inOrderSuccessorParent->right = inOrderSuccessor->right;
    }
    node->key = inOrderSuccessor->key;
    node->value = inOrderSuccessor->value;
    free(inOrderSuccessor);
    return;
  }
}

struct bst_node* bst_findNodeParent(struct bst* bst, int key) {
  struct bst_node* node = bst->root;
  int found = 0;
  while(found == 0) {
    if(key < node->key) {
      if(node->left != NULL) {
        if(node->left->key == key) {
          return node;
        } else{
          node = node->left;
        }
      } else{
        return NULL;
      }
    } else {
      if(node->right != NULL) {
        if(node->right->key == key) {
          return node;
        } else{
          node = node->right;
        }
      } else{
        return NULL;
      }
    }
  }
}
struct bst_node* bst_followLeftParent(struct bst_node* node) {
  int isFound = 0;
  while(isFound == 0) {
    if(node->left->left == NULL) {
      return node->left;
    } else{
      node = node->left;
    }
  }
}



/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  struct bst_node* next = bst->root;
  while(next != NULL) {
    if(key == next->key) {
      return next->value;
    } else if(key >= next->key && next->right != NULL) {
      next = next->right;
    } else if(key < next->key && next->left != NULL) {
      next = next->left;
    } else {
      return NULL;
    }
  }
  return NULL;
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

int bst_height_rec(struct bst_node* node);
/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
   return bst_height_rec(bst->root)-1;
 }

 int bst_height_rec(struct bst_node* node) {
   int right = 0;
   int left = 0;
   if(node->left != NULL) {
     left += bst_height_rec(node->left);
   }
   if(node->right != NULL) {
     right += bst_height_rec(node->right);
   }
   if(left>right) {
     return left+1;
   }
   return right+1;
 }


int bst_path_sum_rec(struct bst_node* node, int sum);
/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
  return bst_path_sum_rec(bst->root, sum);
}

int bst_path_sum_rec(struct bst_node* node, int sum) {
  if(node == NULL) {
    return 0;
  }
  if(node->key == sum && node->left == NULL && node->right == NULL){
    return 1;
  }
  return bst_path_sum_rec(node->left, sum - node->key) || bst_path_sum_rec(node->right, sum-node->key);
}

int bst_range_sum_rec(struct bst_node* node, int lower, int upper);
/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  return bst_range_sum_rec(bst->root, lower, upper);
}

int bst_range_sum_rec(struct bst_node* node, int lower, int upper) {
  if(node == NULL) {
    return 0;
  }

  if(node->key >= lower && node->key <= upper){
    return node->key + bst_range_sum_rec(node->left, lower, upper) + bst_range_sum_rec(node->right, lower, upper);
  } else if(node->key < lower){
    return bst_range_sum_rec(node->right, lower, upper);
  } else if(node->key > upper){
    return bst_range_sum_rec(node->left, lower, upper);
  }
}


/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};


void bst_iterator_fill(struct bst_node* node, struct stack* stk);
/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  struct bst_iterator* it = malloc(sizeof(struct bst_iterator));
  it->stack = stack_create(); 
  bst_iterator_fill(bst->root, it->stack);
  return it;
}

void bst_iterator_fill(struct bst_node* node, struct stack* stk) {
  if(node == NULL) return;
  
  bst_iterator_fill(node->right, stk);
  stack_push(stk, node);
  bst_iterator_fill(node->left, stk);
  return;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  stack_free(iter->stack);
  free(iter);
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  if(stack_isempty(iter->stack) == 1) {
    return 0;
  } else {
    return 1;
  }
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  if(stack_isempty(iter->stack)) return 0;
  struct bst_node* node = stack_pop(iter->stack); 
  *value = node->value;
  return node->key;
}
