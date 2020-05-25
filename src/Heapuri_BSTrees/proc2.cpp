#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <utility>

struct thread
{
    int workload{ 0 };
    int id{ 0 };

    thread() noexcept = default;
    thread(thread const&) noexcept = default;
    thread(thread&&) noexcept = default;
    ~thread() noexcept = default;

    thread(int const workload_, int const id_)
        : workload{ workload_ }
        , id{ id_ }
    {
    }

    auto operator=(thread const&) noexcept -> thread& = default;
    auto operator=(thread&&) noexcept -> thread& = default;

    auto operator==(thread const& other) const noexcept -> bool
    {
        return workload == other.workload && id == other.id;
    }

    auto operator<(thread const& other) const noexcept -> bool
    {
        return std::tie(workload, id) > std::tie(other.workload, other.id);
    }
};

std::priority_queue<thread, std::vector<thread>> consumers;
std::priority_queue<int, std::vector<int>, std::greater<>> workers;

auto main() noexcept -> int
{
    std::ifstream f{ "proc2.in" };
    std::ofstream g{ "proc2.out" };

    int n{ 0 };
    int m{ 0 };

    f >> n >> m;

    for(int i = 0; i < m; ++i) {
        workers.push(i);
    }

    for(int i = 0; i < m; ++i) {
        int s{ 0 };
        int d{ 0 };

        f >> s >> d;

        while(!consumers.empty() && consumers.top().workload <= s) {
            workers.push(consumers.top().id);
            consumers.pop();
        }

        thread t{ s + d, workers.top() };

        g << t.id + 1 << '\n';

        workers.pop();
        consumers.push(t);
    }
}
