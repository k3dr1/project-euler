#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

using ll = long long;

auto main() -> int {
    std::unordered_map<ll, ll> primes {};
    auto f = std::fstream("../common/primes.txt");
    std::string line {};
    while (std::getline(f, line)) {
        primes[std::stoll(line)]++;
    }
    auto primes_sorted = std::vector<ll>(
        (primes | std::views::keys).begin(),
        (primes | std::views::keys).end());
    std::ranges::sort(primes_sorted);

    auto prime = 2;
    auto max_terms = 0;
    for (ll terms = 1; terms < 1000; terms++) {
        for (ll idx = 0; idx <= 100'000; idx++) {
            auto sum = 0ul;
            for (ll j = 0; j < terms; j++) {
                sum += primes_sorted[idx + j];
            }
            if ((sum < 1'000'000) && primes.contains(sum) && (max_terms < terms)) {
                prime = sum;
                max_terms = terms;
            }
        }
    }

    std::cout << "prime: " << prime << '\n'
              << "max_terms: " << max_terms << '\n'
              << '\n';

    return 0;
}
