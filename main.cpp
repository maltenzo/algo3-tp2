#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>
#include "funciones.h"

using namespace std;

int INFTY = 10e6; // Valor para indicar que no hubo solución.
bool MC = false;
bool MB = false;
int n, m; // # nodos, # aristas
vector<vector<int>> matriz_adyacencia;

// Si tenemos las heuristicas en archivos separados, incluirlos

int main(int argc, char** argv)
{
	// Leemos el parametro que indica el algoritmo a ejecutar.
	map<string, string> algoritmos_implementados = {{"ins", "insercion"},{"agm", "heurAGM"},{"T_AGM","Tests AGM"}}; // Las tuplas (Siglas del algoritmo, Nombre completo)

	// Verificar que el algoritmo pedido exista.
	if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
	{
		cerr << "Algoritmo no encontrado: " << argv[1] << endl;
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
	string algoritmo = argv[1];

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
	 if (algoritmo == "ins")
	{
		MB = true;
		circuito = insercion(peso_circuito);
	}else if(algoritmo == "agm"){
	     circuito = heurAG(matriz_adyacencia);
	     peso_circuito = circuito[2];
	     vector<int> temp(circuito[0],0);
	     for(int i = 2; i<circuito.size();i++){
	         temp[i-2] = circuito[i];
	     }
	     circuito = temp;
	 }else if(algoritmo == "T_AGM"){
	     circuito = test_AGM_1();
         peso_circuito = circuito[1];
         vector<int> temp(circuito[0],0);
         for(int i = 2; i<circuito.size();i++){
             temp[i-2] = circuito[i];
         }
         circuito = temp;
	 }// else if (algoritmo =="")..


	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << circuito.size() <<" "<< peso_circuito << endl;

    for(int i = 0; i < circuito.size(); i++){
    	cout << circuito[i];
    }
    cout << endl;
    return 0;
}
