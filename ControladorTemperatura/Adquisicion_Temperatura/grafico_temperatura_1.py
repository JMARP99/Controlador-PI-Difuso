import matplotlib.pyplot as plt
import numpy as np


# Cargar los datos desde los archivos .npy
temperatura = np.load("temperatura.npy")
pwm = np.load("pwm.npy")
tiempo = np.load("tiempo.npy")

# Crear un gráfico de velocidad en función del tiempo
plt.figure(1)
plt.plot(tiempo, temperatura,'r' ,label='Temperatura(C)')
plt.plot(np.repeat(100,241),'b--',label='Referencia(C)')
plt.xlabel('Tiempo(s)')
plt.ylabel('Temperatura (C)')
plt.xlim(1,180)
plt.title('Salida del sistema respecto al tiempo')
plt.ylim(0,120)
plt.legend()

# Mostrar los gráficos
plt.show()