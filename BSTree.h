#include "Node.h"

class BSTree {
  public:
    BSTree() : root(nullptr) {};

    virtual std::shared_ptr<Node> insertNode(const std::string &key, int val);
    virtual int deleteNode(std::string key);
  
    std::pair<std::shared_ptr<Node>, Side> findParentLoc(const std::string &key);
    std::shared_ptr<Node> queryNode(std::string key);
    std::shared_ptr<Node> addChild(std::shared_ptr<Node> pnode, Side s, std::shared_ptr<Node> child);
    std::shared_ptr<Node> getChild(std::shared_ptr<Node> node, Side s);
    void inOrderTraverse();
    std::vector <std::shared_ptr<Node> > getChildren();
    std::vector <std::shared_ptr<Node> > getLeaves();
    
    int size();

  protected:
    std::shared_ptr<Node> root;
};

class RBTree : public BSTree {
  public:
    RBTree() { root = nullptr; };
    RBTree(Node &node);

    std::shared_ptr<Node> insertNode(const std::string &key, int val) override;
    int deleteNode(std::string key) override;

  private:
    void updateColors(std::shared_ptr<Node> node);
    bool tryRecolor(std::shared_ptr<Node> node);
    void rotateLeft(std::shared_ptr<Node> node);
    void rotateRight(std::shared_ptr<Node> node);
    bool checkColorInvariant(); // check invariant that parent of RED node should be BLACK
    bool checkDescendantBlackHeights(); // check invariant that all leaves have same BLACK height
};

