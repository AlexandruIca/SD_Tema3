#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

std::array<int, 5000001> nums{};
std::array<std::size_t, 5000001> deq{};

auto main() noexcept -> int
{
    std::ifstream f{ "deque.in" };
    std::ofstream g{ "deque.out" };

    std::size_t n{ 0 };
    std::size_t k{ 0 };

    std::int64_t sum{ 0 };

    std::size_t front{ 1 };
    std::size_t back{ 0 };

    f >> n >> k;

    for(std::size_t i = 1; i <= n; ++i) {
        f >> nums[i];
    }

    for(std::size_t i = 1; i <= n; ++i) {
        while(front <= back && nums[i] <= nums[deq[back]]) {
            --back;
        }

        deq[++back] = i;

        if(static_cast<int>(deq[front]) ==
           static_cast<int>(i) - static_cast<int>(k)) {
            ++front;
        }

        if(i >= k) {
            sum += nums[deq[front]];
        }
    }

    g << sum << std::endl;
}
