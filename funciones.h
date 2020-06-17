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



class union_find{ //clase creada para krustal eficiente
public:
    vector<int> padre;
    vector<int> altura;

    union_find(vector<int> p, vector<int> a); //creador
    int find(int x);						  //encuentra el padre del subarbol de x
    void unir(int x, int y);				  //cuelga el subarbol de x al de y

private:
    vector<int> _padre, _altura;
};

union_find::union_find(vector<int> p, vector<int> a):
        padre(a), altura(p){}

union_find init(int n){ //inicia un union_find con la cantidad de vertices siendo n
    vector<int> padre(n,0);
    vector<int> altura(n,1);
    for(int  i = 0; i<n; i++){
        padre[i] = i; //al principio cada vértice es su propio subarbol
    }
    union_find res = union_find(padre, altura);
    return res;
}

int union_find::find(int x){
    int p = _padre[x];
    if(p != x){                          //si no es raíz
        _padre[x] = this->find(p);	 //busco la raiz de su padre y la escribo como padre de x
        p = _padre[x];
    }
    return p;
}

void union_find::unir(int x, int y){
    x = this->find(x);						//busco amabs raices
    y = this->find(y);
    if(_altura[x] < _altura[y]){    // si el subarbol x es menor que el de y
        _padre[x] = y;					//cuelgo el de x al de y
    }else{
        _padre[y] = x;					//sino, al reves
    }
    if(_altura[x] == _altura[y]){	//si son de la misma alturam entones se colgó y a x, e x aumentó en 1 su altura
        _altura[x] += 1;
    }
}



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
