#include <algorithm>
#include <charconv>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>

#include "../common/utility.cpp"

int main()
{
    std::unordered_map<int, int> products = {};
    auto digits = std::string("123456789");
    do {
        for (auto&& d : std::views::iota(2uz, 9uz)) {
            int rhs_num {};
            auto lhs = std::string_view(digits).substr(0, d);
            auto rhs = std::string_view(digits).substr(d);
            std::from_chars(rhs.data(), rhs.data() + rhs.size(), rhs_num);
            for (auto&& f : std::views::iota(1uz, lhs.size())) {
                auto a = lhs.substr(0, f);
                auto b = lhs.substr(f);
                int a_num {};
                int b_num {};
                std::from_chars(a.data(), a.data() + a.size(), a_num);
                std::from_chars(b.data(), b.data() + b.size(), b_num);
                if (a_num * b_num == rhs_num)
                    products[rhs_num]++;
            }
        }
    } while (std::ranges::next_permutation(digits).found);

    auto sum { 0 };
    for (auto&& pair : products) {
        sum += pair.first;
    }
    std::cout << "sum=" << sum << '\n';

    return 0;
}
