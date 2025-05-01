#ifndef UTILS_H       // Include guard start
#define UTILS_H       // Define guard macro

#include "gmp_wrapper.h" // Include the GMP integer wrapper
#include <string>        // Include string library
#include <iostream>      // Include iostream for input/output
#include <limits>        // Include limits for numeric_limits (used for clearing input buffer)
#include <gmp.h>         // Include GMP header for random state type

// Declare the global random state (defined in utils.cpp)
extern gmp_randstate_t gmp_random_state; // Declaration of global random state variable

// Function declaration to initialize the global random state
void initialize_random_state(); // Initializes the GMP random number generator state

// Function declaration to clear the global random state
void clear_random_state(); // Cleans up the GMP random number generator state

// Function declaration to read a GMP_Integer from the user with a prompt
GMP_Integer read_integer(const std::string& prompt); // Reads a big integer from standard input

// Function declaration to read an unsigned long from the user with a prompt
unsigned long read_unsigned_long(const std::string& prompt); // Reads an unsigned long from standard input

#endif // UTILS_H       // Include guard end

