#ifndef CATALANTREE_MATH_TOOLS_H
#define CATALANTREE_MATH_TOOLS_H

#include <map>

#include <gmpxx.h>
#include <stdint.h>

mpz_class factorial(uint64_t n);
mpz_class factorial(const mpz_class& n);

mpz_class catalan(uint64_t n);
mpz_class catalan(const mpz_class& n);

mpz_class catalan(uint64_t n, std::map<mpz_class, mpz_class>& cache);
mpz_class catalan(const mpz_class& n, std::map<mpz_class, mpz_class>& cache);

#endif //CATALANTREE_MATH_TOOLS_H
