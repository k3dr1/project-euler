#include <algorithm>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <vector>

const std::vector<int> pascal = {0, // padding num to make addressing easier, kinda like a 1-indexed array
75,
95,64,
17,47,82,
18,35,87,10,
20, 4,82,47,65,
19, 1,23,75, 3,34,
88, 2,77,73, 7,63,67,
99,65, 4,28, 6,16,70,92,
41,41,26,56,83,40,80,70,33,
41,48,72,33,47,32,37,16,94,29,
53,71,44,65,25,43,91,52,97,51,14,
70,11,33,28,77,73,17,78,39,68,17,57,
91,71,52,38,17,14,91,43,58,50,27,29,48,
63,66, 4,68,89,53,67,30,73,16,69,87,40,31,
 4,62,98,27,23, 9,70,98,73,93,38,53,60, 4,23,
};


// returns end node
int triangulate(int n) {
	return n*(n+1)/2;
}

// Inverse of the n(n+1)/2 function
// returns the current row
int inverse_triangulate(int n) {
	return std::ceil((std::sqrt(8*double(n)+1)-1)/2);
}

int left_parent(int n) {
	int row = inverse_triangulate(n);
	if (triangulate(row-1) + 1 == n) {
		// Leftmost node in the row, has no left parent
		return -1;
	} else {
		return (n - row);
	}
}

int right_parent(int n) {
	int row = inverse_triangulate(n);
	if (triangulate(row) == n) {
		// Rightmost node in the row, has no right parent
		return -1;
	} else {
		return (n - row + 1);
	}
}

int best_path(int n) {
	static std::unordered_map<int,int> memo{};
	if (n == -1) return 0;
	if (n == 1) return pascal[1];
	if (memo.find(n) != memo.end()) {
		return memo[n];
	} else {
		memo[n] = pascal[n] + std::max(best_path(left_parent(n)), best_path(right_parent(n)));
		return memo[n];
	}
}

int main() {

	//for (int i = 1; i <= 28; i++) {
	//	std::cout << i << " - " << inverse_triangulate(i) << '\n';
	//}

	// Take the last element, find out which row it is on, go to the previous row, find its last element, add one
	// now you have arrived at the first element of the last row
	int last_row_beginning = triangulate(inverse_triangulate(pascal.size() - 1) - 1) + 1;

	int max = 0;
	for (int n = last_row_beginning; n < pascal.size(); n++) {
		int bp = best_path(n);
		max = max > bp ? max : bp;
	}

	std::cout << "result = " << max << '\n';

	return 0;
}
