#include "modular.h" // Include the corresponding header file

// Function definition for calculating the modulo of a GMP_Integer
GMP_Integer modulo(const GMP_Integer& a, const GMP_Integer& n) { // Function implementation
    if (n.isZero() || n.isNegative()) { // Check if the modulus is non-positive
        throw std::runtime_error("Modulus must be positive."); // Throw error for zero or negative modulus
    } // End if
    GMP_Integer result; // Create a GMP_Integer for the result
    mpz_mod(result.get(), a.get(), n.get()); // Perform GMP modulo operation: result = a mod n
    return result; // Return the result
} // End of modulo

// Function definition for calculating modular exponentiation
GMP_Integer power(const GMP_Integer& base, const GMP_Integer& exp, const GMP_Integer& mod) { // Function implementation
     if (mod.isZero() || mod.isNegative()) { // Check if the modulus is non-positive
        throw std::runtime_error("Modulus must be positive for modular exponentiation."); // Throw error
    } // End if
     if (exp.isNegative()) { // Check if the exponent is negative
         // Modular inverse would be needed, which is more complex.
         // For simplicity, restrict to non-negative exponents.
        throw std::runtime_error("Exponent must be non-negative for this power function."); // Throw error
    } // End if

    GMP_Integer result; // Create a GMP_Integer for the result
    // Perform GMP modular exponentiation: result = (base ^ exp) mod mod
    mpz_powm(result.get(), base.get(), exp.get(), mod.get()); // Calculate modular power
    return result; // Return the result
} // End of power

