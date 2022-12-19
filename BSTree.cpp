#include <assert.h>
#include <memory>
#include <iostream>
#include <stack>
#include <queue>
#include "BSTree.h"

Node* BSTree::insert(const std::string& key, int val) {
  auto newNode = insertNode(root, key, val);

  return newNode;
}

Node* BSTree::remove(const std::string& key) {
  auto removedNode = removeNode(root, key);

  return removedNode; 
}

// normal BST
Node* BSTree::insertNode(Node* recurseRoot, const std::string& key, int val) {
  // auto newNode
  // need to check if 

  if (recurseRoot == nullptr) {
    auto newNode = new Node(key, val);
    treeSize += 1;
    if (root == nullptr) {
      root = newNode;
    }

    return newNode;
  }
  

  if (key < recurseRoot->key) {
    recurseRoot->left = insertNode(recurseRoot->left, key, val);
    recurseRoot->left->parent = recurseRoot;
  } else if (key > recurseRoot->key) {
    recurseRoot->right = insertNode(recurseRoot->right, key, val);
    recurseRoot->right->parent = recurseRoot;
  } else {
    recurseRoot->val = val;
  }

  return recurseRoot;
}

Node* BSTree::findMinNode(Node* root) {
  // find minimum node in the subtree with root
  auto ptr = root;

  while (ptr->left != nullptr) {
    ptr = ptr->left;
  }
  return ptr;
}

Node* BSTree::removeNode(Node* recurseRoot, const std::string& key) {
  if (root == nullptr) {
    return root;
  }

  if (key > recurseRoot->key) {
    recurseRoot->right = removeNode(recurseRoot->right, key);
    
    return recurseRoot;
  } else if (key < recurseRoot->key) {
    recurseRoot->left = removeNode(recurseRoot->left, key);
    return recurseRoot;
  }

  // if we get here, root is the node to be removed
  if (recurseRoot->left == nullptr) {
    auto temp = recurseRoot->right;
    treeSize -= 1;
    delete recurseRoot;
    return temp;
  } else if (recurseRoot->right == nullptr) {
    auto temp = recurseRoot->left;
    treeSize -= 1;
    delete recurseRoot;
    return temp;
  } 
  // both left and right exists
  auto nextNode = findMinNode(recurseRoot->right);
  recurseRoot->right = removeNode(recurseRoot->right, nextNode->key);
  return nextNode;
}

Node* BSTree::findNode(const std::string &qkey) {
  Node* res, *node, *left, *right;
  string key;

  if (root == nullptr) {
    return nullptr;
  }

  node = root;

  while (true) {
    if (node == nullptr) {
      cerr << "Node with key " << key << " not found" << endl;
      // throw NodeNotFoundException(key);
    }

    key = node->key;
    left = node->left;
    right = node->right;

    if (qkey < key)
      node = left;
    else if (qkey > key)
      node = right;
    else {
      return node;
    }
  }
  return nullptr;
}

void BSTree::printNode(Node* node) {
  std::cout << "key: " << node->key << ",value: " << node->val;
}

void BSTree::inOrderTraverse() {
  if (root == nullptr) {
    std::cout << "Nothing in the BST" << std::endl;
    return;
  }

  std::stack<Node*> backtrack;
  Node* curr, *node, *child;

  curr = root;

  while (curr != nullptr) {
    backtrack.push(curr);
    curr = curr->left;
  }

  while (backtrack.size() > 0) {
    curr = backtrack.top();
    backtrack.pop();

    printNode(curr);
    cout << endl;

    if (curr->right != nullptr) {
      curr = curr->right;

      while (curr != nullptr) {
        backtrack.push(curr);
        curr = curr->left;
      } 
    }
  }
}

// std::vector<std::shared_ptr<Node> > BSTree::getChildren() {
//   std::vector<std::shared_ptr<Node> > children;
//   std::queue<std::shared_ptr<Node> > q;

//   if (root == nullptr)
//     return children;

//   q.push(root);
//   while (q.size()) {
//     auto ele = q.front();
//     q.pop();

//     children.push_back(ele);
//     if (ele->leftChild != nullptr)
//       q.push(ele->leftChild);

