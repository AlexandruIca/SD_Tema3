#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

auto partition(std::vector<int>& v,
               std::size_t const left,
               std::size_t const right) -> int
{
    ///*static*/ std::random_device rd{};
    // std::mt19937 rng{ rd() };
    // std::uniform_int_distribution<std::size_t> dist{
    // 0, std::numeric_limits<std::size_t>::max()
    //};

    // auto const pivot = v[left + (dist(rng) % (right - left + 1))];
    auto const pivot = v[left + (right - left) / 2];
    int i = static_cast<int>(left);
    int j = static_cast<int>(right);
    int const size = static_cast<int>(right);
    int const lsize = static_cast<int>(left);

    while(true) {
        while(i < size && v[static_cast<std::size_t>(i)] < pivot) {
            ++i;
        }
        while(j > lsize && v[static_cast<std::size_t>(j)] > pivot) {
            --j;
        }

        if(i < j) {
            std::swap(v[static_cast<std::size_t>(i)],
                      v[static_cast<std::size_t>(j)]);
            ++i;
            --j;
        }
        else {
            return j;
        }
    }

    return 0;
}

auto select(std::vector<int>& v,
            std::size_t const left,
            std::size_t const right,
            int const n) -> void
{
    if(left == right) {
        return;
    }

    int const index = partition(v, left, right);
    int const count = index - static_cast<int>(left) + 1;

    if(count >= n) {
        select(v, left, static_cast<std::size_t>(index), n);
    }
    else {
        select(v, static_cast<std::size_t>(index) + 1, right, n - count);
    }
}

auto main() noexcept -> int
{
    std::ifstream f{ "sdo.in" };
    std::ofstream g{ "sdo.out" };

    std::vector<int> nums{};
    int num{ 0 };
    int k{ 0 };

    f >> num >> k;
    nums.reserve(static_cast<std::size_t>(num));
    nums.push_back(0);

    for(int i = 0; i < num; ++i) {
        int tmp{ 0 };
        f >> tmp;
        nums.push_back(tmp);
    }

    select(nums, 1, nums.size() - 1, k);

    g << nums[static_cast<std::size_t>(k)] << std::endl;
}
