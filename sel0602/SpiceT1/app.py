import numpy as np

il = lambda t: ( (0.14)*np.exp(-1.78*t) ) - ( (0.14)*np.exp(-5.62*t) ) + 1.85

vc = lambda t: - ( (1.85)*np.exp(-1.78*t) ) + ( (5.85)*np.exp(-5.62*t))

vr = lambda t: + ( (1.85)*np.exp(-1.78*t) ) - ( (5.85)*np.exp(-5.62*t)) + 18.5


# timearray = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0]
timearray = [0.1, 0.5, 0.9, 1.4, 1.8]

for i in range(len(timearray)):
    print(f"Time: {timearray[i]}  |  il: {il(timearray[i])}  |  vc: {vc(timearray[i])}  |  vr: {vr(timearray[i])}\n")