#include "funciones.h"

//merge sort basado en el peso de la aristas
void merge_sort(vector<arista>& v,int v_1, int v_2){ //v es el vector, v_1 indice inclusive bajo, v_2 indice exclusivo alto
	if(v.size() == 1){
		return;
	}else{
		int split = v.size()/2;
		merge_sort(v, v_1, split);
		merge_sort(v, split, v_2);
		int i = 0;
		int j = split;

		while(i < split && j < v_2){
			if( v[i].peso < v[j].peso){
				v[i+j-split] = v[i];
				i++;
			}else{
				v[i+j-split] = v[j];
				j++;
			}
		}

		while(i < v_1){
			v[i+j-split] = v[i];
			i++;
		}

		while(j < v_2){
			v[i+j-split] = v[j];
			j++;
		}

		return;
	}
}

vector<arista> sort_aristas(grafo g){ //ordeno las aristas por peso
	vector<arista> res(g.size()*g.size(), arista(-1,-1,-1));
	for(int i = 0; i<g.size(); i++){
		for(int j = 0; j<g.size();j++){
			arista e = arista(i,j,g[i][j]); //primero pongo todas las aristas en un solo vector
			res[i+j] = e;
		}
	}
	merge_sort(res,0,g.size()); //luego uso merge
	return res;
}

vector<arista> kruskal(grafo g){ //creo un AGM con krustal
	int n = g.size();
	vector<arista> res(n-1, arista(-1,-1,-1));
	union_find arboles = init(n);                          //arboles es el union_find que voy a usar
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

//parte recursia de DFS
void dfs_recu(vector<arista> t, vector<int>& orden, int padre, int& nro_orden){ //orden es la lista del orden de los vértices, padre es el vertice padre
    for(int i = 0; i<t.size() && nro_orden<orden.size(); i++){ //en cada recursion, reviso todas las aristas para buscar una con el padre
        arista e = t[i];
        if(e.inicio == padre){                                  //si encuentro una
            orden[nro_orden] = e.fin;                           //agrego el otro vértice al orden
            nro_orden++;
            dfs_recu(t,orden,e.fin,nro_orden);           //sigo la rama por ese vértice
        }else if(e.fin == padre){
            orden[nro_orden] = e.inicio;
            nro_orden++;
            dfs_recu(t,orden,e.fin,nro_orden);
        }
    }
    return;

}

vector<int> dfs(vector<arista> t){
    int padre = 0;                              //padre es el vértice que vemos
    int nro_orden = 0;                          //número de ordenq del vértice que estamos buscando en el momento
    vector<int> orden(t.size()+1,-1);  //creo la lista de vértices en orden de recorrido
    orden[nro_orden] = padre;                   //el primero siempre es el vértice 1 (representado como 0 para usar de indice)
    dfs_recu(t,orden,padre,nro_orden);   //llamo a la recursiva
    return orden;
}

vector<int> heurAG(grafo g){
	vector<arista> t = kruskal(g);          //Hago el arbol, representado como una lista de adyacencia
	vector<int> orden = dfs(t);             //Recorro por dfs, para saber los ordenes
	vector<int> res(g.size(), 0);     // inicializo la resolución
	res[0] = g.size();				        // la cantidad de vértices es siempre n
	res[2] = 1;                             //el primer vertice siempre es "1"
	for(int i = 1; i<orden.size(); i++){
		res[i+2] = orden[i]+1;              // Agrego el vértice i de orden
		res[2]   = g[orden[i-1]][orden[i]]; //Agrego el peso de la arista (V_i-1,V_i)
	}
	return res;
}
