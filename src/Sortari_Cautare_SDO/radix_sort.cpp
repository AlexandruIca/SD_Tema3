#include <cstdlib>
#include <fstream>
#include <iostream>

auto main(int, char*[]) noexcept -> int
{
    std::ifstream f{ "radixsort.in" };
    std::string line{};
    std::getline(f, line);

    std::cout << line << std::endl;

    return EXIT_SUCCESS;
}
