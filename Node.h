#include <stdio.h>
using namespace std;

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

  std::shared_ptr<Node> sibling();
  
  bool isLeftChild();
  bool isRightChild();
  bool isLeafNode() { return leftChild == nullptr && rightChild == nullptr; }
  int height();
  int blackHeight();

  std::shared_ptr<Node> getGrandParent();
  std::shared_ptr<Node> getUncle();

  std::shared_ptr<Node> parent;
  std::shared_ptr<Node> leftChild, rightChild;
  std::string key;
  int val;
  Color color;
};

struct NoParentException : public exception {
   const char * what () const throw () {
      return "accessing parent in node with no parent";
   }
};
