#ifndef CATALANTREE_NODE_H
#define CATALANTREE_NODE_H

#include <string>

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
  bool operator==(const Node& other) const;
  bool operator!=(const Node& other) const;
  Node* llink() const;
  Node* rlink() const;
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
private:
  //! Left subtree
  Node* llink_;
  //! Right subtree
  Node* rlink_;
};

#endif //CATALANTREE_NODE_H
