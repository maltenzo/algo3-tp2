all:
	g++ -o TSP funciones.h i
	Insercion.cpp  GolosoAristas.cpp main.cpp heurAGM.cpp -O3 -std=c++14
