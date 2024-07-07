#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
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
	while (std::getline(f, line, '\n')) {
		primes.push_back(std::stoi(line));
	}

	int sum = 0;
	for (int i = 2; i < 10'000; i++) {
		int s = get_sum_of_proper_divisors(i, primes);
		int z = get_sum_of_proper_divisors(s, primes);
		if ((i == z) && (i != s)) {
			std::cout << i << '\n';
			sum += i;
		}
	}

	std::cout << "result = " << sum << '\n';

	return 0;
}
