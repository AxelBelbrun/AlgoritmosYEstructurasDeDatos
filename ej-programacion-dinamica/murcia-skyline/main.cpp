#include <iostream>
#include <vector>
struct Edificio {
    int id;
    int altura = 0;
    int ancho = 0;
    Edificio() {
        ancho = 0;
        altura = 0;
    };
};


int MurciaSkylineDP(std::vector<Edificio> &edificios, int indiceActual,
                                   int ultimoIndiceSubsecuenciaCreciente, int ultimoIndiceSubsecuenciaDecreciente,
                                   std::vector<std::vector<int>>&M, bool creciente) {
    if(indiceActual == edificios.size()){
        return  0;
    }
    if(creciente) {
        if (M[indiceActual][ultimoIndiceSubsecuenciaCreciente + 1] != -1) {
            return M[indiceActual][ultimoIndiceSubsecuenciaCreciente + 1];
        }
        int secSin = MurciaSkylineDP(edificios, indiceActual + 1, ultimoIndiceSubsecuenciaCreciente,
                                     ultimoIndiceSubsecuenciaDecreciente, M, creciente);
        int secCon = 0;
        if (ultimoIndiceSubsecuenciaCreciente == -1 ||
            edificios[indiceActual].altura > edificios[ultimoIndiceSubsecuenciaCreciente].altura) {
            secCon = edificios[indiceActual].ancho +
                     MurciaSkylineDP(edificios, indiceActual + 1, indiceActual, ultimoIndiceSubsecuenciaDecreciente, M, creciente);
        }
        M[indiceActual][ultimoIndiceSubsecuenciaCreciente + 1] = std::max(secSin, secCon);
        return M[indiceActual][ultimoIndiceSubsecuenciaCreciente + 1];

    }
    else {
        if (M[indiceActual][ultimoIndiceSubsecuenciaDecreciente + 1] != -1) {
            return M[indiceActual][ultimoIndiceSubsecuenciaDecreciente + 1];
        }

        int secSin = MurciaSkylineDP(edificios, indiceActual + 1, ultimoIndiceSubsecuenciaCreciente,
                                        ultimoIndiceSubsecuenciaDecreciente, M, creciente);
        int secCon = 0;
        if (ultimoIndiceSubsecuenciaDecreciente == -1 ||
            edificios[indiceActual].altura < edificios[ultimoIndiceSubsecuenciaDecreciente].altura) {
            secCon = edificios[indiceActual].ancho +
                        MurciaSkylineDP(edificios, indiceActual + 1, ultimoIndiceSubsecuenciaCreciente, indiceActual,
                                        M, creciente);
        }
        M[indiceActual][ultimoIndiceSubsecuenciaDecreciente + 1] = std::max(secSin, secCon);
        return M[indiceActual][ultimoIndiceSubsecuenciaDecreciente + 1];

    }





};



int main() {
    int cantidadDeCasos;
    std::cin >> cantidadDeCasos;
    for(int i = 0; i < cantidadDeCasos; i++){
        int cantidadDeEdificios;
        std::cin >> cantidadDeEdificios;
        std::vector<Edificio> edificios;
        for(int j = 0; j < cantidadDeEdificios; j++){
            Edificio x;
            std::cin >> x.altura;
            x.id = j;
            edificios.push_back(x);
        }
        for(int t = 0; t < cantidadDeEdificios; t++){
            std::cin >> edificios[t].ancho;
        }

        std::vector<std::vector<int>> M(cantidadDeEdificios + 1, std::vector<int>(cantidadDeEdificios + 1, -1));
        int lengthCreciente = MurciaSkylineDP(edificios, 0, -1, -1, M, true);
        std::vector<std::vector<int>> N(cantidadDeEdificios + 1, std::vector<int>(cantidadDeEdificios + 1, -1));

        int lengthDecreciente = MurciaSkylineDP(edificios, 0, -1, -1, N, false);
        std::cout << "Case " << i+1 << ". ";
        if(lengthCreciente >= lengthDecreciente){
            std::cout << "Increasing (" << lengthCreciente << ")" << ". " << "Decreasing (" << lengthDecreciente << ")" << ".";
        } else {
            std::cout << "Decreasing (" << lengthDecreciente << ")" << ". " << "Increasing (" << lengthCreciente << ")" << ".";
        }
        std::cout << std::endl;

    }
}
