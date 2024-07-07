#include <exception>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

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

int main() {
	std::vector<int> primes{};

	std::ifstream f("../common/primes.txt");
	std::string line;
	while (std::getline(f, line, '\n')) {
		primes.push_back(std::stoi(line));
	}

	int i = 2;
	int n = 1;
	while (true) {

		std::unordered_map<int,int> p_divisors = decompose(n, primes);

		int num_divisors = 1;
		for (auto i : p_divisors) {
			num_divisors *= (i.second+1);
		}

		//std::cout << "n=" << n << " num_divisors=" << num_divisors << '\n';

		if (num_divisors > 500) {
			break;
		}

		n += i;
		i++;
	}
	std::cout << "result = " << n << '\n';
}
