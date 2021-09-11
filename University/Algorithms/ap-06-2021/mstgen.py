import random

n_max = 120
for n in range(2, n_max+1, 1):
    m_max = ((n-1)*n)//2
    for m in range(n-1, m_max+1, 1):

        print(n, " ", m, " ", random.randint(m+1, ((n-1)*n)//2+2))