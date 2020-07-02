#include "funciones.h"
#include <list>
#include <algorithm>

using namespace std;

bool mayorQue(vector<int> aristaA, vector<int> aristaB){
    return aristaA[2] < aristaB[2];
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

bool hayCircuito(vector<vector<int>> aristasElegidas,vector<int> e){
    if(aristasElegidas.size() == 0) return false;//elijo un punto de partida y uno de llegada
    int actual = e[0]; int obj = e[1];
    list<vector<int>> listaAristas = vec2list(aristasElegidas);

    auto it = listaAristas.begin();
    while(it != listaAristas.end()) { //busco camino entre el actual y el objetivo

        if((*it)[0] == actual){ //si alguna arista contiene al actual actualizo
            if((*it)[1] == obj){return true;// el el otro extremo es el objetivo devuelvo true
            } else {
                actual = (*it)[1];
                it = listaAristas.erase(it);
                it = listaAristas.begin();
            }

        } else if ((*it)[1] == actual){
            if((*it)[0] == obj){return true;
            } else {
                actual = (*it)[0];
                it = listaAristas.erase(it);
                it = listaAristas.begin();
            }

        } else {++it;}
    }
    return false;
}

vector<int> aristaMinimaFactible(list<vector<int>> &aristasRestantes, vector<vector<int>> aristasElegidas){//quizas sortear aristas para sacar en O(1)
    if(aristasRestantes.size() == 1){return aristasRestantes.front();}// si queda una arista me la quedo

    auto it = aristasRestantes.begin(); // si no itero sobre la lista de aristas restantes
    bool encontre = false; vector<int> e;
    while(!encontre){
        if(!hayCircuito(aristasElegidas, (*it))) { //si no genera circuito la agarro
            e = *it;
            encontre = true;
        } else {                    //si no miro la proxima
            ++it;
        }
    }
    return e;
}

vector<int> armarCircuito(vector<vector<int>> &arVec, int & peso_circ){ //arma respuesta de aristas elegidas
    list<vector<int>> listaAristas = vec2list(arVec);
    vector<int> res;
    int peso = 0; int vertices = arVec.size();

    int previo = 1;
    auto it = listaAristas.begin();
    while(listaAristas.size() != 0) {//Itero sobre aristas elegidas

       if((*it)[0] == previo) { //miro en el primer vertice de la arista di es el previo
           if(res.size() == 0){res.push_back((*it)[0]);// si estoy en el primer par de aristas meto las dos
                res.push_back((*it)[1]);
               peso += (*it)[2]; // agrego el peso de la arista
               previo = (*it)[1]; //actualizo de donde vengo
                it = listaAristas.erase(it);//saco las aristas que voy metiendo
               it = listaAristas.begin();//volvemos a empezar con la nueva lista
           }
           else {
               peso += (*it)[2];
               if(listaAristas.size() == 1) break;//mismo agregando solo la proxima
               res.push_back((*it)[1]);
               previo = (*it)[1];
               it = listaAristas.erase(it);
               it = listaAristas.begin();}

       } else if((*it)[1] == previo){ //mismo pero mirando segundo vertice de la arista
                if(res.size() == 0){res.push_back((*it)[1]);
                    res.push_back((*it)[0]);
                    peso += (*it)[2];
                    previo = (*it)[0];
                    it = listaAristas.erase(it);
                    it = listaAristas.begin();
                }
                else {
                    peso += (*it)[2];
                    if(listaAristas.size() == 1) break;
                    res.push_back((*it)[0]);
                    previo = (*it)[0];
                    it = listaAristas.erase(it);}
                    it = listaAristas.begin();
       } else {
           ++it;
       }
    }

    peso_circ = peso;

return res;
}

vector<vector<int>> matrizAVector(vector<vector<int>> matriz){
    vector<vector<int>> vecAristas;

    for(int i = 0; i < matriz.size(); i++){
        for (int j = i+1; j < matriz.size(); j++){
            vecAristas.push_back({i+1,j+1,matriz[i][j]});
        }
    }
    return vecAristas;
}
vector<int> golosoArista(vector<vector<int>>& X, int& peso_circ){
    int V = X.size();
    vector<vector<int>> vecAristas = matrizAVector(X); //paso de matriz a vectores de aristas
    std::sort(vecAristas.begin(), vecAristas.end(), &mayorQue); // sort las aristas por peso
    list<vector<int>> aristasRestantes = vec2list(vecAristas); // igualar a vecAristas ordenada
    vector<int> estadoVertices(V, 0); // aca marco si cuanats veces se usa cada vertice
    vector<vector<int>> aristasH;

    for(int i = 0; i < V; i++){
        vector<int> e = aristaMinimaFactible(aristasRestantes, aristasH);
        actualizarEstados(e, estadoVertices, aristasRestantes);
        aristasH.push_back(e);
    }
    return armarCircuito(aristasH, peso_circ);
}