//     if (ele->rightChild != nullptr)
//       q.push(ele->rightChild);
//   }

//   return children;
// }

// std::vector<std::shared_ptr<Node> > BSTree::getLeaves() {
//   auto children = getChildren();
//   std::vector<std::shared_ptr<Node> > leaves;

//   for (auto child : children) {
//     if (child->isLeafNode())
//       leaves.push_back(child);
//   }

//   return leaves;
// }

// int BSTree::size() {
//   return getChildren().size();
// }

// // Red Black Tree implementation
// std::shared_ptr<Node> RBTree::insertNode(const std::string key, int val) {
//   auto newNode = std::make_shared<Node>(key, val, RED);

//   if (root == nullptr) {
//     root = newNode;
//     return root;
//   }

//   auto insertLoc = findParentLoc(key);
//   auto child = addChild(insertLoc.first, insertLoc.second, newNode);

//   updateColors(child);

//   // std::cout << "node with key " << key << " inserted with parent " << insertLoc.first->getkey() << std::endl;
//   checkColorInvariant();
//   checkDescendantBlackHeights();

//   return child;
// }

// void RBTree::updateColors(std::shared_ptr<Node> node) {
//   auto parent = node->parent;

//   while (node != root && parent->color == RED) {
//     // case 1 and 4 are recolorable situations
//     if (!tryRecolor(node)) { 
//       // use rotation to maintain invariant
//       if (parent->isLeftChild()) {
//         if (node->isRightChild()) { // case 2
//           rotateLeft(parent);
//           updateColors(parent);
//         }
//         // case 3
//         rotateRight(parent->parent);
//         updateColors(parent);
//       } else {
//         if (node->isLeftChild()) {
//           rotateRight(parent); // case 5
//           updateColors(parent);
//         }
//         // case 6
//         rotateLeft(parent->parent);
//         updateColors(parent);
//       }
//     }
//     // root always have to color BLACK
//     root->color = BLACK;
//   }
// }

// int RBTree::delete(std::string key) {
//   return 0;
// }

// bool RBTree::tryRecolor(std::shared_ptr<Node> node) {
//   /*
//     attempt to recolor parent and sibling's color in order to maintain the
//     invariance of not having consecutive RED nodes.
//   */
//   // recolor

//   auto parent = node->parent;
//   auto uncle = node->getUncle();
//   if (parent && !uncle) {
//     parent->color = RED;
//     node->color = BLACK;
//     return true;
//   } else if (parent && uncle && uncle->color == RED) {
//     parent->color = RED;
//     uncle->color = BLACK;
//     node->color = BLACK;
//     return true;
//   }

//   return false;
// }

// void RBTree::rotateLeft(std::shared_ptr<Node> node) {
//   auto rightChild = node->rightChild;
//   auto subTree = rightChild->leftChild;

//   node->rightChild = subTree;
//   node->parent = rightChild;
//   rightChild->leftChild = node;
//   rightChild->parent = nullptr;

//   if (node == root)
//     root = rightChild;
// }

// void RBTree::rotateRight(std::shared_ptr<Node> node) {
//   auto leftChild = node->leftChild;
//   auto subTree = leftChild->rightChild;

//   node->leftChild = subTree;
//   node->parent = leftChild;
//   leftChild->rightChild = node;
//   leftChild->parent = nullptr;
  
//   if (node == root)
//     root = leftChild;
// }

// bool RBTree::checkColorInvariant() {
//   auto children = getChildren();

//   for (auto child : children) {
//      if (child->color == RED) {
//        auto parent = child->parent;
//        if (parent) {
//          if (parent->color != BLACK)
//            return false;
//          assert(parent->color == BLACK);
//        }
//      }
//   }
//   return true;
// }

// bool RBTree::checkDescendantBlackHeights() {
//   auto leaves = getLeaves();

//   int bh = -1;
//   for (auto leaf : leaves) {
//     if (bh < 0) {
//       bh = leaf->blackHeight();
//     }

//     if (bh != leaf->blackHeight())
//       return false;
//     assert(bh == leaf->blackHeight());
//   }
//   return true;
// }
