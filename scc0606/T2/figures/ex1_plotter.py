from typing import no_type_check
import matplotlib.pyplot as plt
import numpy as np

def plot():
    ex1a = np.array( [3.072769,  2.872562, 2.962380 ] )
    ex1b = np.array( [3.005225,  3.004530, 2.959063 ] )
    ex1c = np.array( [3.111986,  3.024494, 3.002199 ] )
    ex1d = np.array( [0.689733,  0.690785, 0.699717 ] )

    ex1a_mean = np.mean(ex1a)
    ex1b_mean = np.mean(ex1b)
    ex1c_mean = np.mean(ex1c)
    ex1d_mean = np.mean(ex1d)
    

    ex1a_std = np.std(ex1a)
    ex1b_std = np.std(ex1b)
    ex1c_std = np.std(ex1c)
    ex1d_std = np.std(ex1d)
    print([ex1a_std,ex1b_std,ex1c_std,ex1d_std])

    labels = [f"Busca sequencial simples\nMédia:{ex1a_mean: .4g}\nDesvio Padrão:{ex1a_std: .4g}",
              f"Busca realocação\nMédia:{ex1b_mean: .4g}\nDesvio Padrão:{ex1b_std: .4g}", 
              f"Busca transposição\nMédia:{ex1c_mean: .4g}\nDesvio Padrão:{ex1c_std: .4g}", 
              f"Busca por índice primário\nMédia:{ex1d_mean: .4g}\nDesvio Padrão:{ex1d_std: .4g}"]
    
    ctes = [ex1a_mean,ex1b_mean,ex1c_mean,ex1d_mean]
    standardDeviation = [ex1a_std,ex1b_std,ex1c_std,ex1d_std]

    xPos = np.arange(4)
    fig, ax = plt.subplots()
    ax.bar(xPos, ctes, yerr=standardDeviation, align='center', alpha=0.5, capsize=10, ecolor='black')
    ax.set_ylabel('Tempo médio percorrido')
    ax.set_xticks(xPos)
    ax.set_xticklabels(labels)
    ax.set_title("Grafico do tempo com desvio padrão")
    ax.yaxis.grid(True)

    plt.tight_layout()
    plt.show()

plot()

    

