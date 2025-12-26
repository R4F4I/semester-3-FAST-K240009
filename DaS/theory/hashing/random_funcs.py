# for i in range(100):
#     print(i%6, i%3, i%2,"O" if i%6== i%3== i%2 else "n")

import math
def h(k,n,A):
    return math.floor(n*(k*A % 1))

for k in range(0,1,0.1):
    print(k)

# for i in range(10):
#     for j in range(10):
#         for k in range(0,1,0.1):
#             num = h(i,j,k)
#             print(num)


