#include <fstream>
#include <iostream>
#include <vector>

auto read_input(std::ifstream& f) -> std::vector<int>
{
    std::vector<int> result{};
    int count{ 0 };

    f >> count;

    result.reserve(static_cast<std::size_t>(count) + 1);
    result.push_back(0);

    for(int i = 0; i < count; ++i) {
        int tmp{ 0 };
        f >> tmp;
        result.push_back(tmp);
    }

    return result;
}

auto run_queries(std::ifstream& f, std::vector<int> const& v) -> void
{
    std::ofstream g{ "cautbin.out" };
    int count{ 0 };

    std::size_t logn{ 1 };
    while(logn <= v.size()) {
        logn *= 2;
    }

    f >> count;

    for(int i = 0; i < count; ++i) {
        int action{ 0 };
        int num{ 0 };

        f >> action >> num;

        switch(action) {
        case 0:
        case 1: {
            std::size_t j = 0;
            for(std::size_t lg = logn; lg != 0; lg /= 2) {
                if(j + lg < v.size() && v[j + lg] <= num) {
                    j += lg;
                }
            }

            if(action == 0 && v[j] != num) {
                g << "-1\n";
            }
            else {
                g << j << '\n';
            }

            break;
        }
        case 2: {
            std::int64_t j{ static_cast<std::int64_t>(v.size()) - 1 };
            for(auto lg = static_cast<std::int64_t>(logn); lg != 0; lg /= 2) {
                if(j - lg > 0 && v[static_cast<std::uint64_t>(j - lg)] >= num) {
                    j -= lg;
                }
            }

            g << j << '\n';

            break;
        }
        default: {
            break;
        }
        }
    }
}

auto main() noexcept -> int
{
    std::ifstream f{ "cautbin.in" };
    run_queries(f, read_input(f));
}
