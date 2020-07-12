#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>
#include <string>
#include "funciones.h"


using namespace std;

int INFTY = 10e6; // Valor para indicar que no hubo solución.
bool MC = false;
bool MB = false;
int n, m; // # nodos, # aristas
vector<vector<int>> matriz_adyacencia;
bool memoria_ciclos = false;
bool memoria_estructura = false;

// Tabu variables
unsigned int t = 60;
int SUBVECINDAD_PORCENTAJE = 100; // Con que porcentaje de la vecindad nos quedamos
unsigned int ITERACIONES_TABU = 300;


// Si tenemos las heuristicas en archivos separados, incluirlos

int main(int argc, char** argv)
{
	// Leemos el parametro que indica el algoritmo a ejecutar.
	map<string, string> algoritmos_implementados = {{"INS", "insercion"},{"AGM", "heurAGM"},
                                                 {"TABU_CICLOS", "Tabú con memoria de ciclos"}, {"GA", "golosoArista"},
                                                    {"TABU_ESTRUCTURA","Tabú con memoria de estructura"}}; // Las tuplas (Siglas del algoritmo, Nombre completo)

	// Verificar que el algoritmo pedido exista.
	if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
	{
		cerr << "Algoritmo no encontrado: " << argv[1] << endl;
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
	string algoritmo = argv[1];

	// ORDEN DE ARGUMENTOS PARA TABU: T MEMORIA, PORCENTAJE VECINDAD, ITERACIONES
	if(argc > 2 && argc <= 5){ // Si no pasan argumentos se usa lo ya definido
		// atoi convierte el numero string a int, osea "20" --> 20. Literalmente el numero
		if(argc != 5){
			cerr << "CAPO PASA TODOS LOS ARGUMENTOS NO VES QUE SINO EXPLOTA" << endl;
			return 0;
		}
		t = atoi(argv[2]);
		SUBVECINDAD_PORCENTAJE = atoi(argv[3]);
		ITERACIONES_TABU = atoi(argv[4]);
	}

    // Leemos el input.
    int v, w, peso_arista;
    cin >> n >> m;
    matriz_adyacencia.resize(n, vector<int>(n)); // Como el grafo es completo se rellena toda la matriz

    for(int i = 0; i < m; i++){ //Tengo m lineas de entrada indicando v, w, l((v,w))
    	cin >> v >> w >> peso_arista;
    	matriz_adyacencia[v-1][w-1] = peso_arista;
    	matriz_adyacencia[w-1][v-1] = peso_arista;
    }
    // Lleno la matriz de adyacencia con las aristas

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.

	int peso_circuito = 0; // Guardado tras correr los algoritmos
	vector<int> circuito; // Circuito con los vertices recorridos

	int optimum = INFTY;
	auto start = chrono::steady_clock::now();
	 if (algoritmo == "INS")
	{
		MB = true;
		circuito = insercion(peso_circuito);

	}else if(algoritmo == "AGM"){

	     circuito = heurAG(matriz_adyacencia, peso_circuito);

	 }else if(algoritmo == "TABU_CICLOS"){
	 	memoria_ciclos = true;
	 	memoria_estructura = false;
	 	circuito = tabuSearch(peso_circuito);

	 }else if(algoritmo == "TABU_ESTRUCTURA"){
	 	memoria_estructura = true;
	 	memoria_ciclos = false;
		circuito = tabuSearch(peso_circuito);

	 }else if(algoritmo == "GA"){

	     circuito = golosoArista(matriz_adyacencia, peso_circuito);

	 }


	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << circuito.size() <<" "<< peso_circuito << endl;

    for(int i = 0; i < circuito.size(); i++){
    	cout << circuito[i] << " ";
    }
    cout << endl;
    return 0;
}
