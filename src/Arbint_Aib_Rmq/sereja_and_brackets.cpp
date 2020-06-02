#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

constexpr int max_size = 1'000'005;

std::array<int, max_size> prefix1;
std::array<int, max_size> prefix2;
std::array<int, max_size * 4> segtree;

auto build_segtree(int const lo, int const hi, int const pos) -> void
{
    auto const l = static_cast<std::size_t>(lo);
    auto const p = static_cast<std::size_t>(pos);

    if(lo == hi) {
        segtree[p] = prefix1[l];
        return;
    }

    int const mid = lo + (hi - lo) / 2;

    build_segtree(lo, mid, 2 * pos);
    build_segtree(mid + 1, hi, 2 * pos + 1);

    segtree[p] = std::min(segtree[2 * p], segtree[2 * p + 1]);
}

auto get_min(std::size_t a,
             std::size_t b,
             std::size_t lo,
             std::size_t hi,
             std::size_t pos = 1) -> int
{
    if(a == 0) {
        return std::min(0, get_min(a + 1, b, lo, hi, pos));
    }
    if(a <= lo && b >= hi) {
        return segtree[pos];
    }
    if(a > hi || b < lo) {
        return std::numeric_limits<int>::max();
    }

    auto const mid = lo + (hi - lo) / 2;
    return std::min(get_min(a, b, lo, mid, 2 * pos),
                    get_min(a, b, mid + 1, hi, 2 * pos + 1));
}

auto main() noexcept -> int
{
    // std::ifstream f{ "sereja.in" };
    // std::ofstream g{ "sereja.out" };

    std::string s{};
    s.reserve(max_size);

    std::cin >> s;
    // f >> s;

    int s1{ 0 };
    int s2{ 0 };
    std::size_t index{ 1 };

    for(char const c : s) {
        if(c == '(') {
            s1 += 1;
            s2 += 0;
        }
        else if(c == ')') {
            s1 += -1;
            s2 += 1;
        }

        prefix1[index] = s1;
        prefix2[index] = s2;
        ++index;
    }

    std::size_t l{ 0 };
    std::size_t r{ 0 };
    int n{ 0 };

    std::cin >> n;
    // f >> n;

    build_segtree(1, static_cast<int>(index) - 1, 1);

    for(int i = 1; i <= n; ++i) {
        std::cin >> l >> r;
        // f >> l >> r;

        std::cout << 2 * (prefix2[r] - prefix2[l - 1] -
                          (prefix1[l - 1] - get_min(l - 1, r, 1, index - 1)));
        std::cout << std::endl;
    }
}
