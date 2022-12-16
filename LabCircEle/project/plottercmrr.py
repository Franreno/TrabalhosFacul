import matplotlib.pyplot as plt
import numpy as np

def plot():
    freq = 1024
    omega = np.pi*2*freq
    cmrr_lc = lambda t: 3.16087*np.cos(omega*t - 89.9819)
    cmrr_transf = lambda t: 0.500965*np.cos(omega*t + 90)

    t_range = np.linspace(-1, 1, 2000)
    Ycmrr_lc = cmrr_lc(t_range)
    Ycmrr_transf = cmrr_transf(t_range)

    plt.plot(t_range, Ycmrr_lc, 'r', label="$CMRR_{LC}$")
    plt.legend()
    plt.xlabel("$t$")
    plt.title("Gráfico para o $CMRR_{LC}$")
    plt.show()

plot()