#include <string>
#include <vector>
#include <unistd.h>
#include <gmpxx.h>

#include <gtest/gtest.h>

#include "math_tools.h"

namespace {
  class MathTest: public ::testing::Test {
  protected:
    MathTest() {
    }

    virtual ~MathTest() {
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
  };

  TEST(MathTest, FactorialTest) {
    std::vector<mpz_class> values;
    for (int i = 0; i <= 20; ++i) {
      values.push_back(i);
    }
    std::vector<mpz_class> results = {
      1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880,
      3628800, 39916800, 479001600, 6227020800, 87178291200,
      1307674368000, 20922789888000, 355687428096000, 6402373705728000,
      121645100408832000, 2432902008176640000
    };
    for (int i = 0; i <= 20; ++i)
      EXPECT_EQ(results[i], factorial(values[i]));
  }

  TEST(MathTest, CatalanTest) {
    std::vector<mpz_class> values;
    for (int i = 0; i <= 20; ++i) {
      values.push_back(i);
    }
    std::vector<mpz_class> results = {
      1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012,
      742900, 2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420
    };
    for (int i = 0; i <= 20; ++i)
      EXPECT_EQ(results[i], catalan(values[i]));
  }
}
