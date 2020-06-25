#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>
#include <time.h>
#include "funciones.h"

using namespace std;

int SUBVECINIDAD_PORCENTAJE = 10; // Con que porcentaje de la vecindad nos quedamos
int TOP_VECINDAD = 10;

// Funcion para ordenar la subvecindad
bool cicloMejor(vector<int> C1, vector<int> C2){
	return C1[C1.size()] < C2[C2.size()];
}

int costo(vector<int> ciclo){
	int res = 0;
	for(int i = 0; i < ciclo.size()-1; i++){
		res += matriz_adyacencia[i][i+1];
	}
	return res;
}

vector<int> swap(vector<int> c, int i, int j){
	vector<int> res = c;
	if(i > j){
		int a = i;
		i = j;
		j = a; 
	}
	// i es el menor
	int it = 0;
	for(int k = 0; k <= i; k++){
		res[it] = c[k];
		it++;	
	}
	for(int k = j; k > i; k--){
		res[it] = c[k];
		it++;
	}
	for(int k = j+1; k < c.size(); k++){
		res[it] = c[k];
		it++;
	}
	return res;
}

// Grafo G, tengo matriz de adyacencia

vector<vector<int>> localSearch2opt(vector<int> ciclo, const int l){ // recibe el ciclo generado por AGM o alguna otra heuristica
	// l es el costo del circuito que me pasan
	// Pre, el ciclo es de longitud n = matriz_adyacencia.size()
	
	int n = ciclo.size();
	vector<vector<int>> mejores_ciclos(); // Ciclo con costo al final
	// vector de ciclos, donde en cada ciclo tenemos {v2,v0,v4,...,v9,CostoDeCiclo}
	vector<int> candidato = ciclo;
	int mejoraDeCosto;
	int random;


	candidato.push_back(l)
	// candidato con el costo al final


		
	for(int i = 0; i < n; i++){

		int costoViejo_i = matriz_adyacencia[i][i+1 % n];
		for(int j = i+1; j < n; j++){
			if((j+1) % n == i )break;
			
			int costoViejo_j = matriz_adyacencia[j][j+1 % n];

			// Para cada par de vertices, me fijo el swappeo
			candidato = swap(ciclo, i, j);
			//swapeamos a con c

			int costoNuevo_i = matriz_adyacencia[i][i+1 % n];
			int costoNuevo_j = matriz_adyacencia[j][j+1 % n];


			// Esto es basicamente para ahorrarse hacer "costo(candidato)"
			// El costo antes del swap +- las aristas involucradas
			candidato[n] = candidato[n] + costoNuevo_i + costoNuevo_j - costoViejo_i - costoViejo_j;
			
			srand(time(NULL));
			random = rand() % 100;
			if(random < SUBVECINIDAD_PORCENTAJE){
				mejores_ciclos.push_back(candidato)
			}
			candidato[n] = l; // reasigno el costo original del ciclo para que sea consistente el costo de los
			// candidatos en cada iteracion
		}
	}
	
	return mejores_ciclos;
}

vector<int> obtenerMejor(vector<vector<int>> vecindad){
	std::sort(vecindad.begin(), vecindad.end(), cicloMejor);
	vector<vector<int>> top(vecindad.begin(), vecindad.begin() + TOP_VECINDAD);

	srand(time(NULL)); //seed random
	int random = rand() % TOP_VECINDAD;

	return top[random];
}



vector<int> tabuSearch(int &l){
	vector<int> ciclo = heurAG(matriz_adyacencia, l);
	vector<int> mejorCiclo = ciclo;
	if(memoria_ciclos){
		// Inicialiar para recordar ciclos
	}
	else if(memoria_estructura){
		// Inicializar para recordar aristas
	}

	while(ITERACIONES_TABU){
		vector<vector<int>> subVecindad = localSearch2opt(solucionInicial, l);
		// Matriz con ciclos (C...,l(C)))
		ciclo = obtenerMejor(subVecindad, memoria);
		// Funcion de aspiracion??

		// Recordar este mejor ciclo

		// me quedo con el mejor
		if(costo(ciclo) < costo(mejorCiclo)){
			mejorCiclo = ciclo;
		}
		ITERACIONES_TABU--;
	}

	return mejorCiclo;
}