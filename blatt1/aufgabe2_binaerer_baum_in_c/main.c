#include <stdio.h>

#include "tree.h"

int main(void) {
  node_t* root = createTree(16);

  printf("%d\n", (*root).value);

  insert(root,  8);
  insert(root,  4);
  insert(root, 15);
  insert(root, 42);
  insert(root, 23);

  printf("%d\n", (*root).left->value);
  printf("%d\n", (*root).left->left->value);

  if (binarySearch(root, 11)) {
    printf("11 found in tree\n");
  }
  if (binarySearch(root, 23)) {
    printf("23 found in tree\n");
  }
  if (binarySearch(root, 42)) {
    printf("42 found in tree\n");
  }
  
  cleanUpTree(root);
  
  return 0;
}

