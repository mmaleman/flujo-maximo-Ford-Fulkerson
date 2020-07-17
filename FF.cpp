#include "ff.h"
#include "grafo.h"

/*
Implementación del algoritmo de Ford y Fulkerson para hallar el flujo máximo de una red.
Basado fuertemente en el pseudocódigo de Algo 3. Te amo Paula.
Autor: tinchino ahre quien era
*/


void insertarEnRedResidual(const grafo &G, int i, int j, redResidual &R) {
	if(G[i][j].first != -1) {
		// la arista está definida, so, meto uno o dos arcos segun corresponda:
		R[i][j] = G[i][j].second < G[i][j].first; // reviso si flujo < capacidad.
		R[j][i] = G[i][j].second > 0;
	}
}

void crearRedResidual(const grafo &G, redResidual &R) {
	int n = G.size();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			insertarEnRedResidual(G, i, j, R);
		}
	}
}

bool existeAristaDeSAScomplemento(redResidual &R, vector<bool> &S, int &v, int &w) {
	for(int i = 0; i < R.size(); i++) {
		for(int j = 0; j < R.size(); j++) {
			if(R[i][j] && S[i] && !S[j]) {
				v = i;
				w = j;
				return true; // pa cortar ahi de ruta apenas agarra una arista canchera (?)
			}
		}
	}

	return false;
}


camino caminoDeAumento(redResidual R, int s, int t) {
	// devuelve un camino de s a t. Si no hay camino, devuelve un vectorcito vacío. Y, viste cómo es, no pintó devolver un corte.
	int n = R.size();
	vector<bool> S(n, false); // esto representa el corte S en el cual vamos insertando los nodos.
	vector<int> padre(n, -1);
	int v;
	int w; // noditos para seguir la idea de Paula...
	camino res; // vector de int que se inicializa vacío.

	S[s] = true;

	while(!S[t] && existeAristaDeSAScomplemento(R, S, v, w)) { // esa función mete en v y w lo que esperas, (v->w) sería la arista en cuestión
		padre[w] = v;
		S[w] = true;
	}

	if(S[t]) {
		//reconstruir P entre s y t usando padres a partir de t... pero metiendo todo en res.
		int actual = t;
		while(actual != s) {
			res.push_back(actual);
			actual = padre[actual];
		}
		res.push_back(s);
		// tengo un camino de t a s... so, lo invierto y fin.
		reverse(res.begin(),res.end());
	}

	return res;
}

int deltaDeUnCamino(camino &P, grafo &G) {
	int res = 1;
	int deltaActual = 1;

	for(int i = 0; i < P.size() - 1; i++) {
		int v = P[i];
		int w = P[i+1];
		if(G[v][w].first != -1) {
			// el arco (v->w) está en G
			deltaActual = G[v][w].first - G[v][w].second; // c( (v->w) ) - f ( (v->w) )
		} else {
			deltaActual = G[w][v].second; // f ( (w->v) )
		}
		res = min(res, deltaActual);
	}

	return res;
}

int valorDeFlujo(grafo &G, int s) {
	// quiero contar todo el flujo que sale de la fuente.
	int n = G.size();
	int res = 0;

	for(int i = 0; i < n; i++) {
		if(G[s][i].first != -1){
				res += G[s][i].second;
			}
	}

	return res;
}


int fordFulkerson(grafo G, int s, int t) {
	int n = G.size();
	redResidual R(n, vector<bool>(n, false));
	int res = 0;
	camino P;

	crearRedResidual(G, R);	

	while( (P = caminoDeAumento(R, s, t)).size() != 0 ) { // el tamaño de P es 0 sii no hay camino viste, je. En tal caso, dejamos de iterar.
		// P = [s,v1,v2,...,vk,t]
		int deltaGlobal = deltaDeUnCamino(P, G);
		for(int i = 0; i < P.size() - 1; i++) {
			//veo si (v->w) arista de P está en X
			int v = P[i];
			int w = P[i+1];
			if(G[v][w].first != -1) {
				G[v][w] = make_pair(G[v][w].first, G[v][w].second + deltaGlobal);
			} else {
				G[w][v] = make_pair(G[w][v].first, G[w][v].second - deltaGlobal); // igual ver pq lo cambiaste a ultimo momento sin ver el pseudo...........
			}
		}
		crearRedResidual(G, R); // actualizo la red residual pa la proxima iteración.
	}

	return valorDeFlujo(G, s); // acá se calcula F.
}