#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<int,int> decompose(long long int n, const std::vector<int>& primes) {
	std::unordered_map<int,int> res{};
	while (n > 1) {
		bool divided = false;
		for (auto p : primes) {
			if (n%p == 0) {
				res[p]++;
				n /= p;
				divided = true;
			}
		}
		if (!divided) {
			std::cout << "n=" << n << '\n';
			for (auto pair : res) std::cout << "[" << pair.first << "," << pair.second << "]" << '\n';
			throw std::exception();
		}
	}
	return res;
}

int get_sum_of_proper_divisors(int n, const std::vector<int>& primes) {
	std::vector<int> divisors = {1};
	std::unordered_map<int,int> p_divisors = decompose(n, primes);
	for (auto p_v : p_divisors) {
		const int initial_divisors_size = divisors.size();
		for (int i = 0; i < initial_divisors_size; i++) {
			for (int u = 1; u <= p_v.second; u++) {
				divisors.push_back(divisors[i]*(std::pow(p_v.first, u)));
			}
		}
	}
	int res = 0;
	for (auto d : divisors) res += d;
	return (res-n);
}

int main() {
	std::vector<int> primes{};
	std::ifstream f("../common/primes.txt");
	std::string line;
	while(std::getline(f, line)) {primes.push_back(std::stoi(line));}

	//// Writing abundant numbers to a separate file
	//std::ofstream g("abundant_numbers.txt");
	//for (int i = 1; i < 28'123; i++) {
	//	if (get_sum_of_proper_divisors(i, primes) > i) {
	//		std::cout << i << '\n';
	//		std::string s = std::to_string(i);
	//		g.write(s.data(), s.size());
	//		g.write("\n", 1);
	//	}
	//}

	std::unordered_map<int, int> abundant_numbers{};
	std::ifstream g("abundant_numbers.txt");
	while (std::getline(g, line)) {
		int n = std::stoi(line);
		abundant_numbers[n] = 1;
	}

	long long int res = 0;
	for (int i = 1; i < 28'123; i++) {
		// Checking if it can be represented as a sum of two abundant numbers
		bool representable = false;
		for (int a = 1; a < (i/2 + 1);a++) {
			if (abundant_numbers.find(a) != abundant_numbers.end()) {
				// a is abundant
				if (abundant_numbers.find(i - a) != abundant_numbers.end()) {
					representable = true;
					//std::cout << i << "=" << a << "+" << (i-a) << '\n';
				}
			}
		}
		if (!representable) {
			res += i;
			std::cout << "Not representable: " << i << '\n';
		}
	}

	std::cout << "result = " << res << '\n';

	return 0;
}
