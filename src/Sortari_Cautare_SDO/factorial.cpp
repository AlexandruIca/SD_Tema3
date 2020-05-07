#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

constexpr std::array<int, 13> pow5{ { 5,
                                      25,
                                      125,
                                      625,
                                      3125,
                                      15625,
                                      78125,
                                      390625,
                                      1953125,
                                      9765625,
                                      48828125,
                                      244140625,
                                      1220703125 } };

auto main() noexcept -> int
{
    std::ifstream f{ "fact.in" };
    std::ofstream g{ "fact.out" };

    int num{ 0 };
    std::int64_t count{ 0 };

    f >> num;

    if(num == 0) {
        g << '1' << std::endl;
        return EXIT_SUCCESS;
    }

    std::size_t idx{ 0 };
    for(int i = 5;; i += 5) {
        // int j = i;
        /*
                while(j % 5 == 0) {
                    ++count;
                    j /= 5;
                }

                if(count > num) {
                    g << "-1" << std::endl;
                    return EXIT_SUCCESS;
                }
                if(count == num) {
                    g << i << std::endl;
                    return EXIT_SUCCESS;
                }*/
        if(pow5[idx] == i) {
            ++idx;
            count += idx;
        }
        else {
            ++count;
        }
        if(count > num) {
            std::cout << "-1" << std::endl;
            return EXIT_SUCCESS;
        }
        if(count == num) {
            std::cout << i << std::endl;
            return EXIT_SUCCESS;
        }
    }
}
