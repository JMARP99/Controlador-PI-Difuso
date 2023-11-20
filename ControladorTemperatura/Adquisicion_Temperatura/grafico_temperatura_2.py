import matplotlib.pyplot as plt
import numpy as np


# Cargar los datos desde los archivos .npy

pwm = np.load("pwm.npy")
tiempo = np.load("tiempo.npy")

# Crear un gráfico de velocidad en función del tiempo
plt.figure(1)
plt.plot(tiempo, pwm,'r',label='PWM')
plt.xlabel('Tiempo(s)')
plt.ylabel('pwm')
plt.xlim(1,180)
plt.title('Salida del sistema respecto al tiempo')
plt.legend()

# Mostrar los gráficos
plt.show()


print(a)