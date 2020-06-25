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
unsinged int t = 60;

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

			        // (L) no creo que es necesario swapear ahora, talvez sea mejor simplemente guardar (p,i,j) p siendo el peso del ciclo con el swap


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

			        //(L) No sería mejor mantener los T mejores, más que hacer selección por random?
			        //    Para eso solo basta poner un if para ver si ya hay T soluciones, y cuando tnegamos más, nos fijamos si hay alguna peor para reemplazar

			candidato[n] = l; // reasigno el costo original del ciclo para que sea consistente el costo de los
			// candidatos en cada iteracion

			        //(L) reseteamos el peso, pero no volvemos a poner el orden correcto de los vertices
		}
	}
	
	return mejores_ciclos;
}

vector<int> obtenerMejor(vector<vector<int>> vecindad, vector<vector<int>> ultimosCiclos, vector<aristas> ultimosSwaps){
	std::sort(vecindad.begin(), vecindad.end(), cicloMejor); // cicloMejor funcion de comparacion

	// en principio recibe los dos, y usa uno u otro dependiendo de los booleanos
	// Quizas en lo que seria el vector de aristas, el campo de "peso" lo usemos como:
	// A valores mas grandes preferimos esa arista, y mas chico la 'desincentivamos'



}



vector<int> tabuSearch(int &l){
	vector<int> ciclo = heurAG(matriz_adyacencia, l);
	int n = ciclo.size(); // Asumo que viene el ciclo con los n vertices.
	vector<int> mejorCiclo = ciclo;
	vector<vector<int>> memoriaCiclos;
	vector<arista> memoriaEstructura; // Quizas usar otro struct, arista guarda el peso que por
	// el momento no me sirve

	        //(L) podemos usar el struct de forma poco ortodoxa: en vez de usarlo como una arista, hacer que represente los dos vértices que swapeamos y el cambio de peso

	if(memoria_ciclos){
		// Inicialiar para recordar ciclos
		// Si guardo ciclos, preciso un arreglo de tamanio 't' con los ultimos
		memoriaCiclos(t);
	}
	else if(memoria_estructura){
		// Inicializar para recordar aristas
		memoriaEstructura(t);
	}
	int idx_memoria = 0;

	while(ITERACIONES_TABU){ // en principio el criterio de parada que sea iteraciones fijas
	            // (L) me gustaría experimentar en el futuro con iteraciones de "no cambio". que opinian?

		vector<vector<int>> subVecindad = localSearch2opt(solucionInicial, l);
		// Matriz con ciclos (C...,l(C)))
		ciclo = obtenerMejor(subVecindad, memoria);
		// Funcion de aspiracion??

		// Recordar en memoria: o ciclos, o swaps

		// Recordar este mejor ciclo
		if(memoria_ciclos){
			memoriaCiclos[idx_memoria] = ciclo;
			idx_memoria = (idx_memoria + 1) % t; // Guardo los ultimos t
		}
		else if(memoria_estructura){
			// Creo que no podria hacerlo aca eficientemente
			// Y hay que hacerlo en 2opt??
			        //(L) creo que con que hagamos lo mismo que con los ciclos, va bien.
			        //    Eliminar la más vieja y poner una nueva
		}

		// me quedo con el mejor
		if(ciclo[n] < mejorCiclo[n]){
			mejorCiclo = ciclo;
		}
		ITERACIONES_TABU--;
	}

	return mejorCiclo;
}
