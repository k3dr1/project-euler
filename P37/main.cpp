#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

auto get_left_truncations(std::string s)
{
    std::vector<std::string> res {};
    do {
        res.push_back(s);
        s = s.substr(1);
    } while (s.length());
    return res;
}

auto get_right_truncations(std::string s)
{
    std::vector<std::string> res {};
    do {
        res.push_back(s);
        s = s.substr(0, s.length() - 1);
    } while (s.length());
    return res;
}

int main()
{
    std::unordered_map<std::string, int> primes {};
    auto f = std::fstream("../common/primes.txt");
    std::string line {};
    while (std::getline(f, line)) {
        primes[line]++;
    }

    auto sum { 0ul };
    for (auto n : std::views::iota(10uz, 1'000'000uz)) {
        sum += std::ranges::fold_left(
                   get_left_truncations(std::to_string(n))
                       | std::views::transform([&](const auto k) {
                             return primes.contains(k);
                         }),
                   true,
                   std::logical_and<> {})
                && std::ranges::fold_left(
                    get_right_truncations(std::to_string(n))
                        | std::views::transform([&](const auto k) {
                              return primes.contains(k);
                          }),
                    true,
                    std::logical_and<> {})
            ? n
            : 0;
    }

    std::cout << "Sum " << sum << '\n';
}
