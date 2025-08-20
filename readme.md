# SHA-256

A simple SHA-256 implementation in [C++ header](./src/sha256.h). You don't need to link against any libraries, just include the header file.

Example usage:
```cpp
#include "sha256.h" // include src/sha256.h
#include <iostream>

int main() {
    SHA256 sha256("Hello, World!");
    std::cout << "sha256: " << sha256.digest() << std::endl; // get the SHA-256 hash
    return 0;
}
```

## Dependencies

This project requires gtest and cmake to build the tests. You can install them on Ubuntu with the following command:

```bash
sudo apt install libgtest-dev cmake build-essential
```

## Build

Build the project with the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

## Tests

Run the tests with the following command:

```bash
make test
```
