import matplotlib.pyplot as plt
import pandas as pd


csvFile = pd.read_csv("res.txt", sep=";")

plt.plot(csvFile["Gen"], csvFile["MaxFit"], 'g')
plt.show()
