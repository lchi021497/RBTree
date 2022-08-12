Implementation of Red-Black (Self-Balancing) Binary Search Tree

Classes:
- Nodes
- BSTree
- RBTree (inherits BSTree)

Node:
  Member Functions:
    - getParent();
    - getGrandParent();
    - getUncle();
    - getColor();

BSTree:
  Member Functions:
    - int height(Node *node): returns the height of node in the tree. 0 if node is root, and
          throws ValueException if node is NULL.
    - int Insert(Key k, Value v): searches for node in tree with key k, change value if node is found.
          If key is not found, insert a new node with key k and value v.
    - int Remove(Key k): remove node in the tree with key k. Returns 1 if successful, 0 else.
    - Node *Query(Key k): find node with key k. Returns NULL, if does not exist.

RBTree:
  Member Functions:
    - rotateLeft(Node &node): opposite of rotateRight.
    - rotateRight(Node &node): promote the node to it's parent's position and move one of its child
          to be its sibling's child.
    - recolor(Node &node, Color color): recolor node with color




