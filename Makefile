all:
	g++ -o TSP Tests/tests.cpp Insercion.cpp  2opt.cpp  main.cpp heurAGM.cpp -O3 -std=c++14
