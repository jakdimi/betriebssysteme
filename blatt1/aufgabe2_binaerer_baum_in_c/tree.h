#include <stdlib.h>

typedef struct _node_t {
  int value;
  struct _node_t *parent;
  struct _node_t *left;
  struct _node_t *right;
} node_t;
// create new Tree with one root node, which holds rootValue as value
node_t *createTree(int rootValue);

// insert value in tree
void insert(node_t *tree, int value);

// return 1 iff value is found in tree, 0 otherwise
int binarySearch(node_t *tree, int value);

// free all dynamically allocated memory of tree
void cleanUpTree(node_t *tree);

