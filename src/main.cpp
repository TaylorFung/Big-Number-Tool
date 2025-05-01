#include "utils.h"       // Include utility functions (input, random state)
#include "arithmetic.h"  // Include arithmetic operations
#include "modular.h"     // Include modular operations
#include "primality.h"   // Include primality testing and generation
#include "gmp_wrapper.h" // Include the GMP wrapper class
#include <iostream>      // Include iostream for console input/output
#include <string>        // Include string for std::string
#include <limits>        // Include limits for clearing input buffer
// 添加暂停功能的辅助函数
void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Function to display the main menu options to the user
void display_menu() { // Function implementation
    std::cout << "\n===== GMP Big Number Tool Menu =====" << std::endl; // Print menu title
    std::cout << "1. Add two numbers" << std::endl;                 // Option 1
    std::cout << "2. Subtract two numbers" << std::endl;            // Option 2
    std::cout << "3. Multiply two numbers" << std::endl;           // Option 3
    std::cout << "4. Divide two numbers (Quotient & Remainder)" << std::endl; // Option 4
    std::cout << "5. Modulo operation (a mod n)" << std::endl;      // Option 5
    std::cout << "6. Modular Exponentiation (base^exp mod mod)" << std::endl; // Option 6
    std::cout << "7. Check Primality (Miller-Rabin)" << std::endl;  // Option 7
    std::cout << "8. Generate Random Prime (specify bits, e.g., 2048)" << std::endl; // Option 8
    std::cout << "0. Exit" << std::endl;                            // Option 0
    std::cout << "====================================" << std::endl; // Print menu footer
    std::cout << "Enter your choice: "; // Prompt user for input
} // End of display_menu

// Main function - entry point of the application
int main() { // Main function definition
    initialize_random_state(); // Initialize the global GMP random number generator state

    int choice; // Variable to store the user's menu choice

    try { // Start main try block to catch potential errors like EOF during input
        do { // Start main application loop
            display_menu(); // Show the menu options to the user

            // Read the user's choice, handling non-integer input
            while (!(std::cin >> choice)) { // Loop if input is not an integer
                std::cerr << "Invalid input. Please enter a number." << std::endl; // Error message
                std::cin.clear(); // Clear error flags on std::cin
                // Discard the invalid input from the buffer up to the newline
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of line
                std::cout << "Enter your choice: "; // Re-prompt the user
            } // End input validation loop
            // Consume the rest of the line after reading the integer choice
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear rest of the line

            try { // Start try block for handling errors within operations
                // Process the user's choice using a switch statement
                switch (choice) { // Start switch based on user choice
                    case 1: { // Case for Addition
                        GMP_Integer a = read_integer("Enter first number (a): "); // Read first number
                        GMP_Integer b = read_integer("Enter second number (b): "); // Read second number
                        GMP_Integer result = add(a, b); // Perform addition
                        std::cout << "Result (a + b): " << result.toString() << std::endl; // Print result

pause();
                        break; // Exit switch statement
                    } // End case 1
                    case 2: { // Case for Subtraction
                        GMP_Integer a = read_integer("Enter first number (a): "); // Read first number
                        GMP_Integer b = read_integer("Enter second number (b): "); // Read second number
                        GMP_Integer result = subtract(a, b); // Perform subtraction
                        std::cout << "Result (a - b): " << result.toString() << std::endl; // Print result

pause();
                        break; // Exit switch
                    } // End case 2
                    case 3: { // Case for Multiplication
                        GMP_Integer a = read_integer("Enter first number (a): "); // Read first number
                        GMP_Integer b = read_integer("Enter second number (b): "); // Read second number
                        GMP_Integer result = multiply(a, b); // Perform multiplication
                        std::cout << "Result (a * b): " << result.toString() << std::endl; // Print result
                        break; // Exit switch
                    } // End case 3
                    case 4: { // Case for Division
                        GMP_Integer a = read_integer("Enter dividend (a): "); // Read dividend
                        GMP_Integer b = read_integer("Enter divisor (b): "); // Read divisor
                        DivisionResult res = divide(a, b); // Perform division
                        std::cout << "Quotient: " << res.quotient.toString() << std::endl; // Print quotient
                        std::cout << "Remainder: " << res.remainder.toString() << std::endl; // Print remainder

pause();
                        break; // Exit switch
                    } // End case 4
                    case 5: { // Case for Modulo
                        GMP_Integer a = read_integer("Enter number (a): "); // Read base number
                        GMP_Integer n = read_integer("Enter modulus (n, must be positive): "); // Read modulus
                        GMP_Integer result = modulo(a, n); // Perform modulo operation
                        std::cout << "Result (a mod n): " << result.toString() << std::endl; // Print result

pause();
                        break; // Exit switch
                    } // End case 5
                    case 6: { // Case for Modular Exponentiation
                        GMP_Integer base = read_integer("Enter base: "); // Read base
                        GMP_Integer exp = read_integer("Enter exponent (non-negative): "); // Read exponent
                        GMP_Integer mod = read_integer("Enter modulus (must be positive): "); // Read modulus
                        GMP_Integer result = power(base, exp, mod); // Perform modular exponentiation
                        std::cout << "Result (base^exp mod mod): " << result.toString() << std::endl; // Print result

pause();
                        break; // Exit switch
                    } // End case 6
                    case 7: { // Case for Primality Test
                        GMP_Integer n = read_integer("Enter number to test for primality: "); // Read number
                        int reps = 60; // Number of Miller-Rabin rounds (good default)
                         // You could optionally ask the user for the number of reps
                        int result = is_prime(n, reps); // Perform primality test
                        std::cout << "Primality test result for " << n.toString() << ":" << std::endl; // Print header
                        if (result == 0) { // Check if composite
                            std::cout << "  Definitely COMPOSITE." << std::endl; // Print composite result
                        } else if (result == 1) { // Check if probably prime
                            std::cout << "  PROBABLY PRIME (passed " << reps << " Miller-Rabin tests)." << std::endl; // Print probable prime result
                        } else { // result == 2
                            std::cout << "  DEFINITELY PRIME (based on GMP's test)." << std::endl; // Print definite prime result
                        } // End if/else if/else
                        break; // Exit switch
                    } // End case 7
                    case 8: { // Case for Prime Generation
                        unsigned long bits = read_unsigned_long("Enter desired bit length (e.g., 2048): "); // Read desired bit length
                        std::cout << "Generating a " << bits << "-bit prime number..." << std::endl; // Inform user
                        GMP_Integer prime = generate_prime(bits); // Generate the prime number
                        std::cout << "Generated probable prime:" << std::endl; // Print header
                        std::cout << prime.toString() << std::endl; // Print the generated prime
                         std::cout << "(Bit length: " << mpz_sizeinbase(prime.get(), 2) << ")" << std::endl; // Print actual bit length

pause();
                        break; // Exit switch
                    } // End case 8
                    case 0: // Case for Exit
                        std::cout << "Exiting program." << std::endl; // Print exit message
                        break; // Exit switch (and loop condition will be false)
                    default: // Handle invalid menu choices
                        std::cerr << "Invalid choice. Please try again." << std::endl; // Print error message

pause();
                        break; // Exit switch
                } // End switch statement
            } catch (const std::runtime_error& e) { // Catch runtime errors from operations
                std::cerr << "\nOperation Error: " << e.what() << std::endl; // Print the error message
                // No need to clear cin here as the error likely originated from logic, not bad input type
            } // End inner try-catch block
        } while (choice != 0); // Continue loop as long as choice is not 0 (Exit)

    } catch (const std::runtime_error& e) { // Catch errors like EOF from the outer loop's input reading
         std::cerr << "\nInput Error: " << e.what() << std::endl; // Print error message (e.g., EOF)
    } // End outer try-catch block

    clear_random_state(); // Clean up the global GMP random number generator state before exiting
    return 0; // Return 0 to indicate successful execution
} // End of main function

