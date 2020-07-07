import tsplib95
import sys
#===========================================================#
# Instalar la librería tsplib95 con "pip3 install tsplib95" #
# Uso: python3 parser_instancias.py <archivo_a_parsear>     #
# Resultado: imprime a consola la instancia parseada        #
#===========================================================#

file = sys.argv[1]
# Levanto el archivo pasado por parámetro
problem = tsplib95.load(file)

# Imprimo cantidad de vértices y de aristas
cant_nodos = problem.dimension
# Guardo las aristas sobre la diagonal y las de arriba de la diagonal
# Si no quiero la diagonal le resto cant_nodos a cant_aristas
cant_aristas = (cant_nodos**2+cant_nodos)//2
print("{} {}".format(cant_nodos, cant_aristas))

# Obtengo todas las aristas. Como los pesos son simétricos,
# sea i<j imprimo sólo la arista (i,j) (no la (j,i)).
# Las aristas (i,i) se imprimen con peso 0
for i in range(1,cant_nodos+1):
	for j in range(i,cant_nodos+1):
		if(i!=j):
			peso = problem.get_weight(i,j)
			print("{} {} {}".format(i, j, peso))
