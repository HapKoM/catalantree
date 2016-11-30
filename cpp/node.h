#ifndef CATALANTREE_NODE_H
#define CATALANTREE_NODE_H

#include <gmpxx.h>

/**
 * @class Binary tree node
 */
class Node {
public:
  Node();
  Node(const Node* other);
  Node(const Node& other);
  virtual ~Node();
  Node& operator=(const Node& rhs);
  bool operator==(const Node& rhs) const;
  bool operator!=(const Node& rhs) const;
  //! left subtree
  Node* llink() const;
  //! right subtree
  Node* rlink() const;
  //! parent node
  Node* plink() const;
  //! find root node
  const Node* root() const;
  //! set right subtree (this node will become parent of "n")
  void setRlink(Node* n);
  //! set left subtree (this node will become parent of "n")
  void setLlink(Node* n);
  //! set n as parent node
  void setPlink(Node* n);
  /**
   * @brief Tree nodes count (including root node)
   */
  mpz_class size() const;
  /**
   * @brief Maximum tree depth
   */
  mpz_class depth() const;
  /**
   * @brief Width of left subtree
   */
  mpz_class lwidth() const;
  /**
   * @brief Width of right subtree
   */
  mpz_class rwidth() const;
  /**
   * @brief Width of tree
   */
  mpz_class width() const;
  /**
   * @brief Decode index "I" into binary tree with "N" nodes and return pointer to root node
   */
  static Node* decode(mpz_class I, mpz_class N);
  /**
   * @brief Encode tree "root" and return its index
   */
  static mpz_class encode(Node* root);
  /**
   * @brief Search next node in DFS order
   */
  Node* dfs_next() const;
private:
  //! Left subtree
  Node* llink_;
  //! Right subtree
  Node* rlink_;
  //! Parent node
  Node* plink_;
};

#endif //CATALANTREE_NODE_H
