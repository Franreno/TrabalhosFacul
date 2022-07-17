class vi:
    def __init__(self, x, dx):
        self.x = x
        self.dx = dx

    def soma(self, y):
        self.x += y.x
        self.dx += y.dx
    
    def sub(self, y):
        self.x -= y.x
        self.dx += y.dx

    def produto(self, y):
        self.dx = ( (self.x*y.dx) + (y.x*self.dx) )
        self.x *= y.x

    def potencia(self,pt):
        self.dx = (pt*(pow(self.x , (pt-1) )*self.dx))
        self.x = pow(self.x , pt)
    
    def divisao(self,y):
        self.dx = ( (self.x*y.dx) + (y.x*self.dx) ) / (y.x**2)
        self.x /= y.x

    def produtoporconstante(self,cte):
        self.x *= cte
        self.dx *= cte
        
# 
# COMO USAR:
# Inicializacao de um novo dado:
# variavel = vi( dado , incerteza )
# Ex: 
# volume = vi( 0.03 , 0.01 )
#
#
#                        ------------- IMPORTANTE!! -------------------
#  quando realizar uma operacao, a atribuicao sera feita na variavel antes do ponto
#  por exemplo: v1.soma(v2) 
#  isso eh equivalente a ter feito isso: v1 += v2
#  porem o programa ja faz isso tanto pra parte dos dados, quanto pra parte da incerteza.
#  NAO EH NECESSARIO USAR VARIAVEIS TEMPORARIAS (a menos em casos especificos).  
#
#
#
#                        -------------  FUNCOES -------------------
#
#  Soma {
#   Necessario: 2 variaveis
#   v1 = vi(0.1 , 0.2)
#   v2 = vi(0.2 , 0.3)
# 
#   Somar v1 + v2:
#   v1.soma(v2)
#
#   Somar v2 + v1:
#   v2.soma(v1)
# }
# 
# ------------------------------------------------------------------------------------------
#
# Subtracao {
#   Necessario: 2 variaveis
#   v1 e v2.
#  
#  subtrair v1 - v2:
#  v1.sub(v2)
#   
#   Subtrair v2 - v1:
#   v2.sub(v1)
# }
# 
# ------------------------------------------------------------------------------------------
#
# Produto {
#   Necessario: 2 variaveis
#   v1 e v2
# 
#   Produto v1*v2:
#   v1.produto(v2)    
#   ou
#   v2.produto(v1)
# 
# }
# 
# ------------------------------------------------------------------------------------------
#
# Potencia {
#   Necessario: 1 variavel (v1)
# 
#   v1.potencia(2)
#   eh equivalente a v1**2
#   
#   v1.potencia(x) | x -> valor da potencia.
# 
# }
# 
# ------------------------------------------------------------------------------------------
#
# Produtoporconstante {
#   Necessario: 1 variavel (v1)
# 
#   v1.produtoporconstante(x)
#   multiplica o dado e a incerteza por x
# 
# }
# 
# ------------------------------------------------------------------------------------------
#
# Divisao {
#   Necessario: 2 variaveis (v1,v2)
#   
#   Divisao v1/v2:
#       v1.divisao(v2)
# 
#   Divisao v2/v1:
#       v2.divisao(v1)
# }
# 
# ------------------------------------------------------------------------------------------
#
# Exemplo:
#
# F = m.a
#
# P = F/Area
#
# m = vi(x,dx)
# a = vi(y,dy)
#
# F = m
# F.produto(a)
# F.divisao(Area)
#
# print(F.x) -> valor da pressao
# print(F.dx) -> incerteza da pressao
# 
# ------------------------------------------------------------------------------------------
#

#comeca a codar aqui:

