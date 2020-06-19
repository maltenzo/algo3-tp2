all:
	g++ -o TSP Tests/tests.cpp Insercion.cpp   main.cpp heurAGM.cpp -O3 -std=c++14
