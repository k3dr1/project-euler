#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

long long factorial(long long n) {
	long long res = 1;
	for (; n > 1; n--) { res *= n; }
	return res;
}

std::string get_permutation(long long idx, std::vector<char> digits) {
	if (digits.size() == 1) {
		return std::to_string(digits[0]);
	} else {
		long long interval_idx = idx/factorial(digits.size() - 1);
		long long new_idx = idx - interval_idx*factorial(digits.size() - 1);
		char found_digit = digits[interval_idx];
		digits.erase(digits.begin() + interval_idx);
		return ((found_digit) + get_permutation(new_idx, digits));
	}
}

int main() {
	std::vector<char> digits = {'0','1','2','3','4','5','6','7','8','9'};

	std::cout << std::setw(2) << (1'000'000 + 1) << " " << get_permutation(1'000'000, digits) << '\n';
	//for (int i = 0; i < factorial(digits.size()); i++) {
	//	std::cout << std::setw(2) << (i+1) << " " << get_permutation(i, digits) << '\n';
	//}

	return 0;
}
