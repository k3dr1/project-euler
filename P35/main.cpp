#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

auto get_rotations(std::string s)
{
    auto res = std::vector<std::string> {};
    auto v = s;
    do {
        res.push_back(v);
        v = v.substr(1) + v.at(0);
    } while (v != s);
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

    auto counter = std::ranges::fold_left(
        std::views::iota(2uz, 1'000'000uz),
        0ul,
        [&](const auto l, const auto n) {
            return l + std::ranges::fold_left(
                get_rotations(std::to_string(n)), 
                true, 
                [&](bool l, const auto& u) { return l && primes.contains(u); });
        });

    std::cout << "Number of circular primes: " << counter << '\n';

    return 0;
}
