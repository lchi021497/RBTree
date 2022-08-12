#include <assert.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include "BSTree.h"

int main() {
  std::ifstream ifs("input.txt");

  BSTree tree;
  // RBTree tree;
  std::string key;
  int val;

  while(ifs >> key >> val) {
    auto inode = tree.insertNode(key, val);
    
    //std::cout << "key: " << key << ", val: " << val << ", color: " << inode->getcolor() << std::endl;
    std::cout << "tree size: " << tree.size() << std::endl;
    // std::cout << inode->height() << std::endl;
  }
  tree.inOrderTraverse();

}

