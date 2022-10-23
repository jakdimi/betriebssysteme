#include <stdlib.h>

#include "tree.h"

// create new Tree with one root node, which holds rootValue as value
node_t *createTree(int rootValue) {
  node_t* ptr_root = malloc(sizeof(node_t));
  ptr_root->value = rootValue;
  return ptr_root;
}

// insert value in tree
void insert(node_t *tree, int value) {

    if (value < (*tree).value) {
        if (!(*tree).left) {
            node_t* left = malloc(sizeof(node_t));
            left->value = value;
            (*tree).left = left;
            return;
        }
        insert((*tree).left, value);
    }

    if (value > (*tree).value) {
        if (!(*tree).right) {
            node_t* right = malloc(sizeof(node_t));
            right->value = value;
            (*tree).right = right;
            return;
        }
        insert((*tree).right, value);
    }
}

// return 1 iff value is found in tree, 0 otherwise
int binarySearch(node_t *tree, int value) {
    if ((*tree).value == value) {
        return 1;
    }

    if (value < (*tree).value) {
        if (!(*tree).left) return 0;
        return binarySearch((*tree).left, value);
    }

    if (value > (*tree).value) {
        if (!(*tree).right) return 0;
        return binarySearch((*tree).right, value);
    }

    return 0;
}

// free all dynamically allocated memory of tree
void cleanUpTree(node_t *tree) {
    if (!(*tree).left) cleanUpTree((*tree).left);
    if (!(*tree).right) cleanUpTree((*tree).right);
    free(tree);
}
