#include "primality.h" // Include the corresponding header file
#include "utils.h"       // Include utils to access the global random state

// Function definition for primality testing (Miller-Rabin)
int is_prime(const GMP_Integer& n, int reps) { // Function implementation
    // mpz_probab_prime_p performs Miller-Rabin test
    // reps controls the number of iterations (higher means lower chance of error for composites)
    // Return values: 0 = definitely composite, 1 = probably prime, 2 = definitely prime (for small n or special forms)
    return mpz_probab_prime_p(n.get(), reps); // Call GMP's probabilistic primality test function
} // End of is_prime

// Function definition for generating a random prime number
GMP_Integer generate_prime(unsigned long bits) { // Function implementation
    if (bits < 2) { // Check if the requested bit size is too small (prime must be >= 2)
        throw std::runtime_error("Cannot generate prime with less than 2 bits."); // Throw error for invalid bit size
    } // End if

    GMP_Integer p; // Create a GMP_Integer to store the potential prime
    while (true) { // Loop until a probable prime is found
        // Generate a random number with the specified number of bits
        // Uses the global random state initialized earlier
        mpz_urandomb(p.get(), gmp_random_state, bits); // Generate random number of 'bits' length

        // Ensure the number has the exact bit length (most significant bit is 1)
        // mpz_urandomb might generate numbers smaller than 2^(bits-1)
        // We set the highest bit (bit index bits-1) to 1 to guarantee the length
        mpz_setbit(p.get(), bits - 1); // Set the most significant bit to ensure length

        // Optional: Ensure the number is odd, as primes > 2 are odd
        // mpz_nextprime handles this, but setting the lowest bit can speed up the search slightly
        // mpz_setbit(p.get(), 0); // Set the least significant bit (makes it odd)

        // Find the next probable prime number greater than or equal to p
        // mpz_nextprime internally uses primality tests
        mpz_nextprime(p.get(), p.get()); // Find the next prime starting from p

        // Optional extra check: Verify with a certain number of Miller-Rabin rounds
        // mpz_nextprime is generally reliable, but an explicit check adds certainty
         if (is_prime(p, 50) > 0) { // Check if it passes 50 rounds of Miller-Rabin (very likely prime)
            // Check if the generated prime still has the correct number of bits
            // mpz_sizeinbase(num, 2) gives the exact bit length
            if (mpz_sizeinbase(p.get(), 2) == bits) { // Verify the bit length
                 return p; // Return the found probable prime
             } // End if bit length check
             // If bit length changed (e.g., went from 2048 to 2049), regenerate
         } // End if primality check
         // If mpz_nextprime generated a number that fails the check or has wrong bit length, loop again
    } // End while loop
} // End of generate_prime

