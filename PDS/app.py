import numpy as np
import matplotlib.pyplot as plt
import scipy.misc
import scipy.signal
plt.rcParams['figure.figsize'] = (20,8)

# Pegar o sinal ECG do scipy
ECG = scipy.misc.electrocardiogram()
# Frequencia definida para esse sinal = 360
Frequency = 360
# Tempo do sinal: [9,15] segundos
starting_pos = 9 * Frequency
ending_pos = 15 * Frequency
ECG = ECG[ starting_pos:ending_pos ]
time = np.arange(ECG.size) / Frequency

frames = (ECG.size - Frequency)/(Frequency/2) + 1
print(frames)

# Plot do grafico no dominio do tempo
plt.plot(time, ECG)
plt.xlabel("Tempo [s]")
plt.ylabel("ECG [mV]")
plt.ylim(-1, 1.5)
plt.show()

# Usando o scipy para realizar o short time fourrier transform
f,t,Zxx = scipy.signal.stft(ECG, Frequency, nperseg=frames)

# Plotar um Spectrograma
plt.pcolormesh(t,f,np.abs(Zxx),shading='gouraud')
plt.xlabel("Tempo [s]")
plt.ylabel("Freq [Hz]")
plt.show()
