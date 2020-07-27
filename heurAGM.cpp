#include "funciones.h"
#include "unir_find.hpp"
#include <algorithm>


bool mayorQueAGM(arista aristaA, arista aristaB){
    return aristaA.peso < aristaB.peso;
}
//merge sort basado en el peso de la aristas
void merge_sort(vector<arista>& v,int v_1, int v_2){ //v es el vector, v_1 indice inclusive bajo, v_2 indice exclusivo alto
	if(v_1 + 1 == v_2){
		return;
	}else{
		int split = v_1 + (v_2-v_1)/2;
		merge_sort(v, v_1, split);
		merge_sort(v, split, v_2);
		int i = v_1;
		int j = split;
        vector<arista> nuevo = v;

		while(i < split && j < v_2){ //añado la arista más ligera de entre ambas partes del vector a nuevo
			if( v[i].peso < v[j].peso){
				nuevo[i+j-split] = v[i];
				i++;
			}else{
				nuevo[i+j-split] = v[j];
				j++;
			}
		}

		while(i < split){ //agrego las aristas que quedan de la primera parte de v
			nuevo[i+j-split] = v[i];
			i++;
		}

		while(j < v_2){//agrego las aristas restantes de la segunda parte de v
			nuevo[i+j-split] = v[j];
			j++;
		}

		v = nuevo;
		return;
	}
}

vector<arista> sort_aristas(grafo g){ //ordeno las aristas por peso
	vector<arista> res(g.size()*(g.size()-1)/2, arista(-1,-1,-1));
	int k = 0;
	for(int i = 0; i<g.size(); i++){
		for(int j = i+1; j<g.size();j++){
			arista e = arista(i,j,g[i][j]); //primero pongo todas las aristas en un solo vector
			res[k] = e;
			k++;
		}
	}
	//merge_sort(res,0,res.size()); //luego uso merge
    std::sort(res.begin(), res.end(), &mayorQueAGM);
	return res;
}

vector<arista> kruskal(grafo g){ //creo un AGM con krustal
	int n = g.size();
	vector<arista> res(n-1, arista(-1,-1,-1));
	unir_find arboles = init(n);                        //arboles es el unir_find que voy a usar
	vector<arista> aristas_ordenadas = sort_aristas(g);	   //hago el sort de las aristas
	int arista = 0;									   //empiezo en 1 pq ya tengo un subarbol con 1 arista

	for(int i = 0; i<aristas_ordenadas.size() && arista<n-1;i++){	   //meintras haya aristas, y no agregué todos los vértices
		struct arista e = aristas_ordenadas[i];
		int v = e.inicio;
		int w = e.fin;
		if(arboles.find(v) != arboles.find(w)){			   //si no tienen el mismo padre los meinbros de la arista
			arboles.unir(v,w);							   //uno los subarboles
			res[arista] = e;							   //agrego la arsta e al arbol
			arista++;

		}
	}

	return res;
}

vector<int> dfs_mejor(vector<vector<int>> t){
    int padre = 0;                          //padre indica que lista en t estamos viendo, es el padre del vértice que encontremos
    int nro_orden = 1;                      //nro de orden es el que le vamos a asignar al vérticce que encontremos
    int i = 0;                              //indice de la lista de adyacentes de "padre"
    vector<int> orden(t.size(),0);     // orden es el ciclo final
    vector<int> padres(t.size(),-1);    // vector que nos dicen quien es el padre del vértice v_I en padre[v_i]
    vector<int> indices(t.size(),-1);   //indices de donde nos quedamos al recorrer la lista de adyacencia de v_i
    padres[padre] = padre;                     //el padre de 0 es el mismo, por ser raíz
    indices[padre] = i;                         //su indice es 0
    while(nro_orden <t.size()){              //mientras no hayamos dado ordena  todos los vértices
        if(i == t[padre].size()){           // si recorrimos todos los adyacentes de "padre"
            indices[padre] = i;                 //guardamos el indice
            padre = padres[padre];              // nos movemos al padre de "padre"
            i = indices[padre];                 // indice del padre
            i++;                                //avanzo
        }else{                              //si estamos buscando hijos
            int hijo = t[padre][i];         //veo un hijo
            if(hijo != padres[padre]){      //si no es el padre de nuestro padre
                orden[nro_orden] = hijo;        //le doy orden
                nro_orden++;
                indices[padre] = i;             //guardo el indice de "padre"
                padres[hijo] = padre;           //marco como padre de "hijo" a "padre"
                padre = hijo;                   //nos movemos al hijo
                i = indices[hijo];              //buscamos el indice del hijo
            }
            i++;                                //avanzamos
        }
    }
    return orden;
}

vector<int> heurAG(grafo g, int& p){
	auto kruskal_i = chrono::steady_clock::now();
	vector<arista> t = kruskal(g);          //Hago el arbol, representado como una lista de adyacencia
	auto kruskal_f = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(kruskal_f - kruskal_i).count();
	cout << "kruskal:" << total_time << endl; 
	
	vector<vector<int>> arbol_t(g.size());
	
	for(int i = 0; i<t.size();i++){
	    arista e = t[i];
	    arbol_t[e.inicio].push_back(e.fin);
	    arbol_t[e.fin].push_back(e.inicio);
	}
	auto dfs_i = chrono::steady_clock::now();
	vector<int> orden = dfs_mejor(arbol_t);             //Recorro por dfs, para saber los ordenes
	auto dfs_f = chrono::steady_clock::now();
	total_time = chrono::duration<double, milli>(dfs_f - dfs_i).count();
	cout << "dfs:" << total_time << endl; 
	
	p = 0;                                  //seteo el peso en 0
    p += g[orden[0]][orden[orden.size()-1]]; //añado la arsita que completa el circuito
    orden[0] = 1;                           //cambio el vertice a convención 1,n
    for(int i = 1; i<orden.size(); i++){
        p  += g[orden[i-1]-1][orden[i]];    //Agrego el peso de la arista (V_i-1,V_i)
        orden[i] = orden[i]+1;              // Agrego el vértice i de orden
	}

	return orden;
}
