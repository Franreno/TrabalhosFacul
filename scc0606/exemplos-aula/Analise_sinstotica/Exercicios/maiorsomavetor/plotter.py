import matplotlib.pyplot as plt
import numpy as np

def plot():
    filename = r"out.txt"
    with open(filename,'r') as f:
        v = f.readlines()
    f.close()
    
    spl = []
    for elem in v:
        elem = elem.replace('\n', '').split(' ')
        spl.append(float(elem[0]))
        spl.append(float(elem[1]))

    x = spl[::2]
    y = spl[1::2]
    func_nlogn = x*np.log(x)
    print(x)
    print(y)


    plt.plot(x,y)
    plt.plot(x,func_nlogn, color="black")
    plt.scatter(x,y,color="red")
    plt.show()

plot()