#include <iostream>

#include "node.h"
#include "math_tools.h"

Node::Node(): llink_(nullptr), rlink_(nullptr), plink_(nullptr) {
}

Node::Node(const Node* other): llink_(nullptr), rlink_(nullptr), plink_(nullptr) {
  if (other) {
    if (other->llink_) {
      llink_ = new Node(other->llink_);
      llink_->plink_ = this;
    }
    if (other->rlink_) {
      rlink_ = new Node(other->rlink_);
      rlink_->plink_ = this;
    }
  }
}

Node::Node(const Node& other): llink_(nullptr), rlink_(nullptr), plink_(nullptr) {
  if (other.llink_) {
    llink_ = new Node(other.llink_);
    llink_->plink_ = this;
  }
  if (other.rlink_) {
    rlink_ = new Node(other.rlink_);
    rlink_->plink_ = this;
  }
}

Node::~Node() {
  if (llink_) {
    delete llink_;
    llink_ = nullptr;
  }
  if (rlink_) {
    delete rlink_;
    rlink_ = nullptr;
  }
}

Node& Node::operator=(const Node& rhs) {
  // Self assignment check (Scott Meyers)
  if (this == &rhs) return *this;
  llink_ = nullptr;
  rlink_ = nullptr;
  if (rhs.llink_) {
    llink_ = new Node(rhs.llink_);
    llink_->plink_ = this;
  }
  if (rhs.rlink_) {
    rlink_ = new Node(rhs.rlink_);
    rlink_->plink_ = this;
  }
  return *this;
}

bool Node::operator==(const Node& rhs) const {
  bool leq = false;
  if (!llink_ && !rhs.llink_)
    // Both left subtrees are empty => they are equal
    leq = true;
  else if (llink_ && rhs.llink_) {
    // Both left subtrees are not empty => need to compare
    leq = (*(llink_) == *(rhs.llink_));
  } // Otherwise one left subtree is empty, other is not => they are not equal
  bool req = false;
  if (!rlink_ && !rhs.rlink_)
    // Both right subtrees are empty => they are equal
    req = true;
  else if (rlink_ && rhs.rlink_) {
    // Both right subtrees are not empty => need to compare
    req = (*(rlink_) == *(rhs.rlink_));
  } // Otherwise one right subtree is empty, other is not => they are not equal
  return req && leq;
}

bool Node::operator!=(const Node& rhs) const {
  return !(operator==(rhs));
}

Node* Node::llink() const {
  return llink_;
}

Node* Node::rlink() const {
  return rlink_;
}

Node* Node::plink() const {
  return plink_;
}

const Node* Node::root() const {
  const Node* r = this;
  Node* p = r->plink_;
  while (p) {
    r = p;
    p = r->plink_;
  }
  return r;
}

void Node::setRlink(Node* n) {
  rlink_ = n;
  if (rlink_)
    rlink_->plink_ = this;
}

void Node::setLlink(Node* n) {
  llink_ = n;
  if (llink_)
    llink_->plink_ = this;
}

void Node::setPlink(Node* n) {
  plink_ = n;
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
  // Number of nodes in left subtree
  mpz_class NL =  N - 1;
  // Number of nodes in right subtree
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
  // Index of right subtree
  mpz_class IR = I / CL;
  // Index of left subtree
  mpz_class IL = I - IR*CL;
  root->llink_ = decode(IL, NL);
  if (root->llink_) {
    root->llink_->plink_ = root;
  }
  root->rlink_ = decode(IR, NR);
  if (root->rlink_) {
    root->rlink_->plink_ = root;
  }
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

Node* Node::dfs_next() const {
  if (llink_)
    return llink_;
  else if (rlink_)
    return rlink_;
  Node* prev = plink_;
  const Node* last_prev = this;
  while (prev) {
    if (prev->rlink_ && prev->rlink_ != last_prev)
      return prev->rlink_;
    last_prev = prev;
    prev = prev->plink_;
  }
  return nullptr;
}
