#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

auto generate_input(std::uint32_t const n,
                    std::uint32_t const a,
                    std::uint32_t const b,
                    std::uint32_t const c) -> std::vector<std::uint32_t>
{
    std::vector<std::uint32_t> result(n, 0);

    result[0] = b % c;

    for(std::uint32_t i = 1; i < n; ++i) {
        std::uint32_t prod =
            (static_cast<std::uint64_t>(a) * result[i - 1]) % c + b;
        result[i] = prod % c;
    }

    return result;
}

constexpr auto nth_byte(std::uint32_t const x, std::uint32_t const n)
    -> std::uint32_t
{
    return (x >> (n * 8)) & 0xFF;
}

auto count_sort(std::vector<std::uint32_t> const& input,
                std::vector<std::uint32_t>& tmp,
                std::uint32_t const byte) -> void
{
    constexpr std::uint32_t byte_size = 8;
    constexpr std::uint32_t max_count = 1 << byte_size; // 2 ^ 8

    auto byte_of = [byte](std::uint32_t const num) -> std::uint32_t {
        return nth_byte(num, byte);
    };

    std::array<std::uint32_t, max_count> counter{};
    std::array<std::uint32_t, max_count> idx{};

    counter.fill(0);

    for(auto const elem : input) {
        ++counter[byte_of(elem)];
    }

    idx[0] = 0;

    for(std::uint32_t i = 1; i < max_count; ++i) {
        idx[i] = idx[i - 1] + counter[i - 1];
    }

    for(auto const elem : input) {
        tmp[idx[byte_of(elem)]++] = elem;
    }
}

auto radix_sort(std::vector<std::uint32_t>& v) -> void
{
    std::vector<std::uint32_t> tmp(v.size(), 0);
    std::uint32_t byte_index{ 0 };

    for(;;) {
        count_sort(v, tmp, byte_index);
        count_sort(tmp, v, byte_index + 1);
        count_sort(v, tmp, byte_index + 2);
        count_sort(tmp, v, byte_index + 3);

        if((byte_index += 4) >= sizeof(std::uint32_t)) {
            return;
        }
    }
}

auto main(int, char*[]) noexcept -> int
{
    std::ifstream f{ "radixsort.in" };
    std::uint32_t n{ 0 };
    std::uint32_t a{ 0 };
    std::uint32_t b{ 0 };
    std::uint32_t c{ 0 };

    f >> n >> a >> b >> c;

    auto input = generate_input(n, a, b, c);
    radix_sort(input);

    std::ofstream g{ "radixsort.out" };

    for(std::uint32_t i = 0; i < input.size(); i += 10) {
        g << input[i] << ' ';
    }

    return EXIT_SUCCESS;
}
