#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

using ll = long long;

auto pentagon = [](ll n) { return n * (3 * n - 1) / 2; };
auto is_pentagon = [](ll p) { return p == pentagon((1 + std::sqrt(1 + 24 * p)) / 6); };

auto main() -> int
{
    // Yea it's O(n^2)...
    auto N = 10'000;
    for (ll i = 1; i < N; i++) {
        for (ll j = 1; j < i; j++) {
            auto P_i = pentagon(i);
            auto P_j = pentagon(j);
            if (is_pentagon(P_i - P_j) && is_pentagon(P_i + P_j)) {
                std::cout << "P_i = " << P_i << '\n';
                std::cout << "P_j = " << P_j << '\n';
                std::cout << "D = " << P_i - P_j << '\n';
            }
        }
    }

    return 0;
}
