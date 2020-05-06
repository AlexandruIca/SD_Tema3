#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

auto merge(std::vector<int>& v, int const start, int const mid, int const end)
    -> int
{
    std::vector<int> tmp{};
    int i = start;
    int j = mid + 1;
    int inv{ 0 };

    tmp.reserve(static_cast<unsigned>(end - start + 1));

    while(i <= mid && j <= end) {
        auto const l = v[static_cast<std::size_t>(i)];
        auto const r = v[static_cast<std::size_t>(j)];
        if(l <= r) {
            tmp.push_back(l);
            ++i;
        }
        else {
            tmp.push_back(r);
            ++j;
            inv += (mid + 1 - i);
        }
    }

    while(i <= mid) {
        tmp.push_back(v[static_cast<std::size_t>(i)]);
        ++i;
    }
    while(j <= end) {
        tmp.push_back(v[static_cast<std::size_t>(j)]);
        ++j;
    }

    for(std::size_t k = 0; k < tmp.size(); ++k) {
        v[k + static_cast<std::size_t>(start)] = tmp[k];
    }

    return inv;
}

auto merge_sort(std::vector<int>& v, int const l, int const r) -> int
{
    int inv{ 0 };
    if(l < r) {
        int const mid = l + (r - l) / 2;
        inv += merge_sort(v, l, mid);
        inv += merge_sort(v, mid + 1, r);
        inv += merge(v, l, mid, r);
    }

    return inv;
}

auto main() noexcept -> int
{
    std::ifstream f{ "inv.in" };
    std::ofstream g{ "inv.out" };

    std::vector<int> nums{};
    int count{ 0 };

    f >> count;

    nums.reserve(static_cast<std::size_t>(count));

    for(int i = 0; i < count; ++i) {
        int tmp{ 0 };
        f >> tmp;
        nums.push_back(tmp);
    }

    int const total = merge_sort(nums, 0, static_cast<int>(nums.size()) - 1);

    g << total % 9917;

    return EXIT_SUCCESS;
}
