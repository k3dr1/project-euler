#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

using ll = long long;

auto main() -> int
{
    std::unordered_map<std::string, int> primes {};
    auto f = std::fstream("../common/primes.txt");
    std::string line {};
    while (std::getline(f, line)) {
        primes[line]++;
    }

    std::cout << "Max pandigital prime: "
              << std::ranges::fold_left(
                     primes
                         | std::views::keys
                         | std::views::filter(
                             [](auto n) {
                                 return std::ranges::fold_left(
                                     std::views::iota(1uz, n.length() + 1),
                                     true,
                                     [n](auto l, auto r) { return l & n.contains(std::to_string(r)); });
                             }),
                     0ul,
                     [](const auto l, const auto r) { return std::max(l, std::stoul(r)); })
              << '\n';
}
