import matplotlib.pyplot as plt
import numpy as np


# Cargar los datos desde los archivos .npy
velocidad = np.load("velocidad.npy")
tiempo = np.load("tiempo.npy")

# Crear un gráfico de velocidad en función del tiempo
plt.figure(1)
plt.plot(tiempo, velocidad,'r', label='Velocidad(Rpm)')
plt.plot(np.repeat(350,51),'b--',label='Referencia(Rpm)')
#establecer limites en la figura
plt.xlim(1,50)
plt.ylim(0,400)
#nombres en los ejes
plt.xlabel('Tiempo(s)')
plt.ylabel('Velocidad Angular (RPM)')
plt.title('Salida del sistema respecto al tiempo')
#Mostrar grid
plt.grid()
#Mostrar leyenda
plt.legend()
# Mostrar los gráficos
plt.show()