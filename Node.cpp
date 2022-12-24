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
  left = nullptr;
  right = nullptr;
}

Node* Node::sibling() {
  if (parent == nullptr) // no parent
    throw NoParentException();

  if (this == parent->left)
    return parent->right;
  return parent->left;
}

bool Node::isLeftChild() {
  if (parent == nullptr) // is root node
    throw NoParentException();

  return this->parent->left == this; 
}

bool Node::isRightChild() { 
  if (parent == nullptr)
    throw NoParentException();
  return this->parent->right == this; 
}

Node* Node::getGrandParent() {
  if (parent == nullptr)
    throw NoParentException();
  return parent->parent;
}

Node* Node::getUncle() {
  if (parent == nullptr || parent->parent == nullptr)
    throw NoParentException();
  return parent->sibling();
}

int Node::height() {
  // height of node to root, not including node itself
  if (this->parent == nullptr) {
    return 1;
  }

  return 1 + this->parent->height();
}

int Node::blackHeight() {
  // height of node to root that are BLACK, not including node itself  
  if (this->color == BLACK)
    return 1 + this->parent->blackHeight();
  return this->parent->blackHeight();
}

ostream& operator<<(ostream& os, const Node& node) {
  os << "Node(key: " << node.key << ", value: " << node.val << ", color: " << node.color << ")" << endl;
  return os;
}
