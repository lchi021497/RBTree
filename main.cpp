#include <assert.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include "Node.h"
#include "BSTree.h"

int main() {
  std::ifstream ifs("input.txt");

  BSTree tree;
  // RBTree tree;
  
  int op;
  while(!ifs.eof()) {
    ifs >> op;
    cout << "op: " << op << endl;
  
    std::string key;
    int val;
    if (op == 1) {
      ifs >> key >> val;
      cout << "insert key " << key << " with val " << val << endl;
      tree.insert(tree.getRoot(), key, val);
    } else if (op == 2) {
      ifs >> key;
      cout << "remove key " << key << endl;
      tree.remove(tree.getRoot(), key);
    }
       
    std::cout << "tree size: " << tree.size() << std::endl;
    // std::cout << inode->height() << std::endl;
  }
  cout << "finish inserting" << endl;
  tree.inOrderTraverse();
}

