#include <cmath>
#include <iostream>
#include <unordered_map>

int main() {

	constexpr int BIG_PRIME = 15485863;

	std::unordered_map<double,int> m;
	for (int a = 2; a <= 100; a++) {
		for (int b = 2; b <= 100; b++) {
			double c = std::pow(double(a),double(b));
			std::cout << c << '\n';
			m[c]++;
		}
	}

	int res = 0;
	for (auto p : m) {
		res++;
	}
	std::cout << "result = " << res << '\n';

	return 0;
}
