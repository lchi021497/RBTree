#include <assert.h>
#include <memory>
#include <iostream>
#include <stack>
#include <queue>
#include "Node.h"

// constructors
Node::Node(std::string key) : key(key), val(0), color(NONE) { initNode(); }
Node::Node(std::string key, int val) : key(key), val(val), color(NONE) { initNode(); }
Node::Node(std::string key, int val, Color color) : key(key), val(val), color(color) { initNode(); }

void Node::initNode() {
  parent = nullptr;
  left_child = nullptr;
  right_child = nullptr;
}

// getter methods
std::shared_ptr<Node> Node::leftChild() {
  return left_child;
}

std::shared_ptr<Node> Node::rightChild() {
  return right_child;
}

std::shared_ptr<Node> Node::sibling() {
  if (parent == nullptr)
    return nullptr;

  if (this == parent->leftChild().get())
    return parent->rightChild();
  return parent->leftChild();
}

std::shared_ptr<Node> Node::getParent() {
  return parent;
}

// util methods
bool Node::hasLeftChild() {
  return left_child != nullptr;
}

bool Node::hasRightChild() {
  return right_child != nullptr;
}

void Node::setParent(std::shared_ptr<Node> parent) { this->parent = parent; }

bool Node::isLeftChild() {
  if (parent == nullptr) // is root node
    return false;

  auto lc = this->parent->leftChild(); 
  return lc.get() == this; 
}

bool Node::isRightChild() { 
  if (parent == nullptr)
    return false;

  auto rc = this->parent->rightChild();
  return rc.get() == this; 
}

std::shared_ptr<Node> Node::getGrandParent() {
  if (parent == nullptr)
    return nullptr;
  return parent->getParent();
}

std::shared_ptr<Node> Node::getUncle() {
  if (parent == nullptr || parent->getParent() == nullptr)
    return nullptr;
  return parent->sibling();
}

int Node::height() {
  // height of node to root, not including node itself
  std::shared_ptr<Node> node(this); 

  int h = 0;
  do {
    node = node->getParent();
    h++;
  } while (node);

  return h;
}

int Node::blackHeight() {
  // height of node to root that are BLACK, not including node itself
  auto node = this;
  
  int bh = 0;

  node = node->getParent().get();
  while (node) {
    if (node->getcolor() == BLACK)
      bh++;
    node = node->getParent().get();
  }

  return bh;
}

void Node::setLeftChild(std::shared_ptr<Node> lc) { this->left_child = lc; }
void Node::setRightChild(std::shared_ptr<Node> rc) { this->right_child = rc; }



