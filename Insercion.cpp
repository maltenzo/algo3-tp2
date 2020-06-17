#include "funciones.h"

//despues lo adapto para que sea compatible con el main



int infinito = 10e6; // Valor grande para uasr de cota
vector<int> insercion(int& l){
    vector<bool> usados(g.size(), false);
    usados[0] = true;
    usados[1] = true;
    usados[2] = true;
    l = g[0][1] + g[1][2] + g[2][0];//longitud inicial del ciclo
    vector<int> res={0, 1, 2}; //empiezo con un ciclo base
    while(res.size() < g.size()){ //mientras queden nodos sueltos sigo agregando
        int a = elegir(usados); // devuelvo el nodo elegido
        res = insertar(res, l, a);
        usados[a.fin] = true;
    }
    return res;
}

arista elegir(vector<bool> usados){
    arista e = arista(0, 0, 0);
    if (MC){//ELIJO LA MAS cercana
        e = mas_cercana(usados);
    }
    else if (MB){ //mas barata
        e = mas_barata(usados);
    }
    else{//mas lejana
        e = mas_lejana(usados);
    }
    return e;

}

arista mas_cercana(vector<bool> usados){
    arista e = arista(0, 0, infinito);//uso el struct de arista por comodidad
    for (int i = 0; i <g.size(); i++){//PARA TODOS LOS NODOS DENTRO DEL CICLO
        for(int j = 0; j< g.size(); j++){//MIRO SUS VECINOS
            if (!usados[j]){//SI EL VECINO NO PERTENECE AL CICLO
                if (g[i][j] < e.peso){//EVALUO SI ES EL MAS BARATO
                    e = arista(i, j, g[i][j]);//ACTUALIZO LOS VALORES DEL MAS BARATO
                }
            }
        }
    }
    return e.fin;//el j que me quede es el nodo elegido
}



//esto puedo dejarlo mas bonito haciendo que se parezca a la funcion de insercion y reduciendo los for
//dsps lo hago porque alta paja
arista mas_barata(vector<bool> usados){
    arista e = arista(0, 0, 0);
    int l_min  = infinito;
    for(int i = 0; i < g.size(); i++){//para todo par i, j de vertices en el ciclo
        for(int j = 0; j<g.size(); j++){
            for(int k = 0; k< g.size();k++){//tomo un vertice k que no pertenece al ciclo
                if (usados[i] && usados[j] && !usados[k]){
                    if(g[i][k] + g[k][j]- g[i][j] < l_min){ //busco la combinacion mas barata
                        l_min = g[i][k] + g[k][j]- g[i][j];//si la encontre, actualizo
                        e = arista(i, k, g[i][k]);//si la encontre, actualizo
                    }
                }
            }
        }
    }
    return e.fin;//el k que me quede es el nodo elegido
}


arista mas_lejana(vector<bool> usados){
    arista e = arista(0, 0, -1);
    for(int i = 0; i< g.size(); i++){//PARA TODOS LOS NODOS DENTRO DEL CICLO
        for(int j = 0; j< g.size(); j++){ //MIRO SUS VECINOS
            if (!usados[j]){//SI EL VECINO NO PERTENECE AL CICLO
                if (g[i][j] > e.peso){//EVALUO SI ES EL MAS lejano/caro
                    e = arista(i, j, g[i][j]);//ACTUALIZO LOS VALORES DEL MAS BARATO
                }
            }
        }
    }
    return e.fin; //el j que me quedo es el elegido
}

vector<int> insertar(vector<int> ciclo, int& l, int nodo){
    int l_min = infinito;
    int inicio = 0;
    int fin = 0;
    int j = 0;
    for (int i = 0; i < ciclo.size(); i++) {//uso todo nodo con el siguiente
        if(i+1 == ciclo.size()){
            j = 0;//si estoy en el ultimo el siguiente es el primero
        }else{
            j = i+1;
        }
        //busco el mejor lugar donde insertar el nuevo nodo
        if(l + g[i][nodo] + g[nodo][j] - g[i][j] < l_min){//veo si agregando un vertice intermedio consigo una mejor longitud
            l_min = l + g[i][nodo] + g[nodo][j] - g[i][j];//actualizo
            inicio = i;//me guardo el inicio para saber cual es el anterior a donde voy a poner el nuevo
            fin  = j;//este me lo guardo de yapa, no es util
        }
    }
    vector<int> v = {};
    //copio el ciclo viejo y agrego el nuevo nodo donde vaya
    for (int i = 0; i < ciclo.size(); i++) {
        v.push_back(ciclo[i]);
        if (ciclo[i] == inicio){
            v.push_back(nodo);
        }
    }
    l = l_min;//actualizo l (esta pasado por ref)
    return v;
}
