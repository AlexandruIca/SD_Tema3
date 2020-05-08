#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>

constexpr auto num_zeroes(int num) -> int
{
    int count{ 0 };

    while(num > 0) {
        count += static_cast<int>(num / 5);
        num /= 5;
    }

    return count;
}

constexpr auto find_num(int const cnt) -> int
{
    int left = 1;
    int right = std::numeric_limits<int>::max();

    while(left < right) {
        int const mid = left + (right - left) / 2;
        auto n = num_zeroes(mid);

        if(n == cnt) {
            return mid - mid % 5;
        }
        if(n > cnt) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return -1;
}

auto main() noexcept -> int
{
    std::ifstream f{ "fact.in" };
    std::ofstream g{ "fact.out" };

    int num{ 0 };

    f >> num;

    if(num == 0) {
        g << '1' << std::endl;
        return EXIT_SUCCESS;
    }

    g << find_num(num) << std::endl;
}
