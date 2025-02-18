#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using ll = long long;

auto num_digits(ll n)
{
    auto res = 0;
    while (n) {
        n /= 10;
        res++;
    }
    return res;
}

auto find_champernownes(std::vector<ll> n) -> std::vector<char>
{
    auto digits = 0;
    auto counter = 0;
    auto res = std::vector<char> {};
    while (!n.empty()) {
        if (auto d = n.back();
            d < digits) {
            n.pop_back();
            auto idx = d - (digits - num_digits(counter));
            res.push_back(std::to_string(counter).at(idx));
        }
        counter++;
        digits += num_digits(counter);
    }
    return res;
}

auto main() -> int
{
    auto r = find_champernownes(std::vector<ll> { 999999, 99999, 9999, 999, 99, 9, 0 });
    std::cout
        << std::ranges::fold_left(r, 1, [](ll l, char r) { return l * (r - '0'); })
        << '\n';
}
