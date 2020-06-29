#include "funciones.h"
#include <list>
#include <algorithm>

using namespace std;

bool mayorQue(vector<int> aristaA, vector<int> aristaB){
    return aristaA[2] < aristaB[2];
}

vector<int> armarCircuito(vector<vector<int>> &arVec){ //arma respuesta de aristas elegidas
    vector<int> circuito(arVec.size(), -1);
    int peso = 0; int vertices = arVec.size(); vector<int> res;
    for(vector<int> x : arVec){
        peso += x[2];
        if(circuito[x[0]-1] != -1){circuito[x[1]-1] = x[0]-1;}
        else circuito[x[0]-1] = x[1]-1;
    }

    res.push_back(vertices);res.push_back(peso);
    int j = -1;
    while(j != 0){
        if(j == -1){j = 0;}
        res.push_back(j+1);
        j = circuito[j];
    }
    return res;
}


vector<int> aristaMinimaFactible(list<vector<int>> &aristasRestantes){//quizas sortear aristas para sacar en O(1)
    return aristasRestantes.front();
}

void actualizarEstados(vector<int> e, vector<int> &estadoVertices, list<vector<int>> &aristasRestantes){
    estadoVertices[e[0]] ++;
    estadoVertices[e[1]] ++;

    auto it = aristasRestantes.begin();
    while(it != aristasRestantes.end()) {//Sacar aristas inútiles
        if( (*it) == e || estadoVertices[(*it)[0]] == 2 || estadoVertices[(*it)[1]] == 2) {it = aristasRestantes.erase(it);}
        else {++it;}
    }
}

list<vector<int>> vec2list(vector<vector<int>> &X) {
    list<vector<int>> res;
    for(int i = 0; i < X.size(); i++){
        res.push_back(X[i]);
    }
    return res;
}

vector<vector<int>> matrizAVector(vector<vector<int>> matriz){
    vector<int> vecAristas;

    for(int i = 0; i < matriz.size(); i++){

        for (int j = i+1; j < matriz.size(); j++){
            vecAristas.push_back(matriz[i][j]);
        }
    }
    return vecAristas;
}
vector<int> golosoArista(vector<vector<int>> X){
    int V = X.size();
    vector<vector<int>> vecAristas = matrizAVector(X); //paso de matriz a vectores de aristas
    std::sort(vecAristas.begin(), vecAristas.end(), &mayorQue); // sort las aristas por peso
    list<vector<int>> aristasRestantes = vec2list(X); // igualar a X ordenada
    vector<int> estadoVertices(V, 0); // aca marco si cuanats veces se usa cada vertice
    vector<vector<int>> aristasH;

    for(int i = 0; i < V; i++){
        vector<int> e = aristaMinimaFactible(aristasRestantes);
        actualizarEstados(e, estadoVertices, aristasRestantes);
        aristasH.push_back(e);
    }
    return armarCircuito(aristasH);
}
/* lo que use pa testear
int main() {
    //int V = 4;
    //vector<vector<int>> X = {{1,2,10},{1,3,15},{1,4,20},{2,3,35},{2,4,25},{3,4,30}};
    //vector<int> camino = golosoArista(V,X);
    return 0;
}
*/