//
// Created by Usuario on 19/06/2020.
//

#include "tests.h"

vector<int> test_AGM_1(){
    grafo g(4,vector<int>(4,0));
    g[0][1] = 10;
    g[0][2] = 15;
    g[0][3] = 20;
    g[1][2] = 35;
    g[1][3] = 25;
    g[2][3] = 30;
    vector<arista> test_sort = sort_aristas(g);
    vector<arista> test_kruskal = kruskal(g);
    vector<int> test_dfs = dfs(test_kruskal);
    int peso = 0;
    vector<int> test_agm = heurAG(g,peso);
    test_agm.push_back(peso);
    return test_agm;
}

vector<int> test_AGM_2(){
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
    int peso = 0;
    vector<int> test_agm = heurAG(g,peso);
    test_agm.push_back(peso);
    return test_agm;
}