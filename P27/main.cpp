#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>

int get_prime_seq_len(int a, int b, std::unordered_map<int,bool>& primes) {
	int n = 0;
	while (true) {
		// n*n + a*n + b is NOT prime
		if (primes.find(n*n + a*n + b) == primes.end()) {
			return n;
		}
		n++;
	}
}

int main() {

	std::unordered_map<int,bool> primes{};
	std::ifstream f("../common/primes.txt");
	std::string line;
	while(std::getline(f, line)) {
		primes[std::stoi(line)] = true;
	}

	int max_a = 0;
	int max_b = 0;
	int max_max_n = 0;
	// b MUST be a positive prime number
	// since the sequence at n=0 is just b, and that must be prime
	// 41 is chosen as a starting point because of Euler's n^2 + n + 41 sequence
	for (int b = 41; b <= 1000; b++) {
		// Ensuring b is prime
		if (primes.find(b) != primes.end()) {
			for (int a = -999; a <= 999; a++) {
				int max_n = get_prime_seq_len(a, b, primes);
				if (max_n > max_max_n) {
					max_max_n = max_n;
					max_a = a;
					max_b = b;
				}
			}
		}
	}

	std::cout << "a=" << max_a << ", b=" << max_b << ", length=" << max_max_n << '\n';
	std::cout << "result=" << (max_a*max_b) << '\n';

	return 0;
}
