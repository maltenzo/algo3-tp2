#include "funciones.h"
#include <iostream>
//despues lo adapto para que sea compatible con el main
vector<int> ciclo={0, 1, 2}; //empiezo con un ciclo base
int anterior_MB = 0;
int posterior_MB =0;


int infinito = 10e6; // Valor grande para uasr de cota
vector<int> insercion(int& l){
    vector<bool> usados(matriz_adyacencia.size(), false);
    usados[0] = true;
    usados[1] = true;
    usados[2] = true;
    l = matriz_adyacencia[0][1] + matriz_adyacencia[1][2] + matriz_adyacencia[2][0];//longitud inicial del ciclo

    while(ciclo.size() < matriz_adyacencia.size()){ //mientras queden nodos sueltos sigo agregando
        int a = elegir(usados); // devuelvo el nodo elegido
        ciclo = insertar(l, a);
        usados[a] = true;
    }
    for (int i = 0; i < ciclo.size(); i++) {
      ciclo[i] += 1;
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
//Finalmente no usamos las opciones de mas cercana ni mas barata, asi que no estan testadas. Solo utilizamos la opcion de mas barata
}

int mas_cercana(vector<bool> usados){
    arista e = arista(0, 0, infinito);//uso el struct de arista por comodidad
    int nodo;
    for (int i = 0; i <ciclo.size(); i++){//PARA TODOS LOS NODOS DENTRO DEL CICLO
        nodo = ciclo[i]; // agarro el nodo en el ciclo
        for(int j = 0; j< matriz_adyacencia.size(); j++){//MIRO SUS VECINOS
            if (!usados[j]){//SI EL VECINO NO PERTENECE AL CICLO
                if (matriz_adyacencia[nodo][j] < e.peso){//EVALUO SI ES EL MAS BARATO
                    e = arista(nodo, j, matriz_adyacencia[nodo][j]);//ACTUALIZO LOS VALORES DEL MAS BARATO
                }
            }
        }
    }
    return e.fin;//el j que me quede es el nodo elegido
}




int mas_barata(vector<bool> usados){
    int j;
    int nodo;
    int nodo_i;
    int nodo_j;
    int l_min  = infinito;
    for(int i = 0; i < ciclo.size(); i++){//para todo par i, j de vertices adyacentes en el ciclo
      nodo_i = ciclo[i];//agarro el i-esimo nodo
      j = (i+1)%ciclo.size();// si j = ciclo.size -> j = 0. Sino j = i+1
      nodo_j = ciclo[j];//agarro el j-esimo nodo
      for(int k = 0; k< matriz_adyacencia.size();k++){//tomo un vertice k que no pertenece al ciclo
            if (!usados[k]){
                if(matriz_adyacencia[nodo_i][k] + matriz_adyacencia[k][nodo_j]- matriz_adyacencia[nodo_i][nodo_j] < l_min){ //busco la combinacion mas barata
                    l_min = matriz_adyacencia[nodo_i][k] + matriz_adyacencia[k][nodo_j]- matriz_adyacencia[nodo_i][nodo_j];//si la encontre, actualizo
                    nodo = k;
                    anterior_MB = nodo_i;
                    posterior_MB = nodo_j;
                }
            }
        }

    }
    return nodo;//el k que me quede es el nodo elegido
}


int mas_lejana(vector<bool> usados){
    arista e = arista(0, 0, -1);
    for(int i = 0; i< ciclo.size(); i++){//PARA TODOS LOS NODOS DENTRO DEL CICLO
        int nodo = ciclo[i];// agarro el nodo en el ciclo
        for(int j = 0; j< matriz_adyacencia.size(); j++){ //MIRO SUS VECINOS
            if (!usados[j]){//SI EL VECINO NO PERTENECE AL CICLO
                if (matriz_adyacencia[nodo][j] > e.peso){//EVALUO SI ES EL MAS lejano/caro
                    e = arista(nodo, j, matriz_adyacencia[nodo][j]);//ACTUALIZO LOS VALORES DEL MAS BARATO
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

    inicio = anterior_MB;
    fin = posterior_MB;
    l_min = l + matriz_adyacencia[inicio][nodo] + matriz_adyacencia[nodo][fin] - matriz_adyacencia[inicio][fin];


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
