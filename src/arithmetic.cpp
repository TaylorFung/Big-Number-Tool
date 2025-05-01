#include "arithmetic.h" // Include the corresponding header file

// Function definition for adding two GMP_Integers
GMP_Integer add(const GMP_Integer& a, const GMP_Integer& b) { // Function implementation
    GMP_Integer result; // Create a GMP_Integer to store the result
    mpz_add(result.get(), a.get(), b.get()); // Perform GMP addition: result = a + b
    return result; // Return the result object
} // End of add

// Function definition for subtracting two GMP_Integers
GMP_Integer subtract(const GMP_Integer& a, const GMP_Integer& b) { // Function implementation
    GMP_Integer result; // Create a GMP_Integer for the result
    mpz_sub(result.get(), a.get(), b.get()); // Perform GMP subtraction: result = a - b
    return result; // Return the result
} // End of subtract

// Function definition for multiplying two GMP_Integers
GMP_Integer multiply(const GMP_Integer& a, const GMP_Integer& b) { // Function implementation
    GMP_Integer result; // Create a GMP_Integer for the result
    mpz_mul(result.get(), a.get(), b.get()); // Perform GMP multiplication: result = a * b
    return result; // Return the result
} // End of multiply

// Function definition for dividing two GMP_Integers
DivisionResult divide(const GMP_Integer& a, const GMP_Integer& b) { // Function implementation
    if (b.isZero()) { // Check if the divisor is zero
        throw std::runtime_error("Division by zero error."); // Throw an error if division by zero is attempted
    } // End if
    DivisionResult res; // Create a DivisionResult struct to store quotient and remainder
    // Perform GMP division, calculating both quotient (q) and remainder (r): a = b*q + r
    mpz_tdiv_qr(res.quotient.get(), res.remainder.get(), a.get(), b.get()); // Calculate quotient and remainder
    return res; // Return the structure containing quotient and remainder
} // End of divide

