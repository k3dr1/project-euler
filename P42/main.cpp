#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using ll = long long;
using std::ranges::fold_left;
using namespace std::views;

auto main() -> int
{
    std::string line {};
    auto f = std::fstream { "words.txt" };
    while (std::getline(f, line)) { }

    auto t_numbers = std::unordered_map<ll, bool> {};
    for (ll counter = 0ul;
        ll n : std::views::iota(1uz, 1'000'000uz)) {
        counter += n;
        t_numbers[counter] = true;
    }

    std::cout
        << fold_left(
               line
                   | split(',')
                   | transform([](auto&& r) { return std::string(r.begin() + 1, r.end() - 1); })
                   | transform([](const std::string& s) {
                         return fold_left(
                             s,
                             0ul,
                             [](const auto& l, const auto& r) { return l + (r - 'A' + 1); });
                     }),
               0ul,
               [&](const auto l, const auto r) { return l + (t_numbers.contains(r)); })
        << '\n';

    return 0;
}
