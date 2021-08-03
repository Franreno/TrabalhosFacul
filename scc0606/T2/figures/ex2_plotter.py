import matplotlib.pyplot as plt
import numpy as np

def plot_h_div():
    ex2a_insercao = np.array( [0.109969, 0.097830, 0.097529 ] )
    ex2b_insercao = np.array( [0.166983, 0.132759, 0.132772 ] )
    ex2c_insercao = np.array( [0.019200, 0.018553, 0.019008 ] )

    ex2a_busca = np.array( [0.273371, 0.265017, 0.251954 ] )
    ex2b_busca = np.array( [0.405845, 0.292443, 0.294074 ] )
    ex2c_busca = np.array( [0.036272, 0.035214, 0.035895 ] )

    ex2a_insercao_mean = np.mean(ex2a_insercao)
    ex2b_insercao_mean = np.mean(ex2b_insercao)
    ex2c_insercao_mean = np.mean(ex2c_insercao)

    ex2a_busca_mean = np.mean(ex2a_busca)
    ex2b_busca_mean = np.mean(ex2b_busca)
    ex2c_busca_mean = np.mean(ex2c_busca)

    ex2a_insercao_std = np.std(ex2a_insercao)
    ex2b_insercao_std = np.std(ex2b_insercao)
    ex2c_insercao_std = np.std(ex2c_insercao)

    ex2a_busca_std = np.std(ex2a_busca)
    ex2b_busca_std = np.std(ex2b_busca)
    ex2c_busca_std = np.std(ex2c_busca)

    labels_insercao = [f"Ex2a inserção\nMédia: {ex2a_insercao_mean: .4g}\nDes. Padrão: {ex2a_insercao_std: .3g}",
                       f"Ex2b inserção\nMédia: {ex2b_insercao_mean: .4g}\nDes. Padrão: {ex2b_insercao_std: .3g}",
                       f"Ex2c inserção\nMédia: {ex2c_insercao_mean: .4g}\nDes. Padrão: {ex2c_insercao_std: .3g}",
                        ]

    labels_busca =    [f"Ex2a busca\nMédia: {ex2a_busca_mean: .4g}\nDes. Padrão: {ex2a_busca_std: .3g}",
                       f"Ex2b busca\nMédia: {ex2b_busca_mean: .4g}\nDes. Padrão: {ex2b_busca_std: .3g}",
                       f"Ex2c busca\nMédia: {ex2c_busca_mean: .4g}\nDes. Padrão: {ex2c_busca_std: .3g}",
                        ]


    ctes_insercao = [ex2a_insercao_mean, ex2b_insercao_mean, ex2c_insercao_mean]
    ctes_busca = [ex2a_busca_mean, ex2b_busca_mean, ex2c_busca_mean]

    error_insercao = [ex2a_insercao_std, ex2b_insercao_std, ex2c_insercao_std]
    error_busca = [ex2a_busca_std, ex2b_busca_std, ex2c_busca_std]

    xPos = np.arange(3)
    fig = plt.figure(constrained_layout=True)
    ax = fig.subplots(1,2)

    ax[0].bar(xPos,ctes_insercao, yerr=error_insercao, align='center', alpha=0.5, capsize=10, ecolor='black')
    ax[0].set_ylabel('Tempo médio percorrido')
    ax[0].set_xticks(xPos)
    ax[0].set_xticklabels(labels_insercao)
    ax[0].set_title("Tempo para a inserção, funcao h_div")
    ax[0].yaxis.grid(True)


    ax[1].bar(xPos,ctes_busca, yerr=error_busca, align='center', alpha=0.5, capsize=10, ecolor='black')
    ax[1].set_ylabel('Tempo médio percorrido')
    ax[1].set_xticks(xPos)
    ax[1].set_xticklabels(labels_busca)
    ax[1].set_title("Tempo médio para a busca, funcao h_div")
    ax[1].yaxis.grid(True)

    plt.show()



def plot_h_mult():
    ex2a_insercao = np.array( [ 0.265392, 0.252442, 0.253174 ] )
    ex2c_insercao = np.array( [0.055772, 0.055013, 0.055150] )

    ex2a_busca = np.array( [0.695936, 0.595087, 0.597783 ] )
    ex2c_busca = np.array( [0.201714, 0.115215, 0.113678 ] )

    ex2a_insercao_mean = np.mean(ex2a_insercao)
    ex2c_insercao_mean = np.mean(ex2c_insercao)

    ex2a_busca_mean = np.mean(ex2a_busca)
    ex2c_busca_mean = np.mean(ex2c_busca)

    ex2a_insercao_std = np.std(ex2a_insercao)
    ex2c_insercao_std = np.std(ex2c_insercao)

    ex2a_busca_std = np.std(ex2a_busca)
    ex2c_busca_std = np.std(ex2c_busca)

    ctes_insercao = [ex2a_insercao_mean, ex2c_insercao_mean]
    ctes_busca = [ex2a_busca_mean, ex2c_busca_mean]

    error_insercao = [ex2a_insercao_std, ex2c_insercao_std]
    error_busca = [ex2a_busca_std, ex2c_busca_std]

    labels_insercao = [f"Ex2a inserção\nMédia: {ex2a_insercao_mean: .4g}\nDes. Padrão: {ex2a_insercao_std: .3g}",
                       f"Ex2c inserção\nMédia: {ex2c_insercao_mean: .4g}\nDes. Padrão: {ex2c_insercao_std: .3g}",
                        ]

    labels_busca =    [f"Ex2a busca\nMédia: {ex2a_busca_mean: .4g}\nDes. Padrão: {ex2a_busca_std: .3g}",
                       f"Ex2c busca\nMédia: {ex2c_busca_mean: .4g}\nDes. Padrão: {ex2c_busca_std: .3g}",
                        ]

    xPos = np.arange(2)
    fig = plt.figure(constrained_layout=True)
    ax = fig.subplots(1,2)

    ax[0].bar(xPos,ctes_insercao, yerr=error_insercao, align='center', alpha=0.5, capsize=10, ecolor='black')
    ax[0].set_ylabel('Tempo médio percorrido')
    ax[0].set_xticks(xPos)
    ax[0].set_xticklabels(labels_insercao)
    ax[0].set_title("Tempo para a inserção, funcao h_mult")
    ax[0].yaxis.grid(True)


    ax[1].bar(xPos,ctes_busca, yerr=error_busca, align='center', alpha=0.5, capsize=10, ecolor='black')
    ax[1].set_ylabel('Tempo médio percorrido')
    ax[1].set_xticks(xPos)
    ax[1].set_xticklabels(labels_busca)
    ax[1].set_title("Tempo médio para a busca, funcao h_mult")
    ax[1].yaxis.grid(True)

    plt.show()


def plot():
    plot_h_div()
    plot_h_mult()
    

plot()