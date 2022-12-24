#include "Node.h"

#ifndef _BSTREE_
#define _BSTREE_
class BSTree {
  public:
    BSTree() : treeSize(0), root(nullptr) {}
    virtual ~BSTree() {}

    virtual Node* insert(const std::string& key, int val);
    virtual Node* remove(const std::string& key);

    Node* getRoot() { return root; }
    Node* findMinNode(Node* root);
    Node* findNode(const std::string &key);
    
    vector<Node *> inOrderTraverse();
    vector<Node *> getLeaves();
    
    int size() { return treeSize; };

  protected:
    Node* root;
    int treeSize;

    pair<Node*, Node*> insertNode(Node* recurseRoot, const std::string& key, int val);
    Node* removeNode(Node* recurseRoot, const std::string& key);
};

class RBTree : public BSTree {
  public:
    RBTree() { root = nullptr; };
    RBTree(Node &node);

    Node *insert(const std::string& key, int val) override;
    Node *remove(const std::string& key) override;

  private:
    void updateColors(Node* node);
    bool tryRecolor(Node* node);
    Node *rotateLeft(Node* node);
    Node *rotateRight(Node* node);
    void checkPointers();
    bool checkColorInvariant(); // check invariant that parent of RED node should be BLACK
    bool checkDescendantBlackHeights(); // check invariant that all leaves have same BLACK height
};

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