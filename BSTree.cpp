#include <assert.h>
#include <memory>
#include <iostream>
#include <stack>
#include <queue>
#include <utility>
#include "BSTree.h"

Node* BSTree::insert(const std::string& key, int val) {
  auto res = insertNode(root, key, val);

  return res.second;
}

Node* BSTree::remove(const std::string& key) {
  auto removedNode = removeNode(root, key);

  return removedNode; 
}

// normal BST
pair<Node*, Node*> BSTree::insertNode(Node* recurseRoot, const std::string& key, int val) {
  // auto newNode
  // need to check if 

  if (recurseRoot == nullptr) {
    auto newNode = new Node(key, val, RED);
    treeSize += 1;
    if (root == nullptr) {
      root = newNode;
    }

    return make_pair(newNode, newNode);
  }
  
  pair<Node*, Node*> res; 
  if (key < recurseRoot->key) {
    res = insertNode(recurseRoot->left, key, val);
    recurseRoot->left = res.first;
    recurseRoot->left->parent = recurseRoot;
  } else if (key > recurseRoot->key) {
    res = insertNode(recurseRoot->right, key, val);
    recurseRoot->right = res.first; 
    recurseRoot->right->parent = recurseRoot;
  } else {
    recurseRoot->val = val;
  }

  return make_pair(recurseRoot, res.second);
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

// void BSTree::printNode(Node* node) {
//   std::cout << "key: " << node->key << ",value: " << node->val;
// }

vector<Node *> BSTree::inOrderTraverse() {
  vector<Node *> flattened;
  if (root == nullptr) {
    cout << "Nothing in the BST" << endl;
    return flattened;
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

    // printNode(curr);
    // cout << endl;
    flattened.push_back(curr);

    if (curr->right != nullptr) {
      curr = curr->right;

      while (curr != nullptr) {
        backtrack.push(curr);
        curr = curr->left;
      } 
    }
  }

  return flattened;
}


// Red Black Tree implementation
Node* RBTree::insert(const std::string& key, int val) {
  auto newNode = BSTree::insert(key, val);
  if (newNode == NULL)
    return newNode;
  // assert(newNode != NULL);
  // cout << "inserting node " << *newNode << endl;

  if (newNode)
    updateColors(newNode);

  // checkColorInvariant();
  // checkPointers();
  // checkDescendantBlackHeights();

  return newNode;
}

Node* RBTree::remove(const std::string& key) {
  return 0;
}

//  std::vector<std::shared_ptr<Node> > BSTree::getChildren() {
//    std::vector<std::shared_ptr<Node> > children;
//    std::queue<std::shared_ptr<Node> > q;

//    if (root == nullptr)
//      return children;

//    q.push(root);
//    while (q.size()) {
//      auto ele = q.front();
//      q.pop();

//      children.push_back(ele);
//      if (ele->leftChild != nullptr)
//        q.push(ele->leftChild);

//      if (ele->rightChild != nullptr)
//        q.push(ele->rightChild);
//    }

//    return children;
//  }

 std::vector<Node *> BSTree::getLeaves() {
   auto children = inOrderTraverse();
   std::vector<Node *> leaves;

   for (auto child : children) {
     if (child->isLeafNode())
       leaves.push_back(child);
   }

   return leaves;
 }

void RBTree::updateColors(Node* node) {
  // cout << "updating colors... for node " << *node <<  endl;

  if (node == root) {
    // root always have to color BLACK
    root->color = BLACK;
    return;
  }
  auto parent = node->parent;
  auto recurseRoot = node->getGrandParent();
  if (node != root && node->color == RED && parent->color == RED) {
    // case 1 and 4 are recolorable situations
    if (!tryRecolor(node)) { 
      // use rotation to maintain invariant
      
      if (parent->isLeftChild()) {
        if (node->isRightChild()) { // case 2
          auto rotatedParent = rotateLeft(parent);
          recurseRoot = rotatedParent->parent;
        }

        // case 3
        recurseRoot = rotateRight(recurseRoot);
        recurseRoot->color = BLACK;
        recurseRoot->right->color = RED;
        
        updateColors(recurseRoot);
      } else {
        if (node->isLeftChild()) {
          auto rotatedParent = rotateRight(parent); // case 5
          recurseRoot = rotatedParent->parent; 
        }

        // case 6
        recurseRoot = rotateLeft(recurseRoot);
        recurseRoot->color = BLACK;
        recurseRoot->left->color = RED;
        
        updateColors(recurseRoot);
      }
    } else {
      updateColors(recurseRoot);
    }
  }
}

bool RBTree::tryRecolor(Node* node) {
  /*
    attempt to recolor parent and sibling (uncle)'s color in order
    to maintain the invariance of not having consecutive RED nodes.
  */
  // recolor
  // cout << "try color at node " << *node << endl;
  auto parent = node->parent;
  auto uncle = node->getUncle();
  auto grandparent = node->getGrandParent();
  if (parent->color == BLACK)
    return true;

  if (parent && !uncle && parent->color == RED) {
    parent->color = BLACK;
    return true;
  } else if (parent && uncle && parent->color == RED && uncle->color == RED) {
    parent->color = BLACK;
    uncle->color = BLACK;
    grandparent->color = RED;
    
    return true;
  }

  return false;
}

Node *RBTree::rotateLeft(Node* node) {
  // cout << "ROTATE LEFT AT node " << *node << endl;
  auto rightChild = node->right;
  auto subTree = rightChild->left;

  rightChild->left = node;
  rightChild->parent = node->parent;
  if (node->parent) {
    if (node->isLeftChild()) {
      node->parent->left = rightChild;
    } else {
      node->parent->right = rightChild;
    }
  }
  node->right = subTree;
  if (subTree)
    subTree->parent = node;
  node->parent = rightChild;

  if (node == root)
    root = rightChild;
  
  return rightChild;
}

Node *RBTree::rotateRight(Node* node) {
  // cout << "ROTATE RIGHT AT node " << *node << endl;
  auto leftChild = node->left;
  auto subTree = leftChild->right;

  leftChild->right = node;
  leftChild->parent = node->parent;
  if (node->parent) {
    if (node->isLeftChild()) {
      node->parent->left = leftChild;
    } else {
      node->parent->right = leftChild;
    }
  }
  node->left = subTree;
  if (subTree)
    subTree->parent = node;
  node->parent = leftChild;
  
  if (node == root)
    root = leftChild;
  
  return leftChild;
}

void RBTree::checkPointers() {
  auto nodes = inOrderTraverse();

  for (auto node : nodes) {
    if (node->left) {
      // check pointers
      assert(node->left->parent == node);
    }
    if (node->right) {
      assert(node->right->parent == node);
    }
  }
}

bool RBTree::checkColorInvariant() {
  auto children = inOrderTraverse();

  for (auto child : children) {
     if (child->color == RED) {
       auto parent = child->parent;
       if (parent) {
         assert(parent->color == BLACK);
       }
     }
  }
  return true;
}

bool RBTree::checkDescendantBlackHeights() {
  auto leaves = getLeaves();

  int bh = -1;
  for (auto leaf : leaves) {
    if (bh < 0) {
      bh = leaf->blackHeight();
    }

    if (bh != leaf->blackHeight())
      return false;
    assert(bh == leaf->blackHeight());
  }
  return true;
}
