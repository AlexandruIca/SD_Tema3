#include <array>
#include <cstddef>
#include <fstream>
#include <tuple>
#include <unordered_map>

template<typename T>
constexpr auto idx(T& arr, int const index) -> typename T::value_type&
{
    return arr[static_cast<std::size_t>(index)];
}

using pack_t = std::tuple<int, int, int>;

inline auto contains(std::unordered_map<int, pack_t> const& m, int const val)
    -> bool
{
    return m.find(val) != m.end();
}

auto main() noexcept -> int
{
    std::ifstream f{ "loto.in" };
    std::ofstream g{ "loto.out" };

    std::unordered_map<int, pack_t> sums;
    std::array<int, 100> nums{};

    int n{ 0 };
    int s{ 0 };

    f >> n >> s;

    for(int i = 0; i < n; ++i) {
        f >> idx(nums, i);
    }

    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            for(int k = j; k < n; ++k) {
                int sum{ 0 };

                sum += idx(nums, i);
                sum += idx(nums, j);
                sum += idx(nums, k);

                if(!contains(sums, sum)) {
                    sums.emplace(sum,
                                 std::make_tuple(
                                     idx(nums, i), idx(nums, j), idx(nums, k)));
                }
            }
        }
    }

    for(auto const& it : sums) {
        auto const diff = s - it.first;

        if(contains(sums, diff)) {
            auto const& elem = sums[diff];
            g << std::get<0>(it.second) << ' ' << std::get<1>(it.second) << ' '
              << std::get<2>(it.second) << ' ';
            g << std::get<0>(elem) << ' ' << std::get<1>(elem) << ' '
              << std::get<2>(elem);
            return 0;
        }
    }

    g << -1;
}
