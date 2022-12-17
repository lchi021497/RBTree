#include <assert.h>
#include <memory>
#include <iostream>
#include <stack>
#include <queue>
#include "BSTree.h"

int BSTree::deleteNode(std::string key) {
  auto loc = findParentLoc(key);
  auto delete_node = getChild(loc.first, loc.second);
  auto parent = delete_node->getParent();
  if (delete_node == nullptr)
    return -1;
  else if (delete_node == root)
    root = nullptr;
  else if (delete_node->isLeftChild())
    parent->setLeftChild(nullptr);
  else
    parent->setRightChild(nullptr);
  return 1;
}

std::pair<std::shared_ptr<Node>, Side> BSTree::findParentLoc(const std::string &key) {
  std::string pkey;
  std::shared_ptr<Node> node, left, right;
  std::pair<std::shared_ptr<Node>, Side> res;

  if (root == nullptr) {
    res = std::pair<std::shared_ptr<Node>, Side>(nullptr, LEFT);
    return res;
  }

  node = root;

  while (true) {
    pkey = node->getkey();
    left = node->leftChild();
    right = node->rightChild();

    if (left && key < pkey)
      node = left;
    else if (right && key > pkey)
      node = right;
    else {
      // found the node to hang new node off of
      if (key == pkey) {
        if (node->isLeftChild())
          res = std::pair<std::shared_ptr<Node>, Side>(node->getParent(), LEFT);
        else
          res = std::pair<std::shared_ptr<Node>, Side>(node->getParent(), RIGHT);
      }
      else if (key < pkey)
        res = std::pair<std::shared_ptr<Node>, Side>(node, LEFT);
      else
        res = std::pair<std::shared_ptr<Node>, Side>(node, RIGHT);

      break;
    }
  }

  return res;
}


std::shared_ptr<Node> BSTree::queryNode(std::string key) {
  std::string pkey;
  std::shared_ptr<Node> node, left, right;

  if (root == nullptr)
    return nullptr;

  node = root;
  left = node->leftChild();
  right = node->rightChild();
 
  while (left != nullptr || right != nullptr) { 
    pkey = node->getkey();
    left = node->leftChild();
    right = node->rightChild();

    if (key < pkey) 
      node = left;
    else if (key > pkey) 
      node = right;
    else
      return node;
  }

  return nullptr;
}

std::shared_ptr<Node> BSTree::addChild(std::shared_ptr<Node> pnode, Side s, std::shared_ptr<Node> child) {
  auto pkey = pnode->getkey();
    
  child->setParent(pnode);
  if (s == LEFT) {
    pnode->setLeftChild(child);
  } else {
    pnode->setRightChild(child);
  }

  return child;
}

std::shared_ptr<Node> BSTree::getChild(std::shared_ptr<Node> node, Side s) {
  if (node == nullptr)
    return nullptr;
  
  if (s == LEFT)
    return node->leftChild();
  return node->rightChild();    
}

void BSTree::inOrderTraverse() {
  if (root == nullptr) {
    std::cout << "Nothing in the BST" << std::endl;
    return;
  }

  std::stack<std::shared_ptr<Node> > backtrack;
  std::shared_ptr<Node> curr, node, child;

  curr = root;

  while (curr != nullptr || backtrack.size() > 0) {
    if (curr != nullptr) {
      backtrack.push(curr);
      curr = curr->leftChild();
    }

    if (curr == nullptr && backtrack.size() > 0) {
      node = backtrack.top();
      backtrack.pop();

      std::cout << "key: " << node->getkey() << ",value: " << node->getvalue() << std::endl;
      curr = node->rightChild();
    }
  }
}

std::vector<std::shared_ptr<Node> > BSTree::getChildren() {
  std::vector<std::shared_ptr<Node> > children;
  std::queue<std::shared_ptr<Node> > q;

  if (root == nullptr)
    return children;

  q.push(root);
  while (q.size()) {
    auto ele = q.front();
    q.pop();

    children.push_back(ele);
    if (ele->hasLeftChild())
      q.push(ele->leftChild());

    if (ele->hasRightChild())
      q.push(ele->rightChild());
  }

  return children;
}

std::vector<std::shared_ptr<Node> > BSTree::getLeaves() {
  auto children = getChildren();
  std::vector<std::shared_ptr<Node> > leaves;

  for (auto child : children) {
    if (child->isLeafNode())
      leaves.push_back(child);
  }

  return leaves;
}

int BSTree::size() {
  return getChildren().size();
}

std::shared_ptr<Node> RBTree::insertNode(const std::string &key, int val) {
  auto newNode = std::make_shared<Node>(key, val, RED);

  if (root == nullptr) {
    root = newNode;
    return root;
  }

  auto insertLoc = findParentLoc(key);
  auto child = addChild(insertLoc.first, insertLoc.second, newNode);

  updateColors(child);

  // std::cout << "node with key " << key << " inserted with parent " << insertLoc.first->getkey() << std::endl;
  checkColorInvariant();
  checkDescendantBlackHeights();

  return child;
}

void RBTree::updateColors(std::shared_ptr<Node> node) {
  auto parent = node->getParent();

  while (node != root && parent->getcolor() == RED) {
    // case 1 and 4 are recolorable situations
    if (!tryRecolor(node)) { 
      // use rotation to maintain invariant
      if (parent->isLeftChild()) {
        if (node->isRightChild()) { // case 2
          rotateLeft(parent);
          updateColors(parent);
        }
        // case 3
        rotateRight(parent->getParent());
        updateColors(parent);
      } else {
        if (node->isLeftChild()) {
          rotateRight(parent); // case 5
          updateColors(parent);
        }
        // case 6
        rotateLeft(parent->getParent());
        updateColors(parent);
      }
    }
    // root always have to color BLACK
    root->setColor(BLACK);
  }
}

int RBTree::deleteNode(std::string key) {
  return 0;
}

bool RBTree::tryRecolor(std::shared_ptr<Node> node) {
  /*
    attempt to recolor parent and sibling's color in order to maintain the
    invariance of not having consecutive RED nodes.
  */
  // recolor

  auto parent = node->getParent();
  auto uncle = node->getUncle();
  if (parent && !uncle) {
    parent->setColor(RED);
    node->setColor(BLACK);
    return true;
  } else if (parent && uncle && uncle->getcolor() == RED) {
    parent->setColor(RED);
    uncle->setColor(BLACK);
    node->setColor(BLACK);
    return true;
  }

  return false;
}

void RBTree::rotateLeft(std::shared_ptr<Node> node) {
  auto rightChild = node->rightChild();
  auto subTree = rightChild->leftChild();

  node->setRightChild(subTree);
  node->setParent(rightChild);
  rightChild->setLeftChild(node);
  rightChild->setParent(nullptr);

  if (node == root)
    root = rightChild;
}

void RBTree::rotateRight(std::shared_ptr<Node> node) {
  auto leftChild = node->leftChild();
  auto subTree = leftChild->rightChild();

  node->setLeftChild(subTree);
  node->setParent(leftChild);
  leftChild->setRightChild(node);
  leftChild->setParent(nullptr);
  
  if (node == root)
    root = leftChild;
}

bool RBTree::checkColorInvariant() {
  auto children = getChildren();

  for (auto child : children) {
     if (child->getcolor() == RED) {
       auto parent = child->getParent();
       if (parent) {
         if (parent->getcolor() != BLACK)
           return false;
         assert(parent->getcolor() == BLACK);
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
