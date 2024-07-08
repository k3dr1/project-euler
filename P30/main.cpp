#include <iostream>

bool representable4(int n) {
	const int initial_n = n;
	int sum = 0;
	while (n > 0) {
		int rightmost_digit = n%10;
		n /= 10;
		sum += (rightmost_digit*rightmost_digit*rightmost_digit*rightmost_digit);
	}
	return (sum == initial_n);
}

bool representable5(int n) {
	const int initial_n = n;
	int sum = 0;
	while (n > 0) {
		int rightmost_digit = n%10;
		n /= 10;
		sum += (rightmost_digit*rightmost_digit*rightmost_digit*rightmost_digit*rightmost_digit);
	}
	return (sum == initial_n);
}

int main() {

	int res = 0;
	// I just chose million randomly, i'm too lazy to prove that there
	// are no numbers above a million that can be represented
	for (int i = 10; i < 1'000'000; i++) {
		if (representable5(i))  {
			std::cout << i << '\n';
			res += i;
		}
	}

	std::cout << "result = " << res << '\n';

	return 0;
}
