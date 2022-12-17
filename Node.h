#include <stdio.h>
using namespace std;

enum Color {
  RED, BLACK, NONE
};

enum Side {
  LEFT, RIGHT
};

class Node {
  public:
    // contructors
    Node(std::string key);
    Node(std::string key, int val);
    Node(std::string key, int val, Color color);
    void initNode();

    std::string getkey() { return key; }
    int getvalue() { return val; }
    Color getcolor() { return color; }
    void setColor(Color c) { color = c; }
    void updateVal(int val) { val = val; }

    std::shared_ptr<Node> leftChild();
    std::shared_ptr<Node> rightChild();
    std::shared_ptr<Node> sibling();
    std::shared_ptr<Node> getParent();
    
    bool hasLeftChild();
    bool hasRightChild();
    void setParent(std::shared_ptr<Node> parent);
    bool isLeftChild();
    bool isRightChild();
    bool isLeafNode() { return left_child == nullptr && right_child == nullptr; }
    int height();
    int blackHeight();
    void setLeftChild(std::shared_ptr<Node> lc); 
    void setRightChild(std::shared_ptr<Node> rc);
    std::shared_ptr<Node> getGrandParent();
    std::shared_ptr<Node> getUncle();
  
  private:
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> left_child, right_child;
    std::string key;
    int val;
    Color color;
};


