#include <iostream>
#include <ranges>

using ull = unsigned long long;

ull digit_factorial(ull x)
{
    switch (x) {
    case 0:
        return 1;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 6;
    case 4:
        return 24;
    case 5:
        return 120;
    case 6:
        return 720;
    case 7:
        return 5040;
    case 8:
        return 40320;
    case 9:
        return 362880;
    default: {
        std::cerr << "Invalid arg\n";
        return -1;
    }
    }
}

bool is_equal_factorial_sum(ull x)
{
    auto fac_sum { 0 };
    auto copy = x;
    while (copy > 0) {
        fac_sum += digit_factorial(copy % 10);
        copy /= 10;
    }
    return fac_sum == x;
}

int main()
{
    using std::views::iota;
    auto sum { 0 };
    for (auto&& n : iota(10, 10'000'000)) {
        if (is_equal_factorial_sum(n)) {
            std::cout << n << '\n';
            sum += n;
        }
    }
    std::cout << "sum=" << sum << '\n';
    return 0;
}
