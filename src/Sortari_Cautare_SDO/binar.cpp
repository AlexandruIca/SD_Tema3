#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>

auto main() noexcept -> int
{
    std::ifstream f{ "binar.in" };
    std::ofstream g{ "binar.out" };

    std::array<std::array<char, 2001>, 2001> matrix{};
    std::array<std::size_t, 2001> indexes{};

    int n{ 0 };
    int m{ 0 };

    f >> n >> m;
    f.get();

    std::iota(indexes.begin(), indexes.begin() + m, 0);

    std::string line{};
    std::size_t line_no{ 0 };

    while(std::getline(f, line)) {
        for(std::size_t i = 0; i < line.size(); ++i) {
            matrix[i][line_no] = line[i];
        }
        ++line_no;
    }

    std::sort(indexes.begin(),
              indexes.begin() + m,
              [&matrix](std::size_t const i, std::size_t const j) -> bool {
                  // return matrix[i] < matrix[j];
                  return strcmp(matrix[i].data(), matrix[j].data()) < 0;
              });

    for(std::size_t i = 0; i < static_cast<std::size_t>(m); ++i) {
        g << indexes[i] + 1 << ' ';
    }
    g << std::endl;
}
