#include "utils.h"      // Include the corresponding header file
#include <ctime>        // Include ctime for time() to seed random number generator

// Define the global random state variable
gmp_randstate_t gmp_random_state; // Definition of the global random state

// Function definition to initialize the global random state
void initialize_random_state() { // Function implementation
    gmp_randinit_default(gmp_random_state); // Initialize the random state with default algorithm
    // Seed the random state using the current time (simple seeding method)
    // For cryptographic purposes, a better entropy source might be needed (e.g., /dev/urandom)
    gmp_randseed_ui(gmp_random_state, time(NULL)); // Seed using current time
} // End of initialize_random_state

// Function definition to clear the global random state
void clear_random_state() { // Function implementation
    gmp_randclear(gmp_random_state); // Clear the random state to free resources
} // End of clear_random_state


// Function definition to read a GMP_Integer from the user
GMP_Integer read_integer(const std::string& prompt) { // Function implementation
    std::string input_str; // String to store user input
    while (true) { // Loop until valid input is received
        std::cout << prompt; // Display the prompt message to the user
        std::cin >> input_str; // Read the input string from the console

        // Check if input stream failed (e.g., EOF)
         if (std::cin.fail() && !std::cin.eof()) { // Check for general input failure
             std::cin.clear(); // Clear error flags
             // Discard invalid input from buffer up to the newline character
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the line
             std::cerr << "Input error. Please try again." << std::endl; // Inform user of error
             continue; // Ask for input again
         } else if (std::cin.eof()) { // Check if end-of-file was reached
             throw std::runtime_error("Input stream closed (EOF)."); // Signal EOF as an error/exit condition
         } // End if/else if

        try { // Start a try block to catch exceptions from GMP_Integer constructor
            GMP_Integer result(input_str); // Attempt to create a GMP_Integer from the input string
             // Consume the rest of the line in the input buffer
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Important to prevent issues with next input
            return result; // Return the successfully created GMP_Integer
        } catch (const std::runtime_error& e) { // Catch errors during GMP_Integer creation
            std::cerr << "Error: " << e.what() << ". Please enter a valid integer." << std::endl; // Print error message
            // No need to ignore buffer here as >> likely failed or exception happened in constructor
        } // End try-catch
    } // End while loop
} // End of read_integer

// Function definition to read an unsigned long from the user
unsigned long read_unsigned_long(const std::string& prompt) { // Function implementation
    unsigned long value; // Variable to store the unsigned long value
    while (true) { // Loop until valid input is received
        std::cout << prompt; // Display the prompt message
        std::cin >> value; // Attempt to read an unsigned long

        if (std::cin.good()) { // Check if the read was successful and the type is correct
             // Consume the rest of the line in the input buffer
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear rest of the line
            return value; // Return the valid unsigned long value
        } else if (std::cin.eof()) { // Check if end-of-file was reached
            throw std::runtime_error("Input stream closed (EOF)."); // Signal EOF
        } else { // Handle other input errors (e.g., non-numeric input)
            std::cerr << "Invalid input. Please enter a valid positive number." << std::endl; // Inform user of error
            std::cin.clear(); // Clear error flags on cin
            // Discard the invalid input from the buffer up to the newline character
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the line
        } // End if/else if/else
    } // End while loop
} // End of read_unsigned_long

