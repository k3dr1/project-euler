#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <unordered_map>

using ll = long long;

auto main() -> int
{
    std::unordered_map<ll, ll> primes {};
    auto f = std::fstream("../common/primes.txt");
    std::string line {};
    while (std::getline(f, line)) {
        primes[std::stoll(line)]++;
    }

    auto not_representable = [&](auto n) {
        for (ll sq = 1; 2 * sq * sq < n; sq++)
            if (primes.contains(n - 2 * sq * sq))
                return false;
        return true;
    };

    for (auto n : std::views::iota(1, 100'000)
            | std::views::transform([](auto n) { return n * 2 + 1; })
            | std::views::filter([&](auto n) { return !primes.contains(n) & not_representable(n); })) {
        std::cout << n << '\n';
    }

    return 0;
}
