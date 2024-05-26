#include <iostream>
#include <vector>
#include <list>
#include <algorithm>


/*
El código proporcionado resuelve un problema clásico conocido como "El problema del lobo, la cabra y la col" o

"El problema del agricultor". En este problema, un agricultor necesita cruzar un río con un lobo, una cabra

(en este caso, una oveja) y una col. Sin embargo, el bote del agricultor solo puede llevar a él y a un ítem adicional

a la vez. El desafío radica en que si el agricultor deja al lobo solo con la oveja, el lobo se comerá a la oveja.

Si deja a la oveja sola con la col, la oveja se comerá la col. Por lo tanto, el agricultor debe encontrar una forma de

cruzar el río con todos sus ítems intactos.

El código implementa una solución a este problema utilizando una búsqueda en profundidad (DFS) en un grafo que

representa todos los estados posibles del problema. Cada estado se representa como un nodo en el grafo, y cada transición de un estado a otro se representa como una arista en el grafo.

El objetivo del código es encontrar un camino en el grafo desde el estado inicial (donde el agricultor, el lobo,

la oveja y la col están todos en el lado izquierdo del río) hasta el estado final (donde todos están en el lado

derecho del río), sin pasar por ningún estado inválido (donde el lobo se come a la oveja o la oveja se come la col).

*/










// Clase Nodo que representa un estado del problema, donde cada lado del río se representa
// con un vector de 3 elementos, donde el primer elemento representa a la planta, el segundo a la oveja
// y el tercero al lobo, habiendo un 0 cuando ese lado está vacío y 1 cuando está ocupado.
// Además, se tiene un atributo lado que representa en qué lado del río está el
// bote, donde -1 representa el lado izquierdo y 1 el lado derecho.

struct Nodo{
    Nodo() = default;
    std::vector<int> ladoIzq;
    std::vector<int> ladoDer;
    int lado;
    Nodo(std::vector<int>* izq, std::vector<int>* der, int lado) {
        ladoIzq = *izq;
        ladoDer = *der;
        this->lado = lado;
    }
};


// Necesitamos definir que significa que dos estados sean iguales: son iguales sí y solo sí
// los vectores ladoIzq y ladoDer son iguales y el atributo lado es igual.
bool operator==(const Nodo& a, const Nodo& b) {
    for(int i = 0; i < a.ladoIzq.size(); i++){
        if(a.ladoIzq[i] != b.ladoIzq[i]){
            return false;
        }
    }
    for(int i = 0; i < a.ladoDer.size(); i++){
        if(a.ladoDer[i] != b.ladoDer[i]){
            return false;
        }
    }
    if(a.lado != b.lado){
        return false;
    }
    return true;
}


// Función que dado un estado actual y un lado, devuelve los estados posibles a los que se puede llegar
// desde el estado actual. La manera de obtener los estados es chequeando qué elementos hay del lado en el que
// estamos, para luego ver si podemos cruzarlos al otro lado. Si es posible cruzarlos, se crea un nuevo estado
// con los elementos cruzados y se agrega a la lista de estados posibles. Además, se agrega un estado en el que
// no cruzamos nada, es decir, cruzamos el bote solo.

