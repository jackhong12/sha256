#include "sha256.h"
#include <iostream>

int main (int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <string>" << std::endl;
        return 1;
    }

    SHA256 sha256(argv[1]);
    std::cout << "sha256: " << sha256.digest() << std::endl;
    return 0;
}
