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

#define OPT_ITERACIONES 100
#define SUBVECINIDAD_TAM 10

int INFTY = 10e6; // Valor para indicar que no hubo solución.

int costo(vector<int> ciclo){
	int res = 0;
	for(int i = 0; i < ciclo.size()-1; i++){
		res += matriz_adyacencia[i][i+1];
	}
	return res;
}

void swap(vector<int> &c, int i, int j){
	int a = c[i];
	c[i] = c[j]; // c[i] = b = c[j]
	c[j] = a;
}

// Grafo G, tengo matriz de adyacencia
// Esta version inicial solo devuelve 1 vecino 2opt, claramente desaprovechamos
// mucho computo y podriamos usar el top 10 o ir guardando mas de uno.



vector<vector<int>> localSearch2opt(vector<int> ciclo, const int l){ // recibe el ciclo generado por AGM o alguna otra heuristica
	// l es el costo del circuito que me pasan
	// Pre, el ciclo es de longitud n = matriz_adyacencia.size()
	
	int n = ciclo.size();
	vector<vector<int>> mejores_ciclos(SUBVECINIDAD_TAM, vector<int>(n+1, INFTY)); // Ciclo con costo al final
	// vector de ciclos, donde en cada ciclo tenemos {v2,v0,v4,...,v9,CostoDeCiclo}
	vector<int> candidato = ciclo;
	int mejoraDeCosto;


	candidato.push_back(l)
	// candidato con el costo al final

	for(int it = 0; it < OPT_ITERACIONES; it++){ 
		
		for(int i = 0; i < n; i++){
			int arista_ab = matriz_adyacencia[candidato[i]][candidato[(i+1) % n]]; // Arista A--B
			int arista_preaA = matriz_adyacencia[candidato[i]][candidato[(i-1) % n]]; // Arista A--Anterior A
			for(int j = 0; j < n; j++){
				// Para cada par de vertices, me fijo el swappeo

				
				int arista_cd = matriz_adyacencia[candidato[j]][candidato[(j+1) % n]]; // Arista C--D
				int arista_preC = matriz_adyacencia[candidato[j]][candidato[(j-1) % n]]; // Arista C-- anterior c
				candidato = swap(candidato, i, j);
				//swapeamos a con c
				int arista_cb = matriz_adyacencia[candidato[i]][candidato[(i+1) % n]];//esta no se puede sacar del ciclo porque es post swap
				int arista_ad = matriz_adyacencia[candidato[j]][candidato[(j+1) % n]];
				int arista_preAC = matriz_adyacencia[candidato[i]][candidato[(i-1) % n]];//esta no se puede sacar del ciclo porque es post swap
				int arista_preCA = matriz_adyacencia[candidato[j]][candidato[(j-1) % n]];
				// Si intercambiando preA--A--B por preA--C--B, y preC--C--D por preC--A--D mejora:

				// Esto es basicamente para ahorrarse hacer "costo(candidato)"
				// El costo antes del swap +- las aristas involucradas
				candidato[n] = candidato[n] -  arista_ab - arista_cd + arista_cb + arista_ad - arista_preA - arista_preC + arista_preAC + arista_preCA ;
				
				
				for(int k = 0; k < SUBVECINIDAD_TAM; k++){
					if(k == SUBVECINIDAD_TAM){
						if(mejores_ciclos[SUBVECINIDAD_TAM - k][n] > candidato[n]){
							mejores_ciclos[SUBVECINIDAD_TAM - k] = candidato;
							break;
						}						
					}
					
					else if(mejores_ciclos[SUBVECINIDAD_TAM - k][n] > candidato[n] && candidato[n] > mejores_ciclos[SUBVECINIDAD_TAM-k-1][n]){
						mejores_ciclos[SUBVECINIDAD_TAM - k] = candidato;
						break;
					} // Remplazo por el peor de los que voy guardando
				}
			}
		}
	}
	return mejores_ciclos;
}