std::vector<Nodo> estadosPosiblesDesde(Nodo* estadoActual, int lado){
    std::vector<Nodo> estadosPosibles;

    std::vector<int> ladoIzq = estadoActual->ladoIzq;
    std::vector<int> ladoDer = estadoActual->ladoDer;
    if(lado == -1){
        if(ladoIzq[0] == 1){
            ladoIzq[0] = 0;
            ladoDer[0] = 1;
            estadosPosibles.push_back(Nodo(&ladoIzq, &ladoDer, 1));
            ladoIzq[0] = 1;
            ladoDer[0] = 0;
        }
        if(ladoIzq[1] == 1){
            ladoIzq[1] = 0;
            ladoDer[1] = 1;
            estadosPosibles.push_back(Nodo(&ladoIzq, &ladoDer, 1));
            ladoIzq[1] = 1;
            ladoDer[1] = 0;
        }
        if(ladoIzq[2] == 1){
            ladoIzq[2] = 0;
            ladoDer[2] = 1;
            estadosPosibles.push_back(Nodo(&ladoIzq, &ladoDer,1));
            ladoIzq[2] = 1;
            ladoDer[2] = 0;
        }
    }
    else{
        if(ladoDer[0] == 1){
            ladoDer[0] = 0;
            ladoIzq[0] = 1;
            estadosPosibles.push_back(Nodo(&ladoIzq, &ladoDer, -1));
            ladoDer[0] = 1;
            ladoIzq[0] = 0;
        }
        if(ladoDer[1] == 1){
            ladoDer[1] = 0;
            ladoIzq[1] = 1;
            estadosPosibles.push_back(Nodo(&ladoIzq, &ladoDer,-1));
            ladoDer[1] = 1;
            ladoIzq[1] = 0;
        }
        if(ladoDer[2] == 1){
            ladoDer[2] = 0;
            ladoIzq[2] = 1;
            estadosPosibles.push_back(Nodo(&ladoIzq, &ladoDer,-1));
            ladoDer[2] = 1;
            ladoIzq[2] = 0;
        }
    }
    estadosPosibles.push_back(Nodo(&ladoIzq, &ladoDer, -1*lado));
    return estadosPosibles;
}

// Función que chequea si un estado es inválido, es decir, si la oveja se come a la planta o el lobo se come a la oveja
bool estadoInvalido(Nodo& estado){

    //La oveja y la planta están juntas en la izquierda y el bote está en el lado opuesto
    if(estado.ladoIzq[0] == 1 && estado.ladoIzq[1] == 1  && estado.lado == 1){
        return true;
    }

    //El lobo y la oveja están juntos en la izquierda y el bote está en el lado opuesto
    if(estado.ladoIzq[1] == 1 && estado.ladoIzq[2] == 1  && estado.lado == 1){
        return true;
    }

    //La oveja y la planta están juntas en la derecha y el bote está en el lado opuesto
    if(estado.ladoDer[0] == 1 && estado.ladoDer[1] == 1  && estado.lado == -1){
        return true;
    }

    //El lobo y la oveja están juntos en la derecha y el bote está en el lado opuesto
    if(estado.ladoDer[1] == 1 && estado.ladoDer[2] == 1  && estado.lado == -1){
        return true;
    }

    return false;
}

// Se crea un grafo que represente los estados posibles a los que se puede llegar desde un estado inicial
// dado. Para ello, se crea un nodo inicial y se obtienen los estados posibles a los que se puede llegar desde
// ese nodo. Luego, se crea un nodo por cada estado posible y se obtienen los estados posibles a los que se puede
// llegar desde esos nodos. Se repite este proceso hasta que no se puedan obtener estados posibles nuevos.
// EL grafo está representado con una lista de adyacencias.
void crearGrafo(std::vector<std::pair<Nodo, std::list<Nodo>>> &grafo, Nodo* nodo, std::vector<Nodo> estadosPosibles,
                int lado){

    //Si llegamos a un estado donde ya perdimos, no tiene sentido seguir generando nuevos estados desde ahí
    if(estadoInvalido(*nodo)){
        return;
    }

    //Buscamos al nodo actual en el grafo
    Nodo* nodoActual = &grafo[0].first;
    int i = 0;
    while(!((*nodoActual) == (*nodo))){
        i++;
        nodoActual = &grafo[i].first;
    }

    //Chequeamos si los estados posibles que nos pasan ya están en la lista de adyacencias de nuestro nodo
    for(auto estado : estadosPosibles) {
        // Verifica si el estado ya está en la lista de adyacencias antes de agregarlo
        if(std::find(grafo[i].second.begin(), grafo[i].second.end(), estado) != grafo[i].second.end()) {
            continue;
        }
        grafo[i].second.push_back(estado);
        //Chequeamos si el estado adyacente ya está en el grafo, y si no, lo agregamos
        bool existe = false;
        bool huboUnCambio = false;

        for (std::pair<Nodo, std::list<Nodo>> par: grafo) {
            if (par.first == estado) {
                existe = true;
                break;
            }

        }
        if (!existe) {
            grafo.push_back(std::make_pair(estado, std::list<Nodo>()));
            //Con esta variable guardamos la información de si hubo un cambio en el grafo,
            // para saber si debemos seguir generando nuevos estados
            huboUnCambio = true;
        }
        if(huboUnCambio){
            //Dado que hubo un cambio en el grafo, tomamos el último nodo agregado y generamos los estados posibles
            // a los que se puede llegar desde ese nodo.
            Nodo* nodoNuevo = &grafo[grafo.size()-1].first;
            std::vector<Nodo> estadosPosiblesA = estadosPosiblesDesde(nodoNuevo, nodoNuevo->lado);
            crearGrafo(grafo, nodoNuevo, estadosPosiblesA, nodoNuevo->lado);
        }

    }
}

