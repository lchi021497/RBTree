#include <assert.h>
#include <memory>
#include <iostream>
#include <exception>
#include <stack>
#include <queue>
#include "Node.h"

// constructors
Node::Node() { initNode(); }
Node::Node(std::string key) : key(key), color(NONE) { initNode(); }
Node::Node(std::string key, int val) : key(key), val(val), color(NONE) { initNode(); }
Node::Node(std::string key, int val, Color color) : key(key), val(val), color(color) { initNode(); }

void Node::initNode() {
  // initialize pointers
  parent = nullptr;
  leftChild = nullptr;
  rightChild = nullptr;
}

std::shared_ptr<Node> Node::sibling() {
  if (parent == nullptr) // no parent
    throw NoParentException();

  if (this == parent->leftChild.get())
    return parent->rightChild;
  return parent->leftChild;
}

bool Node::isLeftChild() {
  if (parent == nullptr) // is root node
    throw NoParentException();

  auto lc = this->parent->leftChild; 
  return lc.get() == this; 
}

bool Node::isRightChild() { 
  if (parent == nullptr)
    throw NoParentException();

  auto rc = this->parent->rightChild;
  return rc.get() == this; 
}

std::shared_ptr<Node> Node::getGrandParent() {
  if (parent == nullptr)
    throw NoParentException();
  return parent->parent;
}

std::shared_ptr<Node> Node::getUncle() {
  if (parent == nullptr || parent->parent == nullptr)
    throw NoParentException();
  return parent->sibling();
}

int Node::height() {
  // height of node to root, not including node itself
  std::shared_ptr<Node> node(this); 

  int h = 0;
  do {
    node = node->parent;
    h++;
  } while (node);

  return h;
}

int Node::blackHeight() {
  // height of node to root that are BLACK, not including node itself
  auto node = this;
  
  int bh = 0;

  node = node->parent.get();
  while (node) {
    if (node->color == BLACK)
      bh++;
    node = node->parent.get();
  }

  return bh;
}




