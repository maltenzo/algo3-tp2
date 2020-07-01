//
// Created by Usuario on 01/07/2020.
//

#ifndef TP2_GITHUB_UNIR_FIND_HPP
#define TP2_GITHUB_UNIR_FIND_HPP

#include "funciones.h"

class unir_find{ //clase creada para krustal eficiente
public:
    vector<int> padre;
    vector<int> altura;

    unir_find(vector<int> p, vector<int> a); //creador
    int find(int x);						  //encuentra el padre del subarbol de x
    void unir(int x, int y);				  //cuelga el subarbol de x al de y

};

unir_find::unir_find(vector<int> p, vector<int> a):
        padre(p), altura(a){}

unir_find init(int n){ //inicia un unir_find con la cantidad de vertices siendo n
    vector<int> padre(n,0);
    vector<int> altura(n,1);
    for(int  i = 0; i<n; i++){
        padre[i] = i; //al principio cada vértice es su propio subarbol
    }
    unir_find res = unir_find(padre, altura);
    return res;
}

int unir_find::find(int x){
    int p = padre[x];
    if(p != x){                          //si no es raíz
        padre[x] = this->find(p);	 //busco la raiz de su padre y la escribo como padre de x
        p = padre[x];
    }
    return p;
}

void unir_find::unir(int x, int y){
    x = this->find(x);						//busco amabs raices
    y = this->find(y);
    if(altura[x] < altura[y]){    // si el subarbol x es menor que el de y
        padre[x] = y;					//cuelgo el de x al de y
    }else{
        padre[y] = x;					//sino, al reves
    }
    if(altura[x] == altura[y]){	//si son de la misma alturam entones se colgó y a x, e x aumentó en 1 su altura
        altura[x] += 1;
    }
}

#endif //TP2_GITHUB_UNIR_FIND_HPP