// Función que imprime la acción realizada para llegar de un estado a otro
void imprimirAccionRealizada(Nodo& estadoInicial, Nodo& estadoFinal){
    if(estadoInicial.ladoIzq[0] != estadoFinal.ladoIzq[0]) {
        if (estadoInicial.ladoIzq[0] == 1) {
            std::cout << "Cruzamos a la planta hacia la derecha" << std::endl;
        } else {
            std::cout << "Cruzamos a la planta hacia la izquierda" << std::endl;
        }
        return;
    }
    if(estadoInicial.ladoIzq[1] != estadoFinal.ladoIzq[1]) {
        if (estadoInicial.ladoIzq[1] == 1) {
            std::cout << "Cruzamos a la oveja hacia la derecha" << std::endl;
        } else {
            std::cout << "Cruzamos a la oveja hacia la izquierda" << std::endl;
        }
        return;
    }
    if(estadoInicial.ladoIzq[2] != estadoFinal.ladoIzq[2]) {
        if (estadoInicial.ladoIzq[2] == 1) {
            std::cout << "Cruzamos al lobo hacia la derecha" << std::endl;
        } else {
            std::cout << "Cruzamos al lobo hacia la izquierda" << std::endl;
        }
        return;
    }

        std::cout << "Volvemos" << std::endl;


}


bool encontrado = false;


// Básicamente estamos aplicando el algoritmo de búsqueda en profundidad, donde vamos recorriendo el grafo
// hasta encontrar el estado final. Si encontramos el estado final, imprimimos el camino que nos llevó a ese estado.
// Si llegamos a un estado inválido, volvemos al estado anterior.
void buscarCombinacion(std::vector<std::pair<Nodo, std::list<Nodo>>> &grafo,
                       Nodo* estadoInicial, Nodo* estadoFinal, std::vector<Nodo>& camino) {
    if(encontrado || estadoInvalido(*estadoInicial)){
        camino.pop_back();
        return;
    }
    if((*estadoInicial) == (*estadoFinal)){
        std::cout << "Camino encontrado" << std::endl;
        for(int i = 0; i < camino.size()-1; i++){
            imprimirAccionRealizada(camino[i], camino[i+1]);
        }
        encontrado = true;
        return;
    }

    int i = 0;
    while(!((grafo[i].first) == (*estadoInicial))){
        i++;
    }
    for(auto nodo : grafo[i].second){
        if(std::find(camino.begin(), camino.end(), nodo) != camino.end()){
            continue;
        }
        camino.push_back(nodo);
        buscarCombinacion(grafo, &nodo, estadoFinal, camino);

    }
    if(!encontrado && camino.size() > 0) {
        camino.pop_back();
    }

}


int main() {
    std::vector<std::pair<Nodo, std::list<Nodo>>> grafo;
    std::vector<int> ladoIzqInicial = {1,1,1};
    std::vector<int> ladoDerInicial = {0,0,0};
    Nodo estadoInicial = Nodo(&ladoIzqInicial, &ladoDerInicial, -1);
    grafo.push_back(std::make_pair(estadoInicial, std::list<Nodo>()));
    std::vector<Nodo> estadosPosibles = estadosPosiblesDesde(&estadoInicial, -1);
    crearGrafo(grafo, &estadoInicial, estadosPosibles, -1);
    std::vector<int> ladoIzqFinal = {0,0,0};
    std::vector<int> ladoDerFinal = {1,1,1};
    Nodo estadoFinal = Nodo(&ladoIzqFinal, &ladoDerFinal, 1);
    std::vector<Nodo> camino;
    camino.push_back(estadoInicial);
    buscarCombinacion(grafo, &estadoInicial, &estadoFinal, camino);
    return 0;

}
