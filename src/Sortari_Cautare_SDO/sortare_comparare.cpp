#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

auto read_input() -> std::vector<int>
{
    std::ifstream f{ "algsort.in" };
    std::vector<int> result{};
    int count{ 0 };

    f >> count;

    result.reserve(static_cast<std::uint64_t>(count));

    for(int i = 0; i < count; ++i) {
        int num{ 0 };
        f >> num;
        result.push_back(num);
    }

    return result;
}

auto quicksort(std::vector<int>& v,
               std::int64_t const start,
               std::int64_t const end) -> void
{
    auto i = start;
    auto j = end;
    auto pivot = v[static_cast<std::size_t>(start + (end - start) / 2)];

    while(i <= j) {
        while(v[static_cast<std::size_t>(i)] < pivot) {
            ++i;
        }
        while(v[static_cast<std::size_t>(j)] > pivot) {
            --j;
        }

        if(i <= j) {
            std::swap(v[static_cast<std::size_t>(i)],
                      v[static_cast<std::size_t>(j)]);
            ++i;
            --j;
        }
    }

    if(j > start) {
        quicksort(v, start, j);
    }
    if(end > i) {
        quicksort(v, i, end);
    }
}

auto main() noexcept -> int
{
    auto input = read_input();
    quicksort(input, 0, static_cast<std::int64_t>(input.size() - 1));

    std::ofstream g{ "algsort.out" };

    for(int const elem : input) {
        g << elem << ' ';
    }

    return EXIT_SUCCESS;
}
