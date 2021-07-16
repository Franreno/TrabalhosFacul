import numpy as np
import matplotlib.pyplot as plt

def plot_eq(TB=5, TA=10, TM=20, kam=2, kab=3):
    delta = 4*kam**2 + kab**2
    r1 = ( -(2*kam+kab) + np.sqrt(delta))/(2)
    r2 = ( -(2*kam+kab) - np.sqrt(delta))/(2)

    Tmt = lambda t: ( ((TM)/(r1-r2)) * ( r1*(np.exp(r1*t)) - r2*(np.exp(r2*t)))) \
        +( ( (TM*(kam+kab) + kam*TA)/(r1-r2) ) * (np.exp(r1*t)+np.exp(r2*t)) ) \
        +( (kam*kab*TB) * \
            ( ( (np.exp(r1*t))/(r1*(r1-r2)) ) + ( (np.exp(r2*t))/(r2*(r2-r1)) ) + ( (1)/(r1*r2) ) ) )


    C = TA - ( ((TM)/(r1-r2))*( ( (r1)/(r1+kam+kab) ) - ((r2)/(r2+kam+kab)) ) ) \
        - ( ( (TM*(kam+kab)+kam*TA)/(r1-r2) ) * ( (1/(r1+kam+kab))+(1/r2+kam+kab) ) ) \
        - ( (kam*kab) * ( (1/(r1*(r1-r2)*(r1+kam+kab)) ) + (1/(r2*(r1-r2)*(r2+kam+kab)) ) + (1/(r1*r2*(kam+kab)) ) ) )

    Tat = lambda t: ( ((TM)/(r1-r2))*( ( (r1*(np.exp(r1*t)))/(r1+kam+kab) ) - ((r2*(np.exp(r2*t))/(r2+kam+kab)) ) ) ) \
        + ( ( (TM*(kam+kab)+kam*TA)/(r1-r2) ) * ( ((np.exp(r1*t)/(r1+kam+kab))+( (np.exp(r2*t))  /r2+kam+kab) ) ) ) \
        + ( (kam*kab) * ( ((np.exp(r1*t))/(r1*(r1-r2)*(r1+kam+kab)) ) + ( (np.exp(r2*t)) /(r2*(r1-r2)*(r2+kam+kab)) ) + (1/(r1*r2*(kam+kab)) ) ) ) \
        + ( (C)/(np.exp((kam+kab)*t)) )

    t_range = np.linspace(0,10,200)

    YTm = Tmt(t_range)
    YTa = Tat(t_range)    

    plt.plot(t_range, YTm, 'b', label="$T_m(t)$")
    plt.plot(t_range, YTa, 'r', label="$T_A(t)$")
    plt.axhline(y=TB, color='g', label="$T_B(t)$")
    plt.legend()
    plt.xlabel("$t$")
    plt.ylabel("Temperatura")
    plt.show()
        

plot_eq()