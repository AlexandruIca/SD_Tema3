#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

auto main() noexcept -> int
{
    std::ifstream f{ "heapuri.in" };
    std::ofstream g{ "heapuri.out" };

    using priority_queue_t =
        std::priority_queue<int, std::vector<int>, std::greater<>>;

    priority_queue_t nums{};
    priority_queue_t deleted{};
    std::array<int, 200'001> order{};
    std::size_t idx{ 0 };

    int n{ 0 };

    f >> n;
    order.fill(0);

    for(int i = 0; i < n; ++i) {
        int op{ 0 };

        f >> op;

        switch(op) {
        case 1: {
            int x{ 0 };

            f >> x;
            order[++idx] = x;
            nums.push(x);

            break;
        }
        case 2: {
            std::size_t index{ 0 };

            f >> index;
            deleted.push(order[index]);

            break;
        }
        case 3: {
            while(!nums.empty()) {
                int const min = nums.top();

                if(deleted.empty() || deleted.top() != min) {
                    g << min << '\n';
                    break;
                }

                deleted.pop();
                nums.pop();
            }

            break;
        }
        default: {
            break;
        }
        }
    }
}
