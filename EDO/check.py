import numpy as np
import matplotlib.pyplot as plt

TB=5
TA=10
TM=20
kam = 2
kab = 3

lamb1 = 0
getlamb2 = lambda x,y: -(2*x+y  +  np.sqrt(4*(x**2)+(y**2)))/2
getlamb3 = lambda x,y: -(2*x+y  -  np.sqrt(4*(x**2)+(y**2)))/2

lamb2 = getlamb2(kam, kab)
lamb3 = getlamb3(kam, kab)

c2 = ( (lamb3*(TM-TB) ) + (kam*(TM-TA)) )/(lamb3-lamb2)
c3 = ( ( lamb2*(TB-TM) ) + (kam*(TA-TM)) ) / (lamb3-lamb2)


Tmt = lambda t: c2*np.exp(lamb2*t) + c3*np.exp(lamb3*t) + TB
Tat = lambda t: (c2 * ( 1 + ( (lamb2/kam) ) ))*np.exp(lamb2*t) + (c3 * ( 1 + ( (lamb3/kam) ) ))*np.exp(lamb3*t) + TB
Tbt = TB

t_range = np.linspace(0,10,200)

YTm = Tmt(t_range)
YTa = Tat(t_range)    

plt.plot(t_range, YTm, 'b', label="$T_m(t)$")
plt.plot(t_range, YTa, 'r', label="$T_A(t)$")
plt.axhline(y=Tbt, color='g', label="$T_B(t)$")
plt.legend()
plt.xlabel("$t$")
plt.ylabel("Temperatura")
plt.show()
