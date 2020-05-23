#include <array>
#include <fstream>
#include <iostream>

constexpr int size = 100005;
using arr_t = std::array<int, size>;

arr_t nums;
arr_t app;
arr_t count;

template<typename T>
constexpr auto idx(T& arr, int const index) -> typename T::value_type&
{
    return arr[static_cast<std::size_t>(index)];
}

auto preprocess(int const n)
{
    int num{ 0 };

    ++idx(app, idx(nums, n));
    idx(count, n) = ++num;

    for(int i = n - 1; i > 0; --i) {
        if(idx(app, idx(nums, i)) == 0) {
            idx(count, i) = ++num;
        }
        else {
            idx(count, i) = num;
        }

        ++idx(app, idx(nums, i));
    }
}

auto main() noexcept -> int
{
    std::ifstream f{ "input.in" };

    int n{ 0 };
    int m{ 0 };

    std::cin >> n >> m;

    for(int i = 1; i <= n; ++i) {
        std::cin >> idx(nums, i);
    }

    preprocess(n);

    for(int i = 1; i <= m; ++i) {
        int x{ 0 };

        std::cin >> x;
        std::cout << idx(count, x) << std::endl;
    }
}
