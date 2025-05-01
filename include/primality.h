#ifndef PRIMALITY_H // Include guard start
#define PRIMALITY_H // Define guard macro

#include "gmp_wrapper.h" // Include the GMP integer wrapper
#include <gmp.h>         // Include GMP header for random state access

// Function declaration for primality testing (Miller-Rabin)
// Returns: 2 if definitely prime, 1 if probably prime, 0 if composite.
int is_prime(const GMP_Integer& n, int reps = 25); // Checks if n is prime using Miller-Rabin test

// Function declaration for generating a random prime number of specified bit length
GMP_Integer generate_prime(unsigned long bits); // Generates a probable prime number with 'bits' bits

#endif // PRIMALITY_H // Include guard end

