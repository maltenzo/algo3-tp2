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


int idx_memoria = 0;


vector<arista> porcentaje_random(vector<arista> &vecinos, int cantidad){
	int random;
	vector<arista> res;
    if(cantidad == 0){
        cantidad = 1;
    }
	while(cantidad--){
		srand(time(NULL));
		random = rand() % vecinos.size();
		res.push_back(vecinos[random]);

		vecinos.erase(vecinos.begin()+random);

	}
	return res;
}

// Funcion para ordenar la subvecindad
bool cicloMejor(arista C1, arista C2){
	return C1.peso < C2.peso;
}

int costo(vector<int> ciclo){
	int res = 0;
	for(int i = 0; i < ciclo.size(); i++){
		res += matriz_adyacencia[i][i+1 % ciclo.size()];
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

vector<arista> localSearch2opt(vector<int> ciclo, const int l){ // recibe el ciclo generado por AGM o alguna otra heuristica
	// l es el costo del circuito que me pasan
	// Pre, el ciclo es de longitud n = matriz_adyacencia.size()
	
	int n = ciclo.size(); 
	vector<arista> subvecindad; // Vamos a retornar los vecinos como:
	// (vi,vj, costo del ciclo al swappear las aristas incidentes a estos)
	// esto resulta util para cuando querramos guardar las aristas en la lista tabu
	// y ademas nos evitamos construir ciclos innecesarios, solo al momento de guardarlos en soluciones ya exploradas
	
	arista candidato(0, 0, l); // el inicio y fin no representan nada ahora

	for(int i = 0; i < n; i++){

		int costoViejo_i = matriz_adyacencia[ciclo[i]][ciclo[(i+1) % n]];
		for(int j = i+1; j < n; j++){
			if((j+1) % n == i )break;
			
			int costoViejo_j = matriz_adyacencia[ciclo[j]][ciclo[(j+1) % n]];

			candidato.inicio = i; 
			candidato.fin = j;
			// me guardo las posiciones que swappearia, no los vectores

			int costoNuevo_i = matriz_adyacencia[ciclo[i]][ciclo[j]];
			int costoNuevo_j = matriz_adyacencia[ciclo[(i+1) % n]][ciclo[(j+1) % n]];


			// Esto es basicamente para ahorrarse hacer "costo(candidato)"
			// El costo antes del swap +- las aristas involucradas
			candidato.peso = candidato.peso + costoNuevo_i + costoNuevo_j - costoViejo_i - costoViejo_j;
			//recordar que peso en este contexto no representa el peso de la arista sino el costo total del
			//ciclo tras swappear candidato.inicio y candidato.fin

			subvecindad.push_back(candidato); // es la vecindad completa

			candidato.peso = l; // reasigno el costo original del ciclo para que sea consistente el costo de los
			// candidatos en cada iteracion

		}
	}
	

	int cantidad = subvecindad.size(); //cantidad de vecinos en la subvecinidad
	/*if(cantidad > 20){                  //si tenemos más de 20
        srand(time(0));       //queremos usar un porcentaje random
	    int random = rand() % 101;
	    if(random < 30){                //entre 30%
	        random += 30;
	    }else if (random > 80){         //y 80%
	        random -= 20;
	    }
	    cantidad = cantidad*random/100;
	}*/

	// SUBVECINDAD_PORCENTAJE es un numero entre 1 y 100. 
    //subvecindad = porcentaje_random(subvecindad, cantidad );
	
	subvecindad = porcentaje_random(subvecindad, (cantidad*SUBVECINDAD_PORCENTAJE)/100 );
	return subvecindad;
}

vector<int> obtenerMejor(vector<arista> &subvecindad, vector<int> ciclo, int &costoCiclo,
 vector<vector<int>> &ultimosCiclos, vector<arista> &ultimosSwaps){
	

	//std::sort(subvecindad.begin(), subvecindad.end(), mejorCostoVecinos); // mejorCostoVecinos funcion de comparacion
	// las ordeno por costo
	
	//por ciclos
	vector<int> mejor;
	vector<int> vecino;
	
	int costo_mejor = INFTY; // guardo el costo del mejor ciclo que no este en la LTabu
	// por aristas
	arista elegida(0,0,0);
	arista mejor_arista;
	int i=0; int j=0; // estos los necesito si voy por aritas para reconstruir el mejor ciclo y devolverlo


	int costoTrasSwap;	
		
		for(int k = 0; k < subvecindad.size(); k++){ // recorro la subvecindad
			elegida = subvecindad[k];
			
			if(memoria_ciclos){ // tengo que construir los ciclos con el swap
				// descarto por tabu y su costo


				vecino = swap(ciclo, elegida.inicio, elegida.fin);
				if(find(ultimosCiclos.begin(), ultimosCiclos.end(), vecino) != ultimosCiclos.end()) break;
				// si el vecino esta sigo esta en los explorados, sigo con el siguiente

				if(elegida.peso < costo_mejor){
					mejor = vecino;
					costo_mejor = elegida.peso;
					i = elegida.inicio;
					j = elegida.fin;
				}
			}
			else if(memoria_estructura){
				// descarto por tabu y su costo

				costoTrasSwap = elegida.peso;
				
				int indice_i = elegida.inicio;
				int indice_j = elegida.fin;

				elegida.inicio = ciclo[elegida.inicio];
				elegida.fin = ciclo[elegida.fin]; // esto es pq me guarde los i, j y no los v_i v_j
				elegida.peso = matriz_adyacencia[elegida.inicio][elegida.fin];// la hago consistente

				// en memoria las tengo efectivamente como (vi, vj, peso((vi,vj)))
				// ahora la busco en memoria
				
				if(find(ultimosSwaps.begin(), ultimosSwaps.end(), elegida) != ultimosSwaps.end()) break;
				
				arista inversa(elegida.fin, elegida.inicio, elegida.peso);
				if(find(ultimosSwaps.begin(), ultimosSwaps.end(), inversa) != ultimosSwaps.end()) break;

				if(costoTrasSwap < costo_mejor){
					mejor_arista = elegida;
					costo_mejor = costoTrasSwap;
					i = indice_i;
					j = indice_j;
				}


			}
		}
		// Recordar en memoria: o ciclos, o swaps

		// Recordar este mejor ciclo

		// Puede pasar que todo sea TABU y no encontre nada, en este caso 'mejor' es un vector vacio
		// en el caso de memoria_ciclos, y si no tengo los indices en i = j = 0 
		if(memoria_ciclos){
			
			if(mejor.empty()){
				for(int k = 0; k < subvecindad.size(); k++){
					elegida = subvecindad[k];
					if(elegida.peso < costo_mejor){
						costo_mejor = elegida.peso;
						i = elegida.inicio;
						j = elegida.fin;
					} // Me quede con los mejores swaps 					
				}

			} else {
				ultimosCiclos[idx_memoria] = mejor;
				idx_memoria = (idx_memoria + 1) % t; // Guardo los ultimos t
			}
		}
		else if(memoria_estructura){
			if(i == 0 && j == 0){
				for(int k = 0; k < subvecindad.size(); k++){
					elegida = subvecindad[k];
					if(elegida.peso < costo_mejor){
						costo_mejor = elegida.peso;
						i = elegida.inicio;
						j = elegida.fin;
					} // Me quede con los mejores swaps, y no los guardo, porque son tabu 					
				}
			} else {

				ultimosSwaps[idx_memoria] = mejor_arista;
				idx_memoria = (idx_memoria + 1) % t;
				arista mejor_arista2(ciclo[i+1 % ciclo.size()], ciclo[j+1 % ciclo.size()], matriz_adyacencia[ciclo[i+1 % ciclo.size()]][ciclo[j+1 % ciclo.size()]]);
				ultimosSwaps[idx_memoria] = mejor_arista2;
				idx_memoria = (idx_memoria + 1) % t;
			}
		}
		
		mejor = swap(ciclo, i, j);
		costoCiclo = costo_mejor;
		
		return mejor;

}



vector<int> tabuSearch(int &l){
	vector<int> ciclo = golosoArista(matriz_adyacencia, l);
	int n = ciclo.size(); // Asumo que viene el ciclo con los n vertices.

	for(int i = 0; i < n; i++)ciclo[i]--;
	vector<int> mejorCiclo = ciclo;
	int costoCiclo = l;
	vector<vector<int>> memoriaCiclos;
	vector<arista> memoriaEstructura; // Usamos arista como: (vi,vj, peso del ciclo )

	        //(L) podemos usar el struct de forma poco ortodoxa: en vez de usarlo como una arista, hacer que represente los dos vértices que swapeamos y el cambio de peso

	if(memoria_ciclos){
		// Inicialiar para recordar ciclos
		// Si guardo ciclos, preciso un arreglo de tamanio 't' con los ultimos
		memoriaCiclos.resize(t);
	}
	else if(memoria_estructura){
		// Inicializar para recordar aristas
		memoriaEstructura.resize(t);
	}
		

	while(ITERACIONES_TABU){ // en principio el criterio de parada que sea iteraciones fijas
	            // (L) me gustaría experimentar en el futuro con iteraciones de "no cambio". que opinian?

		vector<arista> subVecindad = localSearch2opt(ciclo, costoCiclo);
		// Matriz con los swaps y el costo al hacerlo (vi, vj, costo)

		ciclo = obtenerMejor(subVecindad, ciclo, costoCiclo, memoriaCiclos, memoriaEstructura); // en esta funcion se reconstruye el ciclo
		// Preciso pasarle el ciclo de esta iteracion para poder construirlo a partir de los swaps

		// Costo ciclo guarda el costo del ciclo elegido

		// Funcion de aspiracion??

		// me quedo con el mejor
		if(costoCiclo < l){
			mejorCiclo = ciclo;
			l = costoCiclo;

		}

		ITERACIONES_TABU--;
	}

	for(int i=0; i<mejorCiclo.size(); i++){
	    mejorCiclo[i]++;
	}

	return mejorCiclo;
}
