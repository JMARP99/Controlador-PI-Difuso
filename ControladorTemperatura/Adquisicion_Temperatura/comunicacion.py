import serial
import matplotlib.pyplot as plt
import numpy as np

n_datos = 180

referencia = 100

Temperatura = serial.Serial('COM2', baudrate=9600, timeout=None)

# Inicializa matrices para almacenar los datos
matriz_temperatura = []
matriz_pwm = []
matriz_tiempo = []

while True:
    data = Temperatura.readline().decode('ascii').strip()
    if not data:
        continue

    # Supongamos que los datos son temperatura, PWM y tiempo separados por comas
    temperatura, pwm, tiempo = map(float, data.split(','))

    matriz_temperatura.append(temperatura)
    matriz_pwm.append(pwm)
    matriz_tiempo.append(tiempo)

    print("Temperatura:", temperatura, "PWM:", pwm, "Tiempo:", tiempo)

    if len(matriz_temperatura) == n_datos:
        break

Temperatura.close()

# Convertir las listas en arreglos NumPy
arr_temperatura = np.array(matriz_temperatura)
arr_pwm = np.array(matriz_pwm)
arr_tiempo = np.array(matriz_tiempo)

# Guardar los arreglos en archivos .npy
np.save("temperatura.npy", arr_temperatura)
np.save("pwm.npy", arr_pwm)
np.save("tiempo.npy", arr_tiempo)



# Cargar los datos desde los archivos .npy
temperatura = np.load("temperatura.npy")
pwm = np.load("pwm.npy")
tiempo = np.load("tiempo.npy")

# Crear un gráfico de velocidad en función del tiempo
plt.figure(1)
plt.plot(np.repeat(referencia,n_datos+1),'r--',label='Referencia(C)')
plt.plot(tiempo, temperatura, label='Temperatura(C)')
plt.plot(tiempo, pwm, label='PWM')
plt.xlabel('Tiempo(s)')
plt.xlim(1,n_datos)
plt.title('Gráfico de Temperatura en función del Tiempo')
plt.legend()

# Mostrar los gráficos
plt.show()