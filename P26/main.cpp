#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>

// Basically checks the remainders produced when performing long division
int cycle(int d) {
	// d : divisor
	// n : dividend
	constexpr int EXPANSION_BOUND = 1'000'000;
	int cycle_len = 0;
	int n = 1;
	std::unordered_map<int,int> rem{};
	for (int i = 0; (i < EXPANSION_BOUND) && (n>0); i++) {
		if (n >= d) {
			if (rem.find(n) != rem.end()) {
				return (i - rem[n]);
			} else {
				rem[n] = i;
			}
			n %= d;
			n *= 10;
		} else {
			n *= 10;
		}
	}
	return 0;
}

int main() {

	int max_num = 0;
	int max_cycle = 0;
	for (int i = 1; i <= 1'000; i++) {
		int c = cycle(i);
		if (c > max_cycle) {
			max_num = i;
			max_cycle = c;
		}
	}

	std::cout << "result = " << max_num << " (with period length " << max_cycle << ")" << '\n';

	return 0;
}
