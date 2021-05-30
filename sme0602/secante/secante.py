import numpy as np

def func(x):
    return x**3 - 2*(x**2) + 4
def func2(x):
    return x**2 - 10


def secante(funcao, x0, x1, erro=1e-10):

    fx0 = funcao(x0)
    fx1 = funcao(x1)

    stop = False
    while not stop:
        try:
            x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0)

            fx0 = fx1
            x0 = x1

            fx1 = funcao(x2)
            x1 = x2

            stop = ( abs(x1 - x0) <= erro )
        
        except:
            return x2

    return x2


res = secante(func, -2, 0)
print(res)
res2 = secante(func2, 0, 5)
print(res2)