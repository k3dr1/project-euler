#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using ll = long long;

auto main() -> int
{
    auto num_right_tris{0ul};
    auto best_p{0ul};
    for (ll p = 3; p <= 100'000; p++) {
        auto count{0ul};
        for (ll z = p / 3; z <= p; z++) {
            for (ll y = (p - z) / 2; y < (p - z); y++) {
                auto x = p - z - y;
                if (!(x * x + y * y == z * z)) continue;
                count++;
            }
        }
        if (num_right_tris < count) {
            best_p = p;
            num_right_tris = count;
        }
    }

    std::cout << "best_p = " << best_p << '\n';

    return 0;
}
