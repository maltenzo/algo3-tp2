
#ifndef FUNC_H
#define FUNC_H

#include "Tests/tests.h"
#include "vector"
using namespace std;
using lista_adyacencia = vector<vector<int>>;
using grafo = vector<vector<int>>;

struct arista{ //representa una arista
    int inicio;
    int fin;
    int peso;
    arista(int inicio, int fin, int peso): inicio(inicio), fin(fin), peso(peso){};
};

//agm.cpp
void merge_sort(vector<arista>& v,int v_1, int v_2);
vector<arista> sort_aristas(grafo g);
vector<arista> kruskal(grafo g);
vector<int> dfs(vector<arista> t);
vector<int> heurAG(grafo g, int& p);

//insercion cpp
vector<int> insercion(int& l);
int elegir(vector<bool> usados);
int mas_cercana(vector<bool> usados);
int mas_barata(vector<bool> usados);
int mas_lejana(vector<bool> usados);
vector<int> insertar(int& l, int e);
extern vector<vector<int>> matriz_adyacencia;
extern bool MC;
extern bool MB;
extern vector<int> ciclo;
extern int SUBVECINDAD_PORCENTAJE;
extern bool memoria_ciclos;
extern bool memoria_estructura;
extern unsinged int ITERACIONES_TABU;

#endif // FUNC_H
