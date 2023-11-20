import matplotlib.pyplot as plt
import numpy as np


# Cargar los datos desde los archivos .npy
temperatura = np.load("temperatura.npy")
pwm = np.load("pwm.npy")
tiempo = np.load("tiempo.npy")

# Crear un gráfico de velocidad en función del tiempo
plt.figure(1)
plt.plot(np.repeat(100,241),'r--',label='Referencia(C)')
plt.plot(tiempo, temperatura, label='Temperatura(C)')
plt.plot(tiempo, pwm, label='PWM')
plt.xlabel('Tiempo(s)')
plt.xlim(1,180)
plt.title('Gráfico de Temperatura en función del Tiempo')
plt.ylim(0,120)
plt.legend()

# Mostrar los gráficos
plt.show()