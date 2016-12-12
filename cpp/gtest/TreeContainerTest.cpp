#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <gmpxx.h>

#include <gtest/gtest.h>

#include "treecontainer.h"

namespace {
  class TreeContainerTest: public ::testing::Test {
  protected:
    TreeContainerTest() {
    }

    virtual ~TreeContainerTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
  };

  TEST(TreeContainerTest, EqualityTest) {
    TreeContainer<int>* n1 = new TreeContainer<int>();
    n1->data() = 1;
    TreeContainer<int>* n2 = new TreeContainer<int>();
    n2->data() = 1;

    EXPECT_EQ(*n1, *n2);
    n2->data() = 2;
    EXPECT_NE(*n1, *n2);

    delete n1;
    delete n2;
  }

  TEST(TreeContainerTest, DFS_IteratorTest) {
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
    const int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    TreeContainer<int> n1(v[0]);
    TreeContainer<int>* n2 = new TreeContainer<int>(v[1]);
    TreeContainer<int>* n3 = new TreeContainer<int>(v[2]);
    TreeContainer<int>* n4 = new TreeContainer<int>(v[3]);
    TreeContainer<int>* n5 = new TreeContainer<int>(v[4]);
    TreeContainer<int>* n6 = new TreeContainer<int>(v[5]);
    TreeContainer<int>* n7 = new TreeContainer<int>(v[6]);
    TreeContainer<int>* n8 = new TreeContainer<int>(v[7]);
    TreeContainer<int>* n9 = new TreeContainer<int>(v[8]);
    TreeContainer<int>* n10 = new TreeContainer<int>(v[9]);
    TreeContainer<int>* n11 = new TreeContainer<int>(v[10]);
    TreeContainer<int>* n12 = new TreeContainer<int>(v[11]);
    TreeContainer<int>* n13 = new TreeContainer<int>(v[12]);
    n1.setLlink(n2);
    n2->setLlink(n3);
    n3->setLlink(n4);
    n3->setRlink(n5);
    n2->setRlink(n6);
    n1.setRlink(n7);
    n7->setRlink(n8);
    n8->setLlink(n9);
    n9->setRlink(n10);
    n10->setLlink(n11);
    n10->setRlink(n12);
    n8->setRlink(n13);
    int ctr = 0;
    for (TreeContainer<int>::dfs_iterator it = n1.begin(); it != n1.end(); ++it) {
      EXPECT_EQ(*it, v[ctr++]);
    }
  }

  TEST(TreeContainerTest, DFS_IteratorFindTest) {
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
    const int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    TreeContainer<int> n1(v[0]);
    TreeContainer<int>* n2 = new TreeContainer<int>(v[1]);
    TreeContainer<int>* n3 = new TreeContainer<int>(v[2]);
    TreeContainer<int>* n4 = new TreeContainer<int>(v[3]);
    TreeContainer<int>* n5 = new TreeContainer<int>(v[4]);
    TreeContainer<int>* n6 = new TreeContainer<int>(v[5]);
    TreeContainer<int>* n7 = new TreeContainer<int>(v[6]);
    TreeContainer<int>* n8 = new TreeContainer<int>(v[7]);
    TreeContainer<int>* n9 = new TreeContainer<int>(v[8]);
    TreeContainer<int>* n10 = new TreeContainer<int>(v[9]);
    TreeContainer<int>* n11 = new TreeContainer<int>(v[10]);
    TreeContainer<int>* n12 = new TreeContainer<int>(v[11]);
    TreeContainer<int>* n13 = new TreeContainer<int>(v[12]);
    n1.setLlink(n2);
    n2->setLlink(n3);
    n3->setLlink(n4);
    n3->setRlink(n5);
    n2->setRlink(n6);
    n1.setRlink(n7);
    n7->setRlink(n8);
    n8->setLlink(n9);
    n9->setRlink(n10);
    n10->setLlink(n11);
    n10->setRlink(n12);
    n8->setRlink(n13);
    TreeContainer<int>::dfs_iterator it = std::find(n1.begin(), n1.end(), v[5]);
    EXPECT_EQ(*it, v[5]);
  }

  TEST(TreeContainerTest, DFS_IteratorToStringTest) {
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
    const std::string v("abcdefghijklm");
    TreeContainer<int> n1(v[0]);
    TreeContainer<int>* n2 = new TreeContainer<int>(v[1]);
    TreeContainer<int>* n3 = new TreeContainer<int>(v[2]);
    TreeContainer<int>* n4 = new TreeContainer<int>(v[3]);
    TreeContainer<int>* n5 = new TreeContainer<int>(v[4]);
    TreeContainer<int>* n6 = new TreeContainer<int>(v[5]);
    TreeContainer<int>* n7 = new TreeContainer<int>(v[6]);
    TreeContainer<int>* n8 = new TreeContainer<int>(v[7]);
    TreeContainer<int>* n9 = new TreeContainer<int>(v[8]);
    TreeContainer<int>* n10 = new TreeContainer<int>(v[9]);
    TreeContainer<int>* n11 = new TreeContainer<int>(v[10]);
    TreeContainer<int>* n12 = new TreeContainer<int>(v[11]);
    TreeContainer<int>* n13 = new TreeContainer<int>(v[12]);
    n1.setLlink(n2);
    n2->setLlink(n3);
    n3->setLlink(n4);
    n3->setRlink(n5);
    n2->setRlink(n6);
    n1.setRlink(n7);
    n7->setRlink(n8);
    n8->setLlink(n9);
    n9->setRlink(n10);
    n10->setLlink(n11);
    n10->setRlink(n12);
    n8->setRlink(n13);
    std::string str = std::string(n1.begin(), n1.end());
    std::cout << str << std::endl;
    EXPECT_EQ(str, v);
  }
}
