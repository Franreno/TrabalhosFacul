#                                      ----CALCULADORA METODO DOS MINIMOS QUADRADOS-----


#                                  ----ANTES DE TUDO-----
# antes de rodar o programa, certifique-se que as libraries pandas, numpy, math e matplotlib estao instalados na sua maquina.
# caso nao estejam instalados eh possivel instala-los usando os seguintes comandos em um terminal que rode python.

# pandas: pip install pandas
# numpy: pip install numpy
# matplotlib: pip install matplotlib

# apos fazer isso, o programa devera rodar, se seu excel estiver configurado corretamente

#                                      ----excel-----
# o excel devera compor de duas variaveis, x e y (letra minuscula mesmo!)
# na coluna x deve ser os valores que estao sendo multiplicados pelo coeficiente angular
# na coluna y deve ser os valores que resultam da multiplicacao de a*x
# CUIDADO!
# fique de olho no separador decimal do excel !!
# as vezes usando o ponto como separador decimal buga.

#                                  IMPORTANTE:
#   o excel devera ter o nome de "Data.xlsx" e deve estar dentro da pasta \ExcelSheets
#   Ha um exemplo de excel dentro da pasta \ExcelSheets

# O grafico final sera disponibilizado dentro da pasta \Graficos.


# Parte de import das libraries
import pandas as pd
import numpy as np
from math import sqrt
import matplotlib.pyplot as plt 


# Lendo os dados do excel
df = pd.read_excel(r'ExcelSheets\Data.xlsx')
x_values = pd.DataFrame(df, columns=['x']).to_numpy()
y_values = pd.DataFrame(df, columns=['y']).to_numpy()

#calculo da media
media = []
media.append( np.mean(x_values) )
media.append( np.mean(y_values) )

#           Todas as formulas sao do livro de engenharia do laboratorio de fisica.

# calculo do coeficiente angular:
#   recebe array x, array y e array das medias
def coefangular(x,y,media):
    return np.sum( ((x-media[0])*y) ) / np.sum( ( (x-media[0])**2) )


# Calculo do coeficiente linear:
#   recebe array das medias e o coeficiente angular.
def coeflinear(media, a):
    return ( media[1] - a*media[0] )


# Calculo do erro do array de Y:
#   recebe coeficientes angular e linear, array de x e de y.
def dy(a,b,x,y):
    h = np.sum( ( (a*x+b-y)**2 ) )
    if h == 0:
        return 0.0
    else:
        return sqrt( ( (h) / (len(x)-2) ) )



# Calculo do erro do coeficiente angular:
#   recebe erro de y, array x e array media
def da(dy, x, media):
    if dy==0:
        return 0.0
    else:
        return dy / sqrt( np.sum( ( (x-media[0])**2 ) ) )



# Calculo do erro do coeficiente linear:
#   recebe array de x, erro de y, array de media
def db(x,dy,media):
    if dy==0:
        return 0.0
    else:
        return (sqrt( (np.sum((x**2))) / (len(x)*np.sum( ((x-media[0])**2))))*dy)



cangular = coefangular(x_values, y_values, media ) # coeficiente angular
clinear = coeflinear(media, cangular)              # coeficiente linear
d_y = dy(cangular, clinear, x_values, y_values)    # erro y
d_cangular = da( d_y, x_values, media )            # erro coeficiente angular
d_b = db(x_values,d_y,media)                       # erro coeficiente linear


print( "y = " + str(cangular) + "x + " + str(clinear)  )
print("Coeficiente Angular: " + str(cangular) + " +- " + str(d_cangular) )
print("Coeficiente Linear: " + str(clinear) + " +- " + str(d_b) )

#plotando o grafico de X vs Y
plt.scatter(x_values , y_values, c="red", s=10)
y_final = []
for x in x_values:
    y_final.append((x*cangular) + clinear)

plt.plot(x_values, y_final)

plt.xlabel("x")
plt.ylabel("y")
plt.title("y = " + str(cangular) + "x + " + str(clinear) )
plt.savefig(r"Graficos\graph.png")