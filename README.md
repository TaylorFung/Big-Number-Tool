# GMP Big Number Tool

A command-line tool for performing arbitrary-precision arithmetic using the GMP library.

## Features

* Addition, Subtraction, Multiplication, Division of large integers.
* Modulo operation.
* Modular Exponentiation.
* Probabilistic Primality Testing (Miller-Rabin).
* Random Prime Number Generation (specify bit length, e.g., 2048).
* Interactive command-line interface.

## Prerequisites

* A C++11 compatible compiler (like g++ or clang++).
* CMake (version 3.10 or higher).
* GMP Development Library (`libgmp-dev` on Debian/Ubuntu, `gmp-devel` on Fedora/CentOS, `gmp` via Homebrew on macOS).

## Building

1.  **Clone the repository:**
    ```bash
    git clone <your-repo-url>
    cd GMPBigNumTool
    ```
2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```
3.  **Configure with CMake:**
    ```bash
    cmake ..
    ```
4.  **Compile:**
    ```bash
    make
    ```
    The executable `gmp_tool` will be created in the `build` directory.

## Running

Navigate to the `build` directory and run the executable:

```bash
./gmp_tool
