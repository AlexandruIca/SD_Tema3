#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <vector>

template<int N>
constexpr auto is_prime() noexcept -> bool
{
    static_assert(N >= 0, "");

    for(int i = 2; i <= N / 2; ++i) {
        if(N % i == 0) {
            return false;
        }
    }

    return true;
}

template<typename T, int N>
struct hash
{
    static_assert(std::is_integral<T>::value, "");
    static_assert(is_prime<N>(), "");

private:
    std::array<std::vector<T>, N> m_data;

    constexpr auto index(T const num) -> std::size_t
    {
        return static_cast<std::size_t>(num % N);
    }

public:
    hash() = default;
    hash(hash const&) = delete;
    hash(hash&&) = delete;
    ~hash() noexcept = default;

    auto operator=(hash const&) -> hash& = delete;
    auto operator=(hash &&) -> hash& = delete;

    constexpr auto find(T const num) -> typename std::vector<T>::iterator
    {
        auto& data = m_data[this->index(num)];

        for(auto it = data.begin(); it != data.end(); ++it) {
            if(*it == num) {
                return it;
            }
        }

        return data.end();
    }

    constexpr auto contains(T const num) -> bool
    {
        return this->find(num) != m_data[this->index(num)].end();
    }

    constexpr auto add(T const num) -> void
    {
        auto const idx = this->index(num);

        if(!this->contains(num)) {
            m_data[idx].push_back(num);
        }
    }

    constexpr auto remove(T const num) -> void
    {
        auto it = this->find(num);
        auto const idx = this->index(num);

        if(it != m_data[idx].end()) {
            m_data[idx].erase(it);
        }
    }
};

auto main() noexcept -> int
{
    std::ifstream f{ "hashuri.in" };
    std::ofstream g{ "hashuri.out" };

    hash<int, 666013> h;
    int n{ 0 };

    f >> n;

    for(int i = 0; i < n; ++i) {
        int a{ 0 };
        int b{ 0 };

        f >> a >> b;

        switch(a) {
        case 1: {
            h.add(b);
            break;
        }
        case 2: {
            h.remove(b);
            break;
        }
        case 3: {
            if(h.contains(b)) {
                g << "1\n";
            }
            else {
                g << "0\n";
            }
            break;
        }
        default: {
            break;
        }
        }
    }
}
