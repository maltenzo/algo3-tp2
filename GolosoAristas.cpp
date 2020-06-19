#include <vector>
#include <list>

using namespace std;

vector<int> aristaMinimaFactible(list<vector<int>> &aristasRestantes){//quizas sortear aristas para sacar en O(1)
    int min = INT32_MAX;
    vector<int> res;
    for(vector<int> x : aristasRestantes){
        if(x[2] < min) {min = x[2]; res = x;}
    }
    return res;
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

vector<vector<int>> golosoArista(int V, vector<vector<int>> X){
    vector<vector<int>> aristasUsadas;
    list<vector<int>> aristasRestantes = vec2list(X); // igualar a X
    vector<int> estadoVertices(V, 0);
    vector<vector<int>> aristasH;

    for(int i = 0; i < V; i++){
        vector<int> e = aristaMinimaFactible(aristasRestantes);
        actualizarEstados(e, estadoVertices, aristasRestantes);
        aristasH.push_back(e);
    }
    return aristasH;
}
/* lo que use pa testear
int main() {
    int V = 4;
    vector<vector<int>> X = {{1,2,10},{1,3,15},{1,4,20},{2,3,35},{2,4,25},{3,4,30}};
    vector<vector<int>> camino = golosoArista(V,X);
    return 0;
}
*/