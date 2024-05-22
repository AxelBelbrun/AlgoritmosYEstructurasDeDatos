#include <iostream>
#include <vector>
#include <queue>

typedef long long U64;

U64 calcularCostoMinimo(std::vector<U64> &ofertaYDemanda){
    U64 trabajoMinimo = 0;
    std::priority_queue <U64, std::vector<U64>, std::greater<U64>> vecinosQueVenden;
    std::priority_queue <U64, std::vector<U64>, std::greater<U64>> vecinosQueCompran;
    for(U64 j = 0; j < ofertaYDemanda.size(); j++){
        if(ofertaYDemanda[j] > 0){
            vecinosQueCompran.push(j);
        }
        else if (ofertaYDemanda[j] < 0){
            vecinosQueVenden.push(j);
        }
    }

    for(U64 i = 0; i < ofertaYDemanda.size(); i++){
        while(ofertaYDemanda[i] != 0){
            if(ofertaYDemanda[i] > 0) {
                U64 casaVendedorMasCercano = vecinosQueVenden.top();
                U64 cantVinosEnVenta = -ofertaYDemanda[casaVendedorMasCercano];
                if (cantVinosEnVenta > ofertaYDemanda[i]) {
                    U64 vinosRequeridos = ofertaYDemanda[i];
                    ofertaYDemanda[casaVendedorMasCercano] += vinosRequeridos;
                    trabajoMinimo += (casaVendedorMasCercano - i) * vinosRequeridos;
                    ofertaYDemanda[i] = 0;
                    vecinosQueCompran.pop();
                }
                else if(cantVinosEnVenta == ofertaYDemanda[i]){
                    ofertaYDemanda[casaVendedorMasCercano] = 0;
                    ofertaYDemanda[i] = 0;
                    trabajoMinimo += (casaVendedorMasCercano - i) * cantVinosEnVenta;
                    vecinosQueVenden.pop();
                    vecinosQueCompran.pop();
                }
                else {
                    ofertaYDemanda[i] -= cantVinosEnVenta;
                    trabajoMinimo += (casaVendedorMasCercano - i) * cantVinosEnVenta;
                    ofertaYDemanda[casaVendedorMasCercano] = 0;
                    vecinosQueVenden.pop();
                }
            }
            else{
               U64 casaClienteMasCercano = vecinosQueCompran.top();
                U64 cantVinosEnDemanda = ofertaYDemanda[casaClienteMasCercano];
                if (cantVinosEnDemanda >  -ofertaYDemanda[i]) {
                    U64 vinosDisponibles = ofertaYDemanda[i];
                    ofertaYDemanda[casaClienteMasCercano] += vinosDisponibles;
                    trabajoMinimo += (casaClienteMasCercano - i) * -vinosDisponibles;
                    ofertaYDemanda[i] = 0;
                    vecinosQueVenden.pop();
                }
                else if(cantVinosEnDemanda == ofertaYDemanda[i]){
                    ofertaYDemanda[i] = 0;
                    ofertaYDemanda[casaClienteMasCercano] = 0;
                    trabajoMinimo += (casaClienteMasCercano - i) * cantVinosEnDemanda;
                    vecinosQueCompran.pop();
                    vecinosQueVenden.pop();
                }
                else {
                    ofertaYDemanda[i] += cantVinosEnDemanda;
                    trabajoMinimo += (casaClienteMasCercano - i) * cantVinosEnDemanda;
                    ofertaYDemanda[casaClienteMasCercano] = 0;
                    vecinosQueCompran.pop();
                }
            }

        }
    }
    return trabajoMinimo;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    U64 cantidadDeHabitantes;
    std::cin >> cantidadDeHabitantes;
    while(cantidadDeHabitantes != 0){
        std::vector<U64> ofertaYDemanda(cantidadDeHabitantes);
        for(U64 i = 0; i < cantidadDeHabitantes; i++){
            std::cin >> ofertaYDemanda[i];
        }
        std::cout << calcularCostoMinimo(ofertaYDemanda) << "\n";
        std::cin >> cantidadDeHabitantes;
    }
}
