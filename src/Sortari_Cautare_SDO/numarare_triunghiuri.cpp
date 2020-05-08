#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

auto count(std::vector<int>& v) -> int
{
    std::size_t const n = v.size();
    int count{ 0 };

    for(std::size_t i = 0; i < n - 2; ++i) {
        for(std::size_t j = i + 1; j < n - 1; ++j) {
            for(std::size_t k = j + 1; k < n; ++k) {
                if(v[i] + v[j] >= v[k]) {
                    ++count;
                }
                else {
                    break;
                }
            }
        }
    }

    return count;
}

auto main() noexcept -> int
{
    std::ifstream f{ "nrtri.in" };
    std::ofstream g{ "nrtri.out" };

    int num{ 0 };
    std::vector<int> nums{};

    f >> num;
    nums.reserve(static_cast<std::size_t>(num));

    for(int i = 0; i < num; ++i) {
        int x{ 0 };
        f >> x;
        nums.push_back(x);
    }

    std::sort(nums.begin(), nums.end());
    g << count(nums) << std::endl;
}
