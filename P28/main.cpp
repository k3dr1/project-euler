#include <iostream>

int main() {

	int dim = 1001;    // dimensions, i.e. dim by dim spiral
	int l = (dim-1)/2; // number of layers
	int res = (16*(l*l*l) + 30*(l*l) + 26*l + 3)/3;
	std::cout << "result = " << res << '\n';
	
	// Derived the result myself, pretty easy to do
	// Just gotta realize that every last number of a layer
	// is given by f(l) = 1 + 4*l*(l+1)
	// and the rest is just algebra

	return 0;
}
