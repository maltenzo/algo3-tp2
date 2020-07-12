//
// Created by Usuario on 19/06/2020.
//

#include "tests.h"

vector<int> test_AGM_1(int& peso){
    grafo g(4,vector<int>(4,0));
    g[0][1] = 10;
    g[0][2] = 15;
    g[0][3] = 20;
    g[1][2] = 35;
    g[1][3] = 25;
    g[2][3] = 30;
    vector<arista> test_sort = sort_aristas(g);
    vector<arista> test_kruskal = kruskal(g);
    vector<vector<int>> arbol_t(g.size());
    for(int i = 0; i<test_kruskal.size();i++){
        arista e = test_kruskal[i];
        arbol_t[e.inicio].push_back(e.fin);
        arbol_t[e.fin].push_back(e.inicio);
    }
    vector<int> test_dfs = dfs_mejor(arbol_t);
    peso = 0;
    vector<int> test_agm = heurAG(g,peso);
    return test_agm;
}

vector<int> test_AGM_2(int& peso){
    grafo g(5,vector<int>(5,0));
    g[0][1] = 6;
    g[0][2] = 1;
    g[0][3] = 5;
    g[0][4] = 6;
    g[1][2] = 6;
    g[1][3] = 4;
    g[1][4] = 3;
    g[2][3] = 6;
    g[2][4] = 2;
    g[3][4] = 6;
    g[4][1] = 4;
    g[3][0] = 1;
    peso = 0;
    vector<int> test_agm = heurAG(g,peso);
    return test_agm;
}

vector<int> test_TABU_2(int& peso){
    grafo g(5,vector<int>(5,0));
    g[0][1] = 6;
    g[0][2] = 1;
    g[0][3] = 5;
    g[0][4] = 6;
    g[1][2] = 6;
    g[1][3] = 4;
    g[1][4] = 3;
    g[2][3] = 6;
    g[2][4] = 2;
    g[3][4] = 6;
    g[4][1] = 3;
    g[3][0] = 5;
    for(int i = 0; i<g.size();i++){
        for(int j = i+1; j<g.size();j++){
            g[j][i] = g[i][j];
        }
    }
    peso = 0;
    matriz_adyacencia = g;
    memoria_ciclos = true;
    memoria_estructura = false;
    vector<int> test_tabu = tabuSearch(peso);
    return test_tabu;
}