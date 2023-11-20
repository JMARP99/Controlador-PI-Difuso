import matplotlib.pyplot as plt
import numpy as np


# Cargar los datos desde los archivos .npy
pwm = np.load("pwm.npy")
tiempo = np.load("tiempo.npy")

# Crear un gráfico de velocidad en función del tiempo
plt.figure(1)
plt.plot(tiempo, pwm,'r', label='Señal de control')
#establecer limites en la figura
plt.xlim(1,50)
plt.ylim(0,250)
#nombres en los ejes
plt.xlabel('Tiempo(s)')
plt.ylabel('pwm')
plt.title('Señal de control')
#Mostrar grid
plt.grid()
#Mostrar leyenda
plt.legend()
# Mostrar los gráficos
plt.show()