#include <iostream>
#include <ranges>

int ones(int x) {
    return x%10;
}

int tens(int x) {
    return (x%100)/10;
}

int main() {
    using std::views::iota;
    auto A{1};
    auto B{1};
    for (auto&& a : iota(10, 100)) {
        for (auto&& b : iota(10, 100)) {
            if ((ones(a) == tens(b))
                && (double(tens(a)) / double(ones(b)) == (double(a) / double(b)))
                && (a != b)) {
                std::cout << a << '/' << b << '\n';
                A*=a;
                B*=b;
            }
        }
    }

    std::cout << "Prod:" << A << '/' << B << '\n';
    std::cout << "simplify and submit denominator" << '\n';

    return 0;
}
