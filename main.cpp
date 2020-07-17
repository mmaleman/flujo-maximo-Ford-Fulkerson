#include "ff.h"
#include "grafo.h"

int main() {
    cout << "Hola rey, me rompo un flujo máximo. Cebate. \n";

    int s, t;
    grafo G = leerGrafo(s, t);

    cout << "\nTu grafito lindo es: \n";
    imprimirGrafo(G);
    cout << "\nY su flujo máximo vale: " << fordFulkerson(G, s, t) << endl;

    return 0;
}

    /*
    Si te da paja hacer toda la garompa de input, hardcodeá tu grafo asi:

    grafo g = {{make_pair(-1,-1), make_pair(1,-0), make_pair(2,0), make_pair(-1,-1)},
               {make_pair(-1,-1), make_pair(-1,-1), make_pair(-1,-1), make_pair(3,0)},
               {make_pair(-1,-1), make_pair(4,0), make_pair(-1,-1), make_pair(-1,-1)},
               {make_pair(-1,-1), make_pair(-1,-1), make_pair(-1,-1), make_pair(-1,-1)}};


    Con la garompa de acá arriba, quedaría este grafo:

        1          3
     .------>(1)------.
     |        ^       |    el flujo máximo valdría 3
     |  2     |4      v
    (0)----->(2)     (3)

    int s = 0;  acá, la fuente.
    int t = 3;  acá, el sumidero.
    */