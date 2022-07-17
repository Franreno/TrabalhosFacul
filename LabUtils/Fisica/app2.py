class WithIncertezas:
    
    def __init__(self, x, dx):
        self.x = x
        self.dx = dx
    
    def soma(self , y):
        return WithIncertezas( (self.x + y.x) , (self.dx + y.dx) )

    def sub(self, y):
        return WithIncertezas( (self.x - y.x) , (self.dx + y.dx) )

    def produto(self, y):
        return WithIncertezas( (self.x * y.x) , ( (self.x*y.dx) + (y.x*self.dx) ) )
    
    def potencia(self, pt):
        return WithIncertezas( ( pow(self.x , pt) ) , ( (pt*(pow(self.x , (pt-1) )*self.dx)) ) )

    def divisao(self, y):
        return WithIncertezas( (self.x/y.x) , ( ( (self.x*y.dx) + (y.x*self.dx) ) / (y.x**2) ) ) 
    
    def produtoporconstante(self, cte):
        return WithIncertezas( (self.x*cte) , (self.dx*cte) )

def printWithIncertezas(a):
    print( str(a.x) + ' ' + str(a.dx) )


# a = WithIncertezas(1 , 0.01)
# b = WithIncertezas(1 , 0.02)
# c = WithIncertezas(2 , 0.05)

# h = (a.soma(b)).produto(c)

# # k = h.produto(c)

# printWithIncertezas(a)
# printWithIncertezas(h)
# # printWithIncertezas(k)
