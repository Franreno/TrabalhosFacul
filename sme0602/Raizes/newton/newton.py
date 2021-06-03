import math

def newton(f,df,x,err=1e-10):
    xPrev = x
    stopStatement = False
    while not stopStatement:

        x = x - f(x)/df(x)
        stopStatement = abs(x - xPrev) <= err
        xPrev = x
    
    return x

f = lambda x: math.log(x) + x - 4
df = lambda x: 1.0/x + 1

print(newton(f,df,30))
#2.926271062443501