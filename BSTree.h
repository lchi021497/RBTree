#include "Node.h"

#ifndef _BSTREE_
#define _BSTREE_
class BSTree {
  public:
    BSTree() : treeSize(0), root(nullptr) {}
    virtual ~BSTree() {}

    Node* insert(Node* recurseRoot, const std::string key, int val);
    Node* remove(Node* node, std::string key);

    Node* getRoot() { return root; }
    Node* findMinNode(Node* root);
    Node* findParentNode(const std::string &key);
    Node* findNode(const std::string &key);
    Node* queryNode(std::string key);
    void inOrderTraverse();
    // std::vector <std::shared_ptr<Node> > getChildren();
    // std::vector <std::shared_ptr<Node> > getLeaves();
    
    int size() { return treeSize; };

  protected:
    Node* root;
    int treeSize;
};

// class RBTree : public BSTree {
//   public:
//     RBTree() { root = nullptr; };
//     RBTree(Node &node);

//     std::shared_ptr<Node> insertNode(const std::string key, int val) override;
//     int remove(std::string key) override;

//   private:
//     void updateColors(std::shared_ptr<Node> node);
//     bool tryRecolor(std::shared_ptr<Node> node);
//     void rotateLeft(std::shared_ptr<Node> node);
//     void rotateRight(std::shared_ptr<Node> node);
//     bool checkColorInvariant(); // check invariant that parent of RED node should be BLACK
//     bool checkDescendantBlackHeights(); // check invariant that all leaves have same BLACK height
// };


// class NodeNotFoundException : std::exception {
//   public:
//   NodeNotFoundException(string key) : key(key) { }
//   const char * what () const noexcept override {
//     return "node with ";
//   }
  
//   private:
//   string key;
// };

#endif