import math

def bissection(f, a, b, err=1e-10):
    xPrev = 0
    stopStatement = False
    while not stopStatement:
        x = (a+b)/2.0

        if f(a) * f(b) < 0:
            b = x
        else:
            a = x
        stopStatement = abs(x - xPrev) < err
        xPrev = x

    return x


f = lambda x: x**2 + math.log(x)

print(bissection(f, 0.1,1.0))
# 0.5499999999476132