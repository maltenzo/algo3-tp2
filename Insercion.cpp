#include "funciones.h"

//despues lo adapto para que sea compatible con el main
vector<int> ciclo={0, 1, 2}; //empiezo con un ciclo base


int infinito = 10e6; // Valor grande para uasr de cota
vector<int> insercion(int& l){
    vector<bool> usados(g.size(), false);
    usados[0] = true;
    usados[1] = true;
    usados[2] = true;
    l = g[0][1] + g[1][2] + g[2][0];//longitud inicial del ciclo
    while(ciclo.size() < g.size()){ //mientras queden nodos sueltos sigo agregando
        int a = elegir(usados); // devuelvo el nodo elegido
        ciclo = insertar(ciclo, l, a);
        usados[a] = true;
    }
    return ciclo;
}

int elegir(vector<bool> usados){
    int e = 0;
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

int mas_cercana(vector<bool> usados){
    arista e = arista(0, 0, infinito);//uso el struct de arista por comodidad
    for (int i = 0; i <ciclo.size(); i++){//PARA TODOS LOS NODOS DENTRO DEL CICLO
        nodo = ciclo[i] // agarro el nodo en el ciclo
        for(int j = 0; j< g.size(); j++){//MIRO SUS VECINOS
            if (!usados[j]){//SI EL VECINO NO PERTENECE AL CICLO
                if (g[nodo][j] < e.peso){//EVALUO SI ES EL MAS BARATO
                    e = arista(nodo, j, g[nodo][j]);//ACTUALIZO LOS VALORES DEL MAS BARATO
                }
            }
        }
    }
    return e.fin;//el j que me quede es el nodo elegido
}



//esto puedo dejarlo mas bonito haciendo que se parezca a la funcion de insercion y reduciendo los for
//dsps lo hago porque alta paja
int mas_barata(vector<bool> usados){
    int nodo = 0;
    int l_min  = infinito;
    for(int i = 0; i < ciclo.size(); i++){//para todo par i, j de vertices en el ciclo
      nodo_i = ciclo[i];
        for(int j = i+1; j<=ciclo.size(); j++){
          j = j%ciclo.size();
          nodo_j = ciclo[j];
            for(int k = 0; k< g.size();k++){//tomo un vertice k que no pertenece al ciclo
                if (!usados[k]){
                    if(g[nodo_i][k] + g[k][nodo_j]- g[nodo_i][nodo_j] < l_min){ //busco la combinacion mas barata
                        l_min = g[nodo_i][k] + g[k][nodo_j]- g[nodo_i][nodo_j];//si la encontre, actualizo
                        nodo = k;
                    }
                }
            }
        }
    }
    return nodo;//el k que me quede es el nodo elegido
}


int mas_lejana(vector<bool> usados){
    arista e = arista(0, 0, -1);
    for(int i = 0; i< ciclo.size(); i++){//PARA TODOS LOS NODOS DENTRO DEL CICLO
        int nodo = ciclo[i]// agarro el nodo en el ciclo
        for(int j = 0; j< g.size(); j++){ //MIRO SUS VECINOS
            if (!usados[j]){//SI EL VECINO NO PERTENECE AL CICLO
                if (g[nodo][j] > e.peso){//EVALUO SI ES EL MAS lejano/caro
                    e = arista(nodo, j, g[nodo][j]);//ACTUALIZO LOS VALORES DEL MAS BARATO
                }
            }
        }
    }
    return e.fin; //el j que me quedo es el elegido
}

vector<int> insertar(int& l, int nodo){
    int l_min = infinito;
    int inicio = 0;
    int fin = 0;
    int j = 0;
    for (int i = 0; i < ciclo.size(); i++) {//uso todo nodo con el siguiente
        j = (i+1)%ciclo.size();
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
