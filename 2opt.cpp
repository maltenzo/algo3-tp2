
int costo(vector<int> ciclo){
	int res = 0;
	for(int i = 0; i < ciclo.size()-1; i++){
		res += matriz_adyacencia[i][i+1];
	}
	return res;
}

void swap(vector<int> &c, int i, int j){
	int a = c[i];
	c[i] = c[j]; // c[i] = b = c[j]
	c[j] = a;
}

// Grafo G, tengo matriz de adyacencia
// Esta version inicial solo devuelve 1 vecino 2opt, claramente desaprovechamos
// mucho computo y podriamos usar el top 10 o ir guardando mas de uno.


vector<int> localSearch2opt(vector<int> ciclo){ // recibe el ciclo generado por AGM o alguna otra heuristica
	
	// Pre, el ciclo es de longitud n = matriz_adyacencia.size()

	vector<int> candidato = ciclo;
	int costoInicial = costo();
	int mejoraDeCosto;
	int n = ciclo.size();

	for(int it = 0; it < OPT_ITERACIONES; it++){ 
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				// Para cada par de vertices, me fijo el swappeo

				int arista_ab = matriz_adyacencia[candidato[i]][candidato[(i+1) % n]]; // Arista A--B
				int arista_cd = matriz_adyacencia[candidato[j]][candidato[(j+1) % n]]; // Arista C--D
				candidato = swap(candidato, i, j);

				int arista_ac = matriz_adyacencia[candidato[i]][candidato[(i+1) % n]];
				int arista_bd = matriz_adyacencia[candidato[j]][candidato[(j+1) % n]];
				// Si intercambiando A--B por A--C, y C--D por B--D mejora:

				// Esto es basicamente para ahorrarse hacer "costo(candidato)"
				mejoraDeCosto = costoInicial -  arista_ab - arista_cd + arista_ac + arista_bd;
				
				if(costoInicial > mejoraDeCosto){
					ciclo = candidato;
				}
			}
		}
	}
	return candidato;
}