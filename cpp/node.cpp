#include <iostream>

#include "node.h"
#include "math_tools.h"

Node::Node(): llink_(nullptr), rlink_(nullptr) {
}

Node::Node(const Node* other): llink_(nullptr), rlink_(nullptr) {
  if (other) {
    if (other->llink_) {
      llink_ = new Node(other->llink_);
    }
    if (other->rlink_) {
      rlink_ = new Node(other->rlink_);
    }
  }
}

Node::Node(const Node& other): llink_(nullptr), rlink_(nullptr) {
  if (other.llink_) {
    llink_ = new Node(other.llink_);
  }
  if (other.rlink_) {
    rlink_ = new Node(other.rlink_);
  }
}

Node::~Node() {
  if (llink_)
    delete llink_;
  if (rlink_)
    delete rlink_;
}

bool Node::operator==(const Node& other) const {
  bool leq = false;
  if (!llink_ && !other.llink_)
    // Both left subtrees are empty => they are equal
    leq = true;
  else if (llink_ && other.llink_) {
    // Both left subtrees are not empty => need to compare
    leq = (*(llink_) == *(other.llink_));
  } // Otherwise one left subtree is empty, other is not => they are not equal
  bool req = false;
  if (!rlink_ && !other.rlink_)
    // Both right subtrees are empty => they are equal
    req = true;
  else if (rlink_ && other.rlink_) {
    // Both right subtrees are not empty => need to compare
    req = (*(rlink_) == *(other.rlink_));
  } // Otherwise one right subtree is empty, other is not => they are not equal
  return req && leq;
}

bool Node::operator!=(const Node& other) const {
  return !(operator==(other));
}

Node* Node::llink() const {
  return llink_;
}

Node* Node::rlink() const {
  return rlink_;
}

mpz_class Node::size() const {
  mpz_class lsz(0);
  if (llink_)
    lsz = llink_->size();
  mpz_class rsz(0);
  if (rlink_)
    rsz = rlink_->size();
  return lsz + rsz + 1;
}

mpz_class Node::depth() const {
  mpz_class md(0);
  mpz_class ml(0);
  mpz_class mr(0);
  if (llink_ || rlink_)
    md = 1;
  if (llink_)
    ml = llink_->depth();
  if (rlink_)
    mr = rlink_->depth();
  if (ml > mr)
    md += ml;
  else
    md += mr;
  return md;
}

mpz_class Node::lwidth() const {
  mpz_class w(0);
  if (llink_)
    w = llink_->width() + 1;
  return w;
}

mpz_class Node::rwidth() const {
  mpz_class w(0);
  if (rlink_)
    w = rlink_->width() + 1;
  return w;
}

mpz_class Node::width() const {
  return lwidth() + rwidth();
}

Node* Node::decode(mpz_class I, mpz_class N) {
  if (N == 0)
    return nullptr;
  I %= catalan(N);
  Node* root = new Node();
  if (N == 1)
    return root;
  mpz_class NL =  N - 1;
  mpz_class NR =  0;
  mpz_class SUM = 0;
  mpz_class OLDSUM = 0;
  mpz_class K = 0;
  mpz_class CL = 0;
  mpz_class CR = 0;
  while (SUM <= I) {
    NL = N - K - 1;
    NR = K;
    CL = catalan(NL);
    CR = catalan(NR);
    OLDSUM = SUM;
    SUM += CL*CR;
    K++;
  }
  I -= OLDSUM;
  mpz_class IR = I / CL;
  mpz_class IL = I - IR*CL;
  root->llink_ = decode(IL, NL);
  root->rlink_ = decode(IR, NR);
  return root;
}

mpz_class Node::encode(Node* root) {
  if (!root)
    return 0;
  mpz_class N = root->size();
  mpz_class NL = 0;
  if (root->llink_) {
    NL = root->llink_->size();
  }
  mpz_class IL = encode(root->llink_);
  mpz_class IR = encode(root->rlink_);
  mpz_class NR = N - NL - 1;
  mpz_class I = 0;
  for (mpz_class K = 0; K < NR; ++K) {
    I += catalan(N - K - 1)*catalan(K);
  }
  I+= catalan(NL)*IR;
  I+= IL;
  return I;
}
