#include "grafo.h"

grafo leerGrafo(int &s, int &t) {
    int n, m;
    cin >> n >> m >> s >> t;
    grafo G(n, vector<pair<capacidad, flujo>>(n, make_pair(-1,-1))); // G[i][j] == (-1,-1) sii la arista está indefinida

    for(int i = 0; i < m; i++) {
        int v, w, capacidad;
        cin >> v >> w >> capacidad;
		G[v][w] = make_pair(capacidad, 0);
    }
    
    return G;
}

void imprimirGrafo(grafo &g) {
	cout << " ";
	for(int i = 0; i< g.size(); i++) {
		cout << "   " << i << "  ";
	}
	cout << "\n";
	cout << " ┌"; // alt + 218
	for(int i = 0; i< (g.size()-1)*4; i++) {
		cout << "──"; // alt + 196
	}
	cout << "\n";

    for (int i = 0; i < g.size(); i++) {
        cout << i << "│"; // alt + 179
        for (int j = 0; j < g[i].size(); j++) {
        	if(g[i][j].first == -1) {
        		cout << "(-,-) ";
        	} else {
            	cout << "(" << g[i][j].first << "," << g[i][j].second << ") ";
        	}
        }
        cout << "\n";
    }
}
