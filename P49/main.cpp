#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <unordered_map>
#include <string>
#include <fstream>

using ll = long long;

auto are_permutations(ll a, ll b) -> bool {
    auto digits = std::array<ll, 10> { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    while (a > 0) {
        digits[a % 10]++;
        a /= 10;
    }
    while (b > 0) {
        digits[b % 10]--;
        b /= 10;
    }
    return std::ranges::fold_left(digits, true, [](const auto l, const auto r) { return l && (r == 0); });
}

auto main() -> int
{
    std::unordered_map<ll, ll> primes {};
    auto f = std::fstream("../common/primes.txt");
    std::string line {};
    while (std::getline(f, line)) {
        primes[std::stoll(line)]++;
    }

    std::ranges::for_each(
        std::views::cartesian_product(std::views::iota(1000uz, 10'000uz), std::views::iota(1uz, 10'000uz))
            | std::views::filter([&](const auto& tpl) {
                  auto [b, d] = tpl;
                  return primes.contains(b)
                      && primes.contains(b + d)
                      && primes.contains(b + 2 * d)
                      && are_permutations(b, b + d)
                      && are_permutations(b + d, b + 2 * d);
              })
        ,
        [](const auto& tpl) {
            auto [b,d] = tpl;
            std::cout << std::to_string(b) + std::to_string(b+d) + std::to_string(b+2*d) << '\n';
        });

    return 0;
}
