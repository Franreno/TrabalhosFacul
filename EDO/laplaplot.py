import numpy as np
import matplotlib.pyplot as plt

def plot_lapla_eq(TB=5, TA=10, TM=20, kam=2, kab=3):
    delta = 4*kam**2 + kab**2
    r1 = ( -(2*kam+kab) + np.sqrt(delta))/(2)
    r2 = ( -(2*kam+kab) - np.sqrt(delta))/(2)

    print(f"delta: {delta}, r1: {r1}, r2: {r2}")


    Tmt = lambda t: TB + (( (1/(r1-r2)) * ( (TM*(kam+kab+r1))+( kam*TA + r2*TB ) ) )* np.exp(r1*t)) \
        - (( (1/(r1-r2)) * ( (TM*(kam+kab+r2))+( kam*TA + r1*TB ) ) )* np.exp(r2*t))


    C = TA - TB \
        - ( (kam/(r1-r2))*(1/(kam+kab+r1))*( (TM*(kam+kab+r1)) + (kam*TA) + (r2*TB) ) ) \
        - ( (kam/(r1-r2))*(1/(kam+kab+r2))*( (TM*(kam+kab+r2)) + (kam*TA) + (r1*TB) ) ) 


    Tat = lambda t: TB \
        + ( (kam/(r1-r2))*( (np.exp(r1*t))/(kam+kab+r1))*( (TM*(kam+kab+r1)) + (kam*TA) + (r2*TB) ) ) \
        + ( (kam/(r1-r2))*( (np.exp(r2*t))/(kam+kab+r2))*( (TM*(kam+kab+r2)) + (kam*TA) + (r1*TB) ) )  \
        + ( C*(np.exp( -(kam*kab)*t )) )


    t_range = np.linspace(0,10,200)

    YTm = Tmt(t_range)
    YTa = Tat(t_range)   
     

    return YTm, YTa, TB

    # plt.plot(t_range, YTm, 'b', label="$T_m(t)$")
    # plt.plot(t_range, YTa, 'r', label="$T_A(t)$")
    # plt.axhline(y=TB, color='g', label="$T_B(t)$")
    # plt.legend()
    # plt.xlabel("$t$")
    # plt.ylabel("Temperatura")
    # plt.show()
        