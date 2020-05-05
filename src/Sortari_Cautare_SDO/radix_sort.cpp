#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

int max{ 0 };

auto generate_input(int const n, int const a, int const b, int const c)
    -> std::vector<int>
{
    std::vector<int> result(static_cast<std::size_t>(n + 1), 0);

    max = result[1] = b;

    for(std::size_t i = 2; i < result.size(); ++i) {
        std::int64_t prod = static_cast<std::int64_t>(a) * result[i - 1] + b;
        result[i] = static_cast<int>(prod % c);
        max = std::max(max, result[i]);
    }

    return result;
}

template<int Base>
auto radix_sort(std::vector<int>& v) -> void
{
    std::array<std::queue<int>, Base> digits;
    int pow{ 1 };

    while(max / pow > 0) {
        for(int const num : v) {
            digits[(num / pow) % Base].push(num);
        }

        pow *= Base;
        v.clear();

        for(std::size_t i = 0; i < Base; ++i) {
            while(!digits[i].empty()) {
                v.push_back(digits[i].front());
                digits[i].pop();
            }
        }
    }
}

auto main(int, char*[]) noexcept -> int
{
    std::ifstream f{ "radixsort.in" };
    int n{ 0 };
    int a{ 0 };
    int b{ 0 };
    int c{ 0 };

    f >> n >> a >> b >> c;

    auto input = generate_input(n, a, b, c);
    radix_sort<10>(input);

    std::ofstream g{ "radixsort.out" };

    for(std::size_t i = 1; i < input.size(); i += 10) {
        g << input[i] << ' ';
    }

    return EXIT_SUCCESS;
}
