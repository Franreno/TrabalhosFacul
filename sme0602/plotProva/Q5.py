import matplotlib.pyplot as plt
import numpy as np

x = [0.998175, 1.10364, 0.531075]

f = lambda t: x[0] + x[1]*t + x[2]*(t**2)
f_taylor = lambda t: 1 + t + ((t**2)/2)

t_range = np.linspace(-1.0, 1.0, 100)

yf = f(t_range)
yf_taylor = f_taylor(t_range)


fig = plt.figure(constrained_layout=True)
axis = fig.subplots(2,2)
axis[0,0].plot(t_range, yf, 'r', label="$f(t)$")
axis[0,0].legend()
axis[0,0].set_title("Funcao aproximada")

axis[0,1].plot(t_range, yf_taylor, 'b', label="$f_{taylor}(t)$")
axis[0,1].legend()
axis[0,1].set_title("Funcao taylor")

axis[1,0].plot(t_range, np.exp(t_range), 'g', label="$e^t$")
axis[1,0].legend()
axis[1,0].set_title("Funcao $e^t$")

axis[1,1].plot(t_range, yf, 'r', label="$f(t)$")
axis[1,1].plot(t_range, yf_taylor, 'b', label="$f_{taylor}(t)$")
axis[1,1].plot(t_range, np.exp(t_range), 'g', label="$e^t$")
axis[1,1].legend()
axis[1,1].set_title("As tres juntas")

plt.show()
