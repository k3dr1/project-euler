import itertools
from functools import reduce
from itertools import accumulate, permutations

def div_from_by(n, i, d):
    return int("".join(n[i:i+3]))%d == 0

def check_property(n):
    return div_from_by(n, 1, 2) and div_from_by(n, 2, 3) and div_from_by(n, 3, 5) and div_from_by(n, 4, 7) and div_from_by(n, 5, 11) and div_from_by(n, 6, 13) and div_from_by(n, 7, 17)

s = "0123456789"
r = reduce(lambda a,b : a + int("".join(b)), filter(check_property, permutations(s)), 0)
print(r)
