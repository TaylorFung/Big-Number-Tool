#ifndef ARITHMETIC_H // Include guard start
#define ARITHMETIC_H // Define guard macro

#include "gmp_wrapper.h" // Include the GMP integer wrapper
#include <utility>       // Include utility for std::pair

// Function declaration for adding two GMP_Integers
GMP_Integer add(const GMP_Integer& a, const GMP_Integer& b); // Adds two GMP integers

// Function declaration for subtracting two GMP_Integers
GMP_Integer subtract(const GMP_Integer& a, const GMP_Integer& b); // Subtracts b from a

// Function declaration for multiplying two GMP_Integers
GMP_Integer multiply(const GMP_Integer& a, const GMP_Integer& b); // Multiplies two GMP integers

// Structure to hold division result (quotient and remainder)
struct DivisionResult { // Defines a structure to return quotient and remainder
    GMP_Integer quotient; // The quotient of the division
    GMP_Integer remainder; // The remainder of the division
}; // End of DivisionResult struct

// Function declaration for dividing two GMP_Integers
DivisionResult divide(const GMP_Integer& a, const GMP_Integer& b); // Divides a by b, returns quotient and remainder

#endif // ARITHMETIC_H // Include guard end

