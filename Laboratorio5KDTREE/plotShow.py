import matplotlib.pyplot as plt

# Función para leer el archivo de datos
def leer_datos(archivo):
    k_values = []
    tree1_times = []
    tree2_times = []
    tree3_times = []
    
    with open(archivo, 'r') as file:
        lines = file.readlines()
        
        for line in lines:
            # Buscar las líneas que empiezan con 'k:'
            if line.startswith('k:'):
                k = int(line.split(':')[1].strip())  # Extraer valor de k
                k_values.append(k)
                # Leer las siguientes tres líneas para los tiempos
                tree1_times.append(list(map(float, lines[lines.index(line) + 1].split())))
                tree2_times.append(list(map(float, lines[lines.index(line) + 2].split())))
                tree3_times.append(list(map(float, lines[lines.index(line) + 3].split())))

    return k_values, tree1_times, tree2_times, tree3_times

# Leer los datos del archivo
archivo = 'output.txt'  # Nombre del archivo que contiene los datos
k_values, tree1_times, tree2_times, tree3_times = leer_datos(archivo)

# Separar los tiempos para KDTree y Fuerza Bruta
tree1_kd_times = [x[0] for x in tree1_times]
tree1_brute_times = [x[1] for x in tree1_times]

tree2_kd_times = [x[0] for x in tree2_times]
tree2_brute_times = [x[1] for x in tree2_times]

tree3_kd_times = [x[0] for x in tree3_times]
tree3_brute_times = [x[1] for x in tree3_times]

# Crear gráfico
plt.figure(figsize=(10, 6))

# Graficar los tiempos para cada árbol
plt.plot(k_values, tree1_kd_times, label='Tree1 - Fuerza Bruta', marker='o', linestyle='-', color='b')
plt.plot(k_values, tree1_brute_times, label='Tree1 - KDTree', marker='x', linestyle='--', color='b')

plt.plot(k_values, tree2_kd_times, label='Tree2 - Fuerza Bruta', marker='o', linestyle='-', color='g')
plt.plot(k_values, tree2_brute_times, label='Tree2 - KDTree', marker='x', linestyle='--', color='g')

plt.plot(k_values, tree3_kd_times, label='Tree3 - Fuerza Bruta', marker='o', linestyle='-', color='r')
plt.plot(k_values, tree3_brute_times, label='Tree3 - KDTree', marker='x', linestyle='--', color='r')

# Etiquetas y título
plt.xlabel('k (Número de vecinos)', fontsize=12)
plt.ylabel('Tiempo (segundos)', fontsize=12)
plt.title('Comparación de tiempos de búsqueda KNN (KDTree vs Fuerza Bruta)', fontsize=14)

# Leyenda
plt.legend()

# Mostrar gráfico
plt.grid(True)
plt.tight_layout()
plt.show()
