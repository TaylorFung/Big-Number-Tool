#ifndef MODULAR_H   // Include guard start
#define MODULAR_H   // Define guard macro

#include "gmp_wrapper.h" // Include the GMP integer wrapper

// Function declaration for calculating the modulo of a GMP_Integer
GMP_Integer modulo(const GMP_Integer& a, const GMP_Integer& n); // Calculates a mod n

// Function declaration for calculating modular exponentiation
GMP_Integer power(const GMP_Integer& base, const GMP_Integer& exp, const GMP_Integer& mod); // Calculates (base^exp) mod mod

#endif // MODULAR_H   // Include guard end

