import matplotlib.pyplot as plt
import numpy as np

t_range = np.linspace(0,10,100)

I = lambda t: 5.786*np.exp(-2.94528*t)

YI = I(t_range)



plt.plot(t_range, YI, 'r', label="$I(t)$")
plt.legend()
plt.xlabel("$t$")
plt.show()
