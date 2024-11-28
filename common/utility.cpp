#include <utility>
#include <vector>

namespace common {

template <class T>
void generate_permutations(int k, std::vector<T>& A, std::vector<std::vector<T>>& permutations)
{
    if (k == 1) {
        permutations.push_back(A);
    } else {
        generate_permutations<T>(k - 1, A, permutations);
        for (int i = 0; i < k - 1; i++) {
            if (k % 2 == 0) {
                std::swap(A[i], A[k - 1]);
            } else {
                std::swap(A[0], A[k - 1]);
            }
            generate_permutations<T>(k - 1, A, permutations);
        }
    }
}

} // namespace common
