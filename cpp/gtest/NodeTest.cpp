#include <string>
#include <vector>
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

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
  }

  TEST(NodeTest, CodecTest) {
    gmp_randclass rg(gmp_randinit_default);
    rg.seed(time(NULL));
    for (int j = 1; j < 100; ++j) {
      const mpz_class N = rg.get_z_bits(5);
      const mpz_class I = rg.get_z_bits(100) % catalan(N);
      Node* n3 = Node::decode(I, N);
      mpz_class I1 = 0;
      if (n3)
        I1 = Node::encode(n3);
      EXPECT_EQ(I, I1);
      delete n3;
    }
  }
}
