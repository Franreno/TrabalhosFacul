import numpy as np

def fatoracaoLU(A):
    n = len(A)
    U = np.zeros((n,n))
    L = np.identity(n)

    for m in range(n):
        for j in range(m,n):
            U[m,j] = A[m,j] - np.sum( L[m,0:m] * U[0:m,j])
        for i in range(m+1, n):
            L[i,m] = (A[i,m] - np.sum(L[i,0:m] * U[0:m,m]))/U[m,m]
    return L, U

