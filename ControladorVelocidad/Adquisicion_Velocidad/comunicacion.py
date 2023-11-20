import serial
import matplotlib.pyplot as plt
import numpy as np

n_datos = 50

referencia = 350

Velocidad = serial.Serial('COM2', baudrate=9600, timeout=None)

# Inicializa matrices para almacenar los datos
matriz_velocidad = []
matriz_pwm = []
matriz_tiempo = []

while True:
    data = Velocidad.readline().decode('ascii').strip()
    if not data:
        continue

    # Supongamos que los datos son velocidad, PWM y tiempo separados por comas
    velocidad, pwm, tiempo = map(float, data.split(','))

    matriz_velocidad.append(velocidad)
    matriz_pwm.append(pwm)
    matriz_tiempo.append(tiempo)

    print("Velocidad:", velocidad, "PWM:", pwm, "Tiempo:", tiempo)

    if len(matriz_velocidad) == n_datos:
        break

Velocidad.close()


# Convertir las listas en arreglos NumPy
arr_velocidad = np.array(matriz_velocidad)
arr_pwm = np.array(matriz_pwm)
arr_tiempo = np.array(matriz_tiempo)

# Guardar los arreglos en archivos .npy
np.save("velocidad.npy", arr_velocidad)
np.save("pwm.npy", arr_pwm)
np.save("tiempo.npy", arr_tiempo)


# Cargar los datos desde los archivos .npy
velocidad = np.load("velocidad.npy")
pwm = np.load("pwm.npy")
tiempo = np.load("tiempo.npy")

# Crear un gráfico de velocidad en función del tiempo
plt.figure(1)
plt.plot(np.repeat(350,51),'r--',label='Referencia(Rpm)')
plt.plot(tiempo, velocidad, label='Velocidad(Rpm)')
plt.plot(tiempo, pwm, label='PWM')
plt.xlabel('Tiempo(s)')
plt.xlim(1,50)
plt.title('Gráfico de Velocidad en función del Tiempo')
plt.ylim(0,400)
plt.legend()

# Mostrar los gráficos
plt.show()