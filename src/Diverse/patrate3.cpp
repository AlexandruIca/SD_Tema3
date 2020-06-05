#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

struct checked_double
{
    static constexpr double margin = 0.00001;
    double value{ 0 };

    constexpr checked_double() noexcept = default;
    constexpr checked_double(checked_double const&) noexcept = default;
    constexpr checked_double(checked_double&&) noexcept = default;
    ~checked_double() noexcept = default;

    constexpr auto operator=(checked_double const&) noexcept
        -> checked_double& = default;
    constexpr auto operator=(checked_double&&) noexcept
        -> checked_double& = default;

    constexpr auto operator=(double const val) -> checked_double&
    {
        value = val;
        return *this;
    }

    constexpr auto operator()() const noexcept -> double
    {
        return value;
    }
};

constexpr auto abs(checked_double const num) noexcept -> checked_double
{
    return num() < 0 ? checked_double{ -num() } : num;
}

constexpr auto operator<(checked_double const a,
                         checked_double const b) noexcept -> bool
{
    return a() + checked_double::margin < b();
}

constexpr auto operator==(checked_double const a,
                          checked_double const b) noexcept -> bool
{
    return abs(checked_double{ a() - b() })() < checked_double::margin;
}

constexpr auto operator+(checked_double const a,
                         checked_double const b) noexcept -> checked_double
{
    return { a() + b() };
}

constexpr auto operator-(checked_double const a,
                         checked_double const b) noexcept -> checked_double
{
    return { a() - b() };
}

using coord_t = std::pair<checked_double, checked_double>;

constexpr auto operator==(coord_t const& a, coord_t const& b) noexcept -> bool
{
    return (a.first == b.first) && (a.second == b.second);
}

auto operator/(coord_t const& a, int const b) noexcept -> coord_t
{
    return { checked_double{ a.first() / b },
             checked_double{ a.second() / b } };
}

auto operator+(coord_t const& a, coord_t const& b) noexcept -> coord_t
{
    return { checked_double{ a.first() + b.first() },
             checked_double{ a.second() + b.second() } };
}

auto main() noexcept -> int
{

    std::ifstream f{ "patrate3.in" };
    std::ofstream g{ "patrate3.out" };

    std::vector<coord_t> points{};
    std::size_t n{ 0 };
    std::size_t count{ 0 };

    f >> n;
    points.reserve(n);

    for(std::size_t i = 0; i < n; ++i) {
        double x{ 0 };
        double y{ 0 };

        f >> x >> y;

        points.emplace_back(checked_double{ x }, checked_double{ y });
    }

    std::sort(points.begin(), points.end());

    for(std::size_t i = 0; i < n - 1; ++i) {
        for(std::size_t j = i + 1; j < n; ++j) {
            auto const mid = (points[i] + points[j]) / 2;
            auto const distance = std::make_pair(mid.first - points[i].first,
                                                 mid.second - points[i].second);
            auto const point1 = std::make_pair(mid.first + distance.second,
                                               mid.second - distance.first);
            auto const point2 = std::make_pair(mid.first - distance.second,
                                               mid.second + distance.first);

            auto from = points.begin();
            std::advance(from, i);
            auto to = points.end();

            if(std::binary_search(from, to, point1) &&
               std::binary_search(from, to, point2)) {
                ++count;
            }
        }
    }

    g << count << std::endl;
}
