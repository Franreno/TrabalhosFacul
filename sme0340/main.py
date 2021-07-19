import matplotlib.pyplot as plt
import numpy as np
from random import uniform

from eigenplot import plot_eigen_eq
from laplaplot import plot_lapla_eq

def main():
    t_range = np.linspace(0,10,200)
    fig = plt.figure(constrained_layout=True)
    axis = fig.subplots(2,2)
    for i in range(2):
        for j in range(1):
            rand_kam = uniform(2,10)
            rand_kab = uniform(2,10)
            eigen_Tm, eigen_Ta, eigen_Tb =  plot_eigen_eq(kam=rand_kam, kab=rand_kab)
            lapla_Tm, lapla_Ta, lapla_Tb =  plot_lapla_eq(kam=rand_kam, kab=rand_kab)

            axis[i,j].plot(t_range, eigen_Tm, 'b', label="$T_m(t)$")
            axis[i,j].plot(t_range, eigen_Ta, 'r', label="$T_A(t)$")
            axis[i,j].axhline(y=eigen_Tb, color='g', label="$T_B(t)$")
            axis[i,j].legend()
            axis[i,j].set_title(f"Eigenvalues, $kam: {rand_kam: .4g}$ $kab: {rand_kab: .4g}$")
            j+=1
            axis[i,j].plot(t_range, lapla_Tm, 'orange', label="$T_m(t)$")
            axis[i,j].plot(t_range, lapla_Ta, 'purple', label="$T_A(t)$")
            axis[i,j].axhline(y=lapla_Tb, color='g', label="$T_B(t)$")
            axis[i,j].legend()
            axis[i,j].set_title("Laplaplot")
            axis[i,j].set_title(f"Laplace, $kam: {rand_kam: .4g}$ $kab: {rand_kab: .4g}$")
            

    plt.show()

main()
