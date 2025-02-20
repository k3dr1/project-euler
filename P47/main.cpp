#include <algorithm>
#include <cmath>
#include <concepts>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <unordered_map>

using ll = long long;

auto num_distinct_factors(ll n, 
         const std::unordered_map<ll, ll>& primes, 
         const std::vector<ll>& p_vec,
         std::unordered_map<ll, ll>& memo) -> ll {
    if (primes.contains(n)) {
        return 1;
    } 
    if (memo.contains(n)) {
        return memo.at(n);
    }
    auto ndiv = 0;
    auto original_n = n;
    for (ll i = 0; (1 < n) && (i < primes.size()) && (ndiv <= 4); i++) {
        if (n%p_vec[i] == 0) {
            while (n%p_vec[i] == 0) {
                n /= p_vec[i];
            }
            ndiv++;
            i = 0;
        }
    }
    memo[original_n] = ndiv;
    return ndiv;
}

auto main() -> int
{
    std::unordered_map<ll, ll> primes_sorted {};
    auto f = std::fstream("../common/primes.txt");
    std::string line {};
    while (std::getline(f, line)) {
        primes_sorted[std::stoll(line)]++;
    }
    std::vector<ll> p_vec = std::vector<ll>(
        std::begin(primes_sorted | std::views::keys),
        std::end(primes_sorted | std::views::keys));
    std::ranges::sort(p_vec, std::ranges::less_equal());

    auto memo = std::unordered_map<ll,ll>{};
    for (auto n : std::views::iota(1uz, 500'000uz)) {
        std::cout << n << '\n';
        if (num_distinct_factors(n, primes_sorted, p_vec, memo) == 4
            && num_distinct_factors(n+1, primes_sorted, p_vec, memo) == 4
            && num_distinct_factors(n+2, primes_sorted, p_vec, memo) == 4
            && num_distinct_factors(n+3, primes_sorted, p_vec, memo) == 4
        ) {
            std::cout << n+0 << ":" << num_distinct_factors(n+0, primes_sorted, p_vec, memo) << '\n';
            std::cout << n+1 << ":" << num_distinct_factors(n+1, primes_sorted, p_vec, memo) << '\n';
            std::cout << n+2 << ":" << num_distinct_factors(n+2, primes_sorted, p_vec, memo) << '\n';
            std::cout << n+3 << ":" << num_distinct_factors(n+3, primes_sorted, p_vec, memo) << '\n';
            break;
        }
    }
}
