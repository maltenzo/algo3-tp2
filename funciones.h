#ifndef FUNC_H
#define FUNC_H

#include "vector"
using namespace std;

struct arista{ //representa una arista
    int inicio;
    int fin;
    int peso;
    arista(int inicio, int fin, int peso): inicio(inicio), fin(fin), peso(peso){};
};


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
