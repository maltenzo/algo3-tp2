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

int INFTY = 10e6; // Valor para indicar que no hubo solución.

int costo(vector<int> ciclo){
	int res = 0;
	for(int i = 0; i < ciclo.size()-1; i++){
		res += matriz_adyacencia[i][i+1];
	}
	return res;
}

vector<int> swap(vector<int> c, int i, int j){
	int a = c[i];
	c[i] = c[j]; // c[i] = b (c[j])
	c[j] = a;
	return c;
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
		int arista_ab = matriz_adyacencia[candidato[i]][candidato[(i+1) % n]]; // Arista A--B
		int arista_preaA = matriz_adyacencia[candidato[i]][candidato[(i-1) % n]]; // Arista A--Anterior A
		for(int j = 0; j < n; j++){
			// Para cada par de vertices, me fijo el swappeo

			
			int arista_cd = matriz_adyacencia[candidato[j]][candidato[(j+1) % n]]; // Arista C--D
			int arista_preC = matriz_adyacencia[candidato[j]][candidato[(j-1) % n]]; // Arista C-- anterior c
			candidato = swap(ciclo, i, j);
			//swapeamos a con c
			int arista_cb = matriz_adyacencia[candidato[i]][candidato[(i+1) % n]];//esta no se puede sacar del ciclo porque es post swap
			int arista_ad = matriz_adyacencia[candidato[j]][candidato[(j+1) % n]];
			int arista_preAC = matriz_adyacencia[candidato[i]][candidato[(i-1) % n]];//esta no se puede sacar del ciclo porque es post swap
			int arista_preCA = matriz_adyacencia[candidato[j]][candidato[(j-1) % n]];
			// Si intercambiando preA--A--B por preA--C--B, y preC--C--D por preC--A--D mejora:

			// Esto es basicamente para ahorrarse hacer "costo(candidato)"
			// El costo antes del swap +- las aristas involucradas
			candidato[n] = candidato[n] -  arista_ab - arista_cd + arista_cb + arista_ad - arista_preA - arista_preC + arista_preAC + arista_preCA ;
			
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
