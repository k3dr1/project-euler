#include <iostream>
#include <ranges>
#include <unordered_map>

using ll = long long;

auto main() -> int
{
    auto m = std::unordered_map<ll, ll> {};

    for (auto n : std::views::iota(1uz, 1'000'000uz)) {
        m[n * (n + 1) / 2]     |= 1;
        m[n * (3 * n - 1) / 2] |= 2;
        m[n * (2 * n - 1)]     |= 4;
    }

    for (const auto& [k,v] : m) {
        if (v == 7) std::cout << k << '\n';
    }

    return 0;
}
