#include "math_tools.h"

mpz_class factorial(uint64_t n) {
  return factorial(mpz_class(n));
}

mpz_class factorial(const mpz_class& n) {
  mpz_class f(1);
  for (mpz_class i = 1; i <= n; ++i) {
    f *= i;
  }
  return f;
}

mpz_class catalan(uint64_t n) {
  return catalan(mpz_class(n));
}

mpz_class catalan(const mpz_class& n) {
  mpz_class f0 = factorial(n);
  mpz_class f1 = factorial(2*n);
  return f1/(f0*f0*(n + 1));
}

mpz_class catalan(uint64_t n, std::map<mpz_class, mpz_class>& cache) {
  return catalan(mpz_class(n), cache);
}

mpz_class catalan(const mpz_class& n, std::map<mpz_class, mpz_class>& cache) {
  if (cache.find(n) != cache.end()) {
    return cache[n];
  }
  mpz_class c = catalan(n);
  cache[n] = c;
  return c;
}
