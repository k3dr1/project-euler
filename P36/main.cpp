#include <algorithm>
#include <bitset>
#include <iostream>
#include <ranges>
#include <string>

auto is_palindrome(std::string s) -> bool
{
    std::string u = s;
    std::reverse(u.begin(), u.end());
    return u == s;
}

auto main() -> int
{
    auto counter = 0ul;
    for (auto n : std::views::iota(1uz, 1'000'000uz)) {
        auto base2 = std::bitset<32>(n).to_string();
        base2 = base2.substr(base2.find_first_not_of('0'));
        if (is_palindrome(std::to_string(n)) && is_palindrome(base2))
            counter += n;
    }

    std::cout << counter << '\n';

    return 0;
}
