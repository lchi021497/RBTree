#include <stdio.h>
using namespace std;

#ifndef _NODE_
#define _NODE_
enum Color {
  RED, BLACK, NONE
};

enum Side {
  LEFT, RIGHT
};

struct Node {
  // contructors
  Node();
  Node(std::string key);
  Node(std::string key, int val);
  Node(std::string key, int val, Color color);
  void initNode(); // initialize all pointers

  Node* sibling();
  
  bool isLeftChild();
  bool isRightChild();
  bool isLeafNode() { return left == nullptr && right == nullptr; }
  int height();
  int blackHeight();

  Node* getGrandParent();
  Node* getUncle();

  Node* parent;
  Node* left;
  Node* right;
  std::string key;
  int val;
  Color color;
};

struct NoParentException : public exception {
   const char * what () const throw () {
      return "accessing parent in node with no parent";
   }
};

#endif