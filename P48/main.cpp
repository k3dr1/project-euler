#include <iostream>
#include <vector>
#include <ranges>

using ll = long long;

auto main() -> int {

    auto mod = 10'000'000'000ull;
    auto res{0ull};
    for (auto k : std::views::iota(1uz, 1'000uz)) {
        auto q = 1ull;
        for (ll i = 0; i < k; i++) {
            q *= k;
            q %= mod;
        }
        res %= mod;
        res += q;
    }

    std::cout << res << '\n';

    return 0;
}
