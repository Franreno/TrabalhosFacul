import math

# DESCRICAO: O programa calcula o erro para o lab de qumica, segundo a apostila fornecida pelo instituto
# Deve-se informar a quantidade de medidas e os valores das medidas
# O programa informara os valores numericos de Media_dos_valores, S: (desvio medio), e: (erro)


t = [12.706 , 4.303 , 3.183 , 2.776 , 2.571]
n = int(input('Valor de medidas feitas durante o experimento: '))
tuse = t[(n-2)]

#input of data
# se teve n medidas, vai ter n resultados
x = []
i=0
while i<n:
    print('Digite o valor do experimento %d: ' % (i+1) )
    x.append(float(input()))
    i += 1
xavg = sum(x) / n

# s
# Soma de ( xavg - x[n] ) ^ 2
# dividido por n-1
# e tira a raiz quadrada
i=0
s=0
while i<n:
   s += ( ( xavg - x[i] )**2 )
   i +=1
s /= (n-1)
sf = math.sqrt(s)

# final de e:
e = (tuse*( (sf)/(math.sqrt(n)) ) )

#Resultados
print('Media dos valores medidos: %f' % xavg)
print('Valor final de s: %f' % sf)
print('Valor final de e: %f' % e)