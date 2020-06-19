all:
	g++ -o TSP funciones.h Insercion.cpp  GolosoAristas.cpp main.cpp heurAGM.cpp -O3 -std=c++14
