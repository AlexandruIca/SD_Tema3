#include <algorithm>
#include <array>
#include <cstddef>
#include <fstream>
#include <set>

std::array<int, 100005> v;
std::array<int, 100005> app;

template<typename T>
constexpr auto idx(T& arr, int const idx) -> typename T::value_type&
{
    return arr[static_cast<std::size_t>(idx)];
}

auto main() noexcept -> int
{
    std::ifstream f{ "vila2.in" };
    std::ofstream g{ "vila2.out" };

    int n{ 0 };
    int k{ 0 };
    int diff{ 0 };

    f >> n >> k;

    int min{ 40000 };
    int max{ -1 };

    for(int i = 1; i <= k + 1; ++i) {
        f >> idx(v, i);

        max = std::max(max, idx(v, i));
        min = std::min(min, idx(v, i));
        ++idx(app, idx(v, i));
    }

    diff = max - min;

    for(int i = k + 2; i <= n; ++i) {
        f >> idx(v, i);

        --idx(app, idx(v, i - k - 1));
        ++idx(app, idx(v, i));

        min = std::min(min, idx(v, i));
        max = std::max(max, idx(v, i));

        while(idx(app, min) == 0) {
            ++min;
        }
        while(idx(app, max) == 0) {
            --max;
        }

        diff = std::max(diff, max - min);
    }

    g << diff << std::endl;
}
