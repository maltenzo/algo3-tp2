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
    vector<int> test_agm = heurAG(g);
    return test_agm;
}
