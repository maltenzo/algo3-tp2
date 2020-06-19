#ifndef FUNC_H
#define FUNC_H

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


void merge_sort(vector<arista>& v,int v_1, int v_2);
vector<arista> sort_aristas(grafo g);
vector<arista> kruskal(grafo g);
vector<int> dfs(vector<arista> t);
vector<int> heurAG(grafo g);

vector<int> insercion(int& l);
arista elegir(vector<bool> usados);
arista mas_cercana(vector<bool> usados);
arista mas_barata(vector<bool> usados);
arista mas_lejana(vector<bool> usados);
vector<int> insertar(vector<int> ciclo, int& l, arista e);
extern vector<vector<int>> g;
extern bool MC;
extern bool MB;


#endif // FUNC_H
