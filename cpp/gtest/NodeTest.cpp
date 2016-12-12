#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <gmpxx.h>

#include <gtest/gtest.h>

#include "math_tools.h"
#include "node.h"

namespace {
  class NodeTest: public ::testing::Test {
  protected:
    NodeTest() {
    }

    virtual ~NodeTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
  };

  TEST(NodeTest, EqualityTest) {
    Node* n1 = new Node();
    Node* n2 = new Node();

    EXPECT_EQ(*n1, *n2);

    Node* n3 = Node::decode(100, 100);
    Node* n4 = Node::decode(100, 100);
    Node* n5 = Node::decode(100, 101);

    EXPECT_EQ(*n3, *n4);
    EXPECT_NE(*n3, *n5);

    n1->setLlink(n2);
    Node* n6 = new Node();
    n2->setRlink(n6);

    EXPECT_EQ(*n1, *(n6->root()));

    delete n1;
    // n2 and n6 deleted in n1 destructor as subtrees of n1
    delete n3;
    delete n4;
    delete n5;
  }

  TEST(NodeTest, CodecTest) {
    gmp_randclass rg(gmp_randinit_default);
    rg.seed(time(NULL));
    for (int j = 1; j < 100; ++j) {
      const size_t N = j;
      const mpz_class I = rg.get_z_bits(100) % catalan(N);
      Node* n3 = Node::decode(I, N);
      mpz_class I1 = 0;
      if (n3)
        I1 = Node::encode(n3);
      EXPECT_EQ(I, I1);
      delete n3;
    }
  }

  TEST(NodeTest, DFSTest) {
    /*        n1
     *       /  \
     *      n2   n7
     *     /  \   \
     *    n3  n6  n8
     *   /  \     / \
     *  n4  n5   n9  n13
     *            \
     *            n10
     *            / \
     *          n11 n12
     */
    Node* n1 = new Node();
    Node* n2 = new Node();
    Node* n3 = new Node();
    Node* n4 = new Node();
    Node* n5 = new Node();
    Node* n6 = new Node();
    Node* n7 = new Node();
    Node* n8 = new Node();
    Node* n9 = new Node();
    Node* n10 = new Node();
    Node* n11 = new Node();
    Node* n12 = new Node();
    Node* n13 = new Node();
    n1->setLlink(n2);
    n2->setLlink(n3);
    n3->setLlink(n4);
    n3->setRlink(n5);
    n2->setRlink(n6);
    n1->setRlink(n7);
    n7->setRlink(n8);
    n8->setLlink(n9);
    n9->setRlink(n10);
    n10->setLlink(n11);
    n10->setRlink(n12);
    n8->setRlink(n13);
    Node* nodes[] = { n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13};

    for (int i = 0; i < 13; ++i) {
        std::cout << "node [" << i << "] = (" << nodes[i] << "): llink = (" << nodes[i]->llink()
                  << "); rlink = (" << nodes[i]->rlink() << "); plink = (" << nodes[i]->plink() << ")" << std::endl;
    }

    EXPECT_EQ(n1->dfs_next(), n2);
    EXPECT_EQ(n2->dfs_next(), n3);
    EXPECT_EQ(n3->dfs_next(), n4);
    EXPECT_EQ(n4->dfs_next(), n5);
    EXPECT_EQ(n5->dfs_next(), n6);
    EXPECT_EQ(n6->dfs_next(), n7);
    EXPECT_EQ(n7->dfs_next(), n8);
    EXPECT_EQ(n8->dfs_next(), n9);
    EXPECT_EQ(n9->dfs_next(), n10);
    EXPECT_EQ(n10->dfs_next(), n11);
    EXPECT_EQ(n11->dfs_next(), n12);
    EXPECT_EQ(n12->dfs_next(), n13);
    EXPECT_EQ(n13->dfs_next(), nullptr);
    delete n1;
    // All other nodes automatically deleted as n1 subtrees
  }
}
