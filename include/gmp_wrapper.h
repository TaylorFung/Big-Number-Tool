#ifndef GMP_WRAPPER_H // Include guard: prevents multiple inclusion
#define GMP_WRAPPER_H // Define the include guard macro

#include <gmp.h>      // Include the core GMP header file
#include <string>     // Include string header for std::string
#include <stdexcept>  // Include standard exceptions header for std::runtime_error
#include <memory>     // Include memory header for std::unique_ptr (used for string conversion)

// Define a class to wrap mpz_t for automatic memory management (RAII)
class GMP_Integer {
public: // Public interface of the class
    mpz_t value; // The underlying GMP integer object

    // Default constructor: initializes the mpz_t value
    GMP_Integer() { // Constructor definition
        mpz_init(value); // Initialize the GMP integer
    } // End of constructor

    // Constructor from string: initializes from a string representation
    GMP_Integer(const std::string& str, int base = 10) { // Constructor taking string and base
        mpz_init(value); // Initialize the GMP integer
        // Attempt to set the value from the string in the specified base
        if (mpz_set_str(value, str.c_str(), base) != 0) { // Check if setting from string failed
             mpz_clear(value); // Clear the partially initialized value to prevent leaks
             throw std::runtime_error("Invalid number format: " + str); // Throw an error if input is invalid
        } // End if
    } // End of constructor

    // Constructor from unsigned long integer
     GMP_Integer(unsigned long int ul) { // Constructor taking an unsigned long
        mpz_init_set_ui(value, ul); // Initialize the GMP integer with the unsigned long value
    } // End of constructor

    // Copy constructor: creates a new GMP_Integer as a copy of another
    GMP_Integer(const GMP_Integer& other) { // Copy constructor definition
        mpz_init_set(value, other.value); // Initialize this integer as a copy of 'other'
    } // End of copy constructor

    // Move constructor: transfers ownership from a temporary object (optional but good practice)
    GMP_Integer(GMP_Integer&& other) noexcept { // Move constructor definition (noexcept for performance)
        // Transfer the mpz_t state directly without copying
        value[0] = other.value[0]; // Copy the internal GMP structure
        // Invalidate the source object's internal state to prevent double free
        // A simple way is to re-initialize the source (though not strictly necessary if source isn't used)
         mpz_init(other.value); // Re-initialize the source to a default state (0)
    } // End of move constructor


    // Destructor: clears the mpz_t value to free memory
    ~GMP_Integer() { // Destructor definition
        mpz_clear(value); // Free the memory associated with the GMP integer
    } // End of destructor

    // Copy assignment operator: assigns the value of another GMP_Integer to this one
    GMP_Integer& operator=(const GMP_Integer& other) { // Copy assignment operator definition
        if (this != &other) { // Prevent self-assignment
            mpz_set(value, other.value); // Set this integer's value to the value of 'other'
        } // End if
        return *this; // Return a reference to this object
    } // End of copy assignment operator

    // Move assignment operator: transfers ownership from a temporary object
     GMP_Integer& operator=(GMP_Integer&& other) noexcept { // Move assignment operator definition
        if (this != &other) { // Prevent self-assignment
             mpz_swap(value, other.value); // Swap the internal states efficiently
             // No need to clear 'other' explicitly if it's going out of scope
        } // End if
        return *this; // Return a reference to this object
    } // End of move assignment operator

    // Method to get the string representation of the number
    std::string toString(int base = 10) const { // toString method definition
        // Calculate the required size for the string representation
        // Add 2 for potential sign and null terminator
        size_t required_size = mpz_sizeinbase(value, base) + 2; // Get size needed for string in given base
        // Allocate memory using unique_ptr for automatic management
        std::unique_ptr<char[]> buffer(new char[required_size]); // Allocate buffer dynamically
        // Get the string representation from GMP
        char* result_ptr = mpz_get_str(buffer.get(), base, value); // Convert mpz_t to string
         if (!result_ptr) { // Check if conversion failed
            throw std::runtime_error("Failed to convert GMP integer to string."); // Throw error if failed
        } // End if
        return std::string(result_ptr); // Return the result as a std::string
    } // End of toString method

     // Method to check if the number is zero
    bool isZero() const { // isZero method definition
        return mpz_sgn(value) == 0; // Return true if the sign is 0 (meaning the number is zero)
    } // End of isZero method

     // Method to check if the number is negative
    bool isNegative() const { // isNegative method definition
        return mpz_sgn(value) < 0; // Return true if the sign is negative
    } // End of isNegative method

    // Method to get the underlying mpz_t (const version)
    const mpz_t& get() const { // Const getter for the mpz_t
        return value; // Return a const reference to the internal mpz_t
    } // End of const getter

    // Method to get the underlying mpz_t (non-const version)
    mpz_t& get() { // Non-const getter for the mpz_t
        return value; // Return a non-const reference to the internal mpz_t
    } // End of non-const getter

}; // End of GMP_Integer class definition

#endif // GMP_WRAPPER_H // End of include guard

