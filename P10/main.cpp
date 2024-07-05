// Code taken from my implementation of a segmented sieve of eratosthenes
// https://github.com/k3dr1/segmented-prime-sieve

#include <iostream>
#include <cmath>
#include <vector>

bool is_prime(int n) {
	for (int i = 2; i <= (int)std::sqrt(n); i++) {
		if (n%i == 0) return false;
	}
	return true;
}

std::vector<int> standard_sieve(int n) {
	// output vector that will contain all the found primes in the range [2,n)
	std::vector<int> found_primes = {};
	// each bool at index i denotes the primality of i, initially everything is set to true
	std::vector<bool> A = std::vector<bool>(n, true);
	A[0] = false; // 0 is not a prime
	A[1] = false; // 1 is not a prime
	for (int i = 2; i <= (int)std::sqrt(n); i++) {
		// if A[i] is prime
		if (A[i] != false) {
			// set all of its multiples in the range to false
			// only multiples from i*i and up need to be set, everything
			// less than that will have been covered by other nums
			for (int j = i*i; j < n; j += i) {
				A[j] = false;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (A[i] == true) {
			found_primes.push_back(i);
		}
	}
	return found_primes;
}

std::vector<int> segmented_sieve(int n) {
	long long int delta = (int)std::sqrt(n);
	long long int m = delta*2 - 1;
	std::vector<int> found_primes = standard_sieve(delta);

	// m is the topmost value of the segment
	// meaning the segment is [m-delta+1,m]
	// number k has index k-(m-delta+1) = k-m+delta-1
	// number at index i has value m-delta+1+i
	for (; m < n; m += delta) {
		// faster than std::vector<bool>, although non-standard g++ supports variable length arrays 
		// as an extension, an alternative to this is using "new char[delta]" to allocate an array on the heap
		char A[delta] = {};
		for (int i = 0; i < delta; i++) A[i] = true;

		int i = 0;
		while (found_primes[i] <= (int)std::sqrt(m)) {
			int p = found_primes[i];
			// finds the index corresponding to the smallest multiple of p in the segment,
			// and then incrementally mark all the multiples as non-prime
			for (int multiple = (p - ((m-delta+1)%p))%p; multiple < delta; multiple += p) {
				A[multiple] = false;
			}
			i++;
		}
		for (int i = 0; i < delta; i++) {
			if (A[i] == true) {
				found_primes.push_back(m-delta+1+i);
			}
		}
	}
	return found_primes;
}

int main() {

	long long int res = 0;
	long long int N = 2'000'000;
	auto primes =  standard_sieve(N);
	for (auto p : primes) {
		res += p;
	}
	// res = 142913828922
	std::cout << res << '\n';

	return 0;
}
