#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

struct point_t
{
    double x{ 0 };
    double y{ 0 };

    constexpr point_t() noexcept = default;
    point_t(double const a, double const b) noexcept
        : x{ a }
        , y{ b }
    {
    }
    point_t(point_t const&) noexcept = default;
    point_t(point_t&&) noexcept = default;
    ~point_t() noexcept = default;

    auto operator=(point_t const&) noexcept -> point_t& = default;
    auto operator=(point_t&&) noexcept -> point_t& = default;

    inline auto operator<(point_t const& other) const -> bool
    {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }

    inline auto operator==(point_t const& other) const -> bool
    {
        auto eq = [](double const a, double const b) -> bool {
            return std::abs(a - b) <= 0.0001;
        };

        return eq(x, other.x) && eq(y, other.y);
    }
};

auto main() noexcept -> int
{
    std::ifstream f{ "sea.in" };
    std::ofstream g{ "sea.out" };

    std::vector<point_t> vapoare{};

    std::size_t n{ 0 };
    std::size_t m{ 0 };

    f >> n >> m;

    vapoare.reserve(n);

    for(std::size_t i = 0; i < n; ++i) {
        double x{ 0 };
        double y{ 0 };

        f >> x >> y;
        vapoare.emplace_back(x, y);
    }

    std::sort(vapoare.begin(), vapoare.end());
    g << std::setprecision(4) << std::fixed;

    std::size_t last{ 0 };

    auto dist = [](double const a, double const b) -> double {
        return a * a + b * b;
    };

    for(std::size_t i = 0; i < m; ++i) {
        double x{ 0 };
        int count{ 0 };

        f >> x >> count;

        while(last < n && vapoare[last].x < x) {
            ++last;
        }

        for(int j = 1; j < static_cast<int>(last); ++j) {
            /*
                        if(j <= 0) {
                            continue;
                        }*/
            /*
            auto& tmp = vapoare[static_cast<std::size_t>(j)];
            auto& tmp_prev = vapoare[static_cast<std::size_t>(j - 1)];
            */
            if(j > 0) {
                auto& tmp = vapoare[static_cast<std::size_t>(j)];
                auto& tmp_prev = vapoare[static_cast<std::size_t>(j - 1)];

                if(dist(tmp.x - x, tmp.y) > dist(tmp_prev.x - x, tmp_prev.y)) {
                    std::swap(tmp, tmp_prev);
                    j -= 2;
                }
            }

            /*
            if(std::hypot(tmp.x - x, tmp.y) >
               std::hypot(tmp_prev.x - x, tmp_prev.y)) {
                std::swap(tmp, tmp_prev);
                j -= 2;
            }*/

            /*
            if(dist(tmp.x - x, tmp.y) > dist(tmp_prev.x - x, tmp_prev.y)) {
                std::swap(tmp, tmp_prev);
                j -= 2;
            }*/
        }

        auto& elem = vapoare[last - static_cast<std::size_t>(count)];
        g << std::hypot(elem.x - x, elem.y) << '\n';

        /*
        auto comp = [p = point_t{ x, 0 }](point_t const& a,
                                          point_t const& b) -> bool {
            return std::hypot(a.x - p.x, a.y - p.y) >
                   std::hypot(b.x - p.x, b.y - p.y);
        };

        std::priority_queue<point_t, std::vector<point_t>, decltype(comp)> q{
            comp
        };

        auto end =
            std::lower_bound(vapoare.begin(), vapoare.end(), point_t{ x, 0 });

        for(auto it = vapoare.begin(); it != end; ++it) {
            q.push(*it);
        }

        int c{ 0 };
        point_t to{ 0, 0 };
        while(!q.empty() && c++ < count) {
            to = q.top();
            q.pop();
        }

        g << std::hypot(to.x - x, to.y) << '\n';
        */
    }
}
