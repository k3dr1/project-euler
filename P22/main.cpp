#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

// Comparator for names
bool alphabet_cmp(std::string& a, std::string& b) {
	int i = 0;
	int j = 0;
	while ((i < a.size()) && (j < b.size())) {
		if (a[i] == b[j]) {i++; j++;}
		if (a[i] >  b[j]) return false;
		if (a[i] <  b[j]) return true;
	}
	std::cout << "HMMM WEIRD NAMES DETECTED: " << a << ":" << b << '\n';
	return false;
}

int name_score(std::string& s) {
	int res = 0;
	for (char c : s) res += (c - 64);
	return res;
}

int main() {
	std::vector<std::string> names{};
	std::ifstream f("names.txt");

	std::string name = {};
	while (std::getline(f, name, ',')) {
		names.push_back(name.substr(1, name.size() - 2));
	}
	std::sort(names.begin(), names.end(), alphabet_cmp);

	long long int res = 0;
	for (int i = 0; i < names.size(); i++) {
		res += (i+1)*name_score(names[i]);
	}

	std::cout << "result = " << res << '\n';

	return 0;
}
