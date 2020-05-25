#include <array>
#include <fstream>
#include <utility>
#include <vector>

template<typename T>
inline auto idx(T& vec, int index) -> typename T::value_type&
{
    return vec[static_cast<std::size_t>(index)];
}

std::array<int, 500'000> srd;
std::array<int, 500'000> rsd;

std::vector<std::pair<int, int>> node;

std::size_t pos{ 0 };
constexpr int none = 0;

auto construct(int const left, int const right) -> int
{
    if(left > right) {
        return none;
    }

    auto const elem = rsd[pos++];
    int i = left;

    while(i <= right) {
        if(idx(srd, i) == elem) {
            break;
        }

        ++i;
    }

    idx(node, elem).first = construct(left, i - 1);
    idx(node, elem).second = construct(i + 1, right);

    return elem;
}

auto main() noexcept -> int
{
    std::ifstream f{ "curatenie.in" };
    std::ofstream g{ "curatenie.out" };

    std::size_t n{ 0 };

    f >> n;

    node.resize(static_cast<std::size_t>(n + 1));

    for(std::size_t i = 0; i < n; ++i) {
        f >> srd[i];
    }
    for(std::size_t i = 0; i < n; ++i) {
        f >> rsd[i];
    }

    static_cast<void>(construct(0, static_cast<int>(n) - 1));

    for(std::size_t i = 1; i <= n; ++i) {
        g << node[i].first << ' ' << node[i].second << '\n';
    }
}
