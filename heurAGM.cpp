#include "funciones.h"

using lista_adyacencia = vector<vector<int>>
using grafo = vector<vector<int>>

struct arista{ //representa una arista
	int inicio;
	int fin;
	int peso;
}

arista arista(int i, int f, int p){ //iniciador de una arista
	arista e;
	e.inicio = i;
	e.fin = f;
	e.peso = p
	return p;
}

class union_find{ //clase creada para krustal eficiente
public:
	vector<int> padre;
	vector<int> altura;

	union_find(vector<int> p, vector<int> a); //creador
	int find(int x);						  //encuentra el padre del subarbol de x
	void union(int x, int y);				  //cuelga el subarbol de x al de y
}

union_find::uniond_find(vector<int> p, vector<int> a):
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
	int p = this.padre[x]
	if(p != x){                          //si no es raíz
		this.padre[x] = this.find(p);	 //busco la raiz de su padre y la escribo como padre de x
		p = this.padre[x]
	}
	return p;
}

void union_find::union(int x, int y){
	x = this.find(x);						//busco amabs raices
	y = this.find(y);
	if(this.altura(x) < this.altura(y)){    // si el subarbol x es menor que el de y
		this.padre[x] = y;					//cuelgo el de x al de y
	}else{
		this.padre[y] = x;					//sino, al reves
	}
	if(this.altura[x] == this.altura[y]){	//si son de la misma alturam entones se colgó y a x, e x aumentó en 1 su altura
		this.altura[x] += 1;
	}
}

void merge_sort(vector<arista>& v,int v_1, int v_2){ //merge sort basado en el peso de la aristas
	if(v.size() == 1){
		return;
	}else{
		int split = v.size/2;
		merge_sort(v, v_1, split);
		merge_sort(v, split, v_2);
		i = 0;
		j = split;

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
	vector<int> res(g.size()*g.size(), 0);
	for(int i = 0; i<g.size(); i++){
		for(int j = 0; j<g.size();j++){
			arista e = arista(i,j,g[i][j]); //primero pongo todas las aristas en un solo vector
			res[i+j] = e;
		}
	}
	merge_sort(res,0,g.size()); //luego uso merge
	return res;
}

vector<aristas> kruskal(grafo g){ //creo un AGM con krustal
	int n = g.size();
	vector<aristas> res(n-1, arista(-1,-1,-1));
	union_find arboles = init(n);                          //arboles es el union_find que voy a usar
	vector<arista> aristas_ordenadas = sort_aristas(g);	   //hago el sort de las aristas
	int arista = 0;									   //empiezo en 1 pq ya tengo un subarbol con 1 arista

	for(int i = 0; i<aristas_ordenadas.size() && arista<n-1;i++){	   //meintras haya aristas, y no agregué todos los vértices
		arista e = aristas_ordenadas[i];
		int v = e.inicio;
		int w = e.fin;
		if(arboles.find(v) != arboles.find(w)){			   //si no tienen el mismo padre los meinbros de la arista
			arboles.union(v,w);							   //uno los subarboles
			res[arista] = e;							   //agrego la arsta e al arbol
			arista++;

		}
	}

	return res;
}

vector<int> heurAG(grafo g){
	vector<aristas> t = kruskal(g);   \\Hago el arbol, representado como una lista de adyacencia
	vector<int> orden = dfs(t);        \\Recorro por dfs, para saber los ordenes
	vector<int> res(g.size(), 0);      \\ inicializo la resolución
	res[0] = g.size();				   \\ la cantidad de vértices es siempre n
	res[2] = 1;                        \\el primer vertice siempre es "1" 
	for(int i = 1; i<orden.size(); i++){
		res[i+2] = orden[i]+1;           \\ Agrego el vértice i de orden
		res[2]   = G[orden[i-1]][orden[i]]; \\Agrego el peso de la arista (V_i-1,V_i) 
	}
	return res;
}

