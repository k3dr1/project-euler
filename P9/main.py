a = 0
b = 0
c = 0
for i in range(1, 1000):
    for j in range(i+1, 1000):
        for k in range(j+1, 1000):
            if (i*i + j*j == k*k):
                #print(f"{i}^2 + {j}^2 = {k}^2")
                if (i + j + k == 1000):
                    a = i
                    b = j
                    c = k

print(f"{a}^2 + {b}^2 = {c}^2")
print(f"a*b*c={a*b*c}")
