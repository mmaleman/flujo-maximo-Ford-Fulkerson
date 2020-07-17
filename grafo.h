#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int capacidad;
typedef int flujo;

typedef vector<vector<pair<capacidad, flujo>>> grafo;
typedef vector<vector<bool>> redResidual;
typedef vector<int> camino;

grafo leerGrafo(int &s, int &t);
void imprimirGrafo(grafo &g);

#endif