#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

constexpr auto is_open(char const c) -> bool
{
    return c == '{' || c == '[' || c == '(';
}

constexpr auto is_closed(char const c) -> bool
{
    return c == '}' || c == ']' || c == ')';
}

constexpr auto match(std::vector<std::pair<char, int>> const& v, char const c)
    -> bool
{
    return is_closed(c) && is_open(v.back().first) &&
           std::abs(c - v.back().first) <= 2;
}

auto main() noexcept -> int
{
    std::ifstream f{ "paranteze.in" };
    std::ofstream g{ "paranteze.out" };

    int max_length{ 0 };
    int length{ 0 };
    int n{ 0 };
    std::vector<std::pair<char, int>> v{};
    std::array<bool, 1000001> app{};

    f >> n;
    v.reserve(static_cast<std::size_t>(n / 2) + 1);
    app.fill(false);

    for(int i = 0; i < n; ++i) {
        char c{ '\0' };
        f >> c;

        if(is_open(c)) {
            v.emplace_back(c, i);
        }
        else if(!v.empty()) {
            if(match(v, c)) {
                app[static_cast<std::size_t>(i)] =
                    app[static_cast<std::size_t>(v.back().second)] = true;
            }

            v.pop_back();
        }
    }

    for(std::size_t i = 0; i < static_cast<std::size_t>(n); ++i) {
        if(app[i] == true) {
            ++length;
        }
        else {
            max_length = std::max(max_length, length);
            length = 0;
        }
    }

    g << max_length << std::endl;
}
