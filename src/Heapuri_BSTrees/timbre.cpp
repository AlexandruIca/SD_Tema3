#include <algorithm>
#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

template<typename T>
constexpr auto idx(T& vec, int const index) -> typename T::value_type&
{
    return vec[static_cast<std::size_t>(index)];
}

auto main() noexcept -> int
{
    std::ifstream f{ "timbre.in" };
    std::ofstream g{ "timbre.out" };

    std::array<std::pair<int, int>, 10'001> intervals{};
    std::priority_queue<int, std::vector<int>, std::greater<>> nums{};

    int n{ 0 };
    int m{ 0 };
    int k{ 0 };

    f >> n >> m >> k;

    intervals.fill(std::make_pair(0, 0));

    for(int i = 0; i < m; ++i) {
        int margin{ 0 };
        int cost{ 0 };

        f >> margin >> cost;
        idx(intervals, i) = { margin, cost };
    }

    std::sort(intervals.begin(), intervals.begin() + m);

    int last{ m - 1 };
    int cost{ 0 };

    while(n > 0) {
        while(last >= 0 && idx(intervals, last).first >= n) {
            nums.push(idx(intervals, last--).second);
        }

        n -= std::min(n, k);

        if(!nums.empty()) {
            cost += nums.top();
            nums.pop();
        }
    }

    g << cost << '\n';
}
