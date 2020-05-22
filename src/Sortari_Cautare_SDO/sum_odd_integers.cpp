#include <cstdint>
#include <fstream>
#include <iostream>

constexpr auto is_possible(std::int64_t const num, std::int64_t const count)
    -> bool
{
    if(count * count > num) {
        return false;
    }
    if((num + count) % 2 != 0) {
        return false;
    }

    return true;
}

auto main() noexcept -> int
{
    std::int64_t t{ 0 };
    std::cin >> t;

    for(std::int64_t i = 0; i < t; ++i) {
        std::int64_t n{ 0 };
        std::int64_t k{ 0 };

        std::cin >> n >> k;

        if(is_possible(n, k)) {
            std::cout << "YES\n";
        }
        else {
            std::cout << "NO\n";
        }
    }
}
