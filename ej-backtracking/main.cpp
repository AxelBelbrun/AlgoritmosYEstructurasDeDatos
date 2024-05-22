#include <iostream>
#include <vector>
#include <algorithm>
struct Jugador {
    std::string nombre;
    int ataque;
    int defensa;
};

std::vector<Jugador> atacantesGanadores;
std::vector<Jugador> defensoresGanadores;

void mejoresAtacantesBT(std::vector<Jugador> &jugadores, int k, std::vector<Jugador> &atacantes,
                        std::vector<Jugador> &defensores) {
                        
    //Agrego el jugador en la posición k como atacante y como defensor, siempre y cuando los conjuntos no estén llenos.
    if (atacantes.size() < 5) {
    
        //Como no quiero modificar los conjuntos originales, creo una copia y luego agrego el jugador a esa copia.. ***
        std::vector<Jugador> atacantesAux = atacantes;
        atacantesAux.push_back(jugadores[k]);
        mejoresAtacantesBT(jugadores, k + 1, atacantesAux, defensores);
    }
    if (defensores.size() < 5) {
        // *** la misma idea en este caso
        std::vector<Jugador> defensoresAux = defensores;
        defensoresAux.push_back(jugadores[k]);
        mejoresAtacantesBT(jugadores, k + 1, atacantes, defensoresAux);
    }
    
    //Una vez que se llenaron ambos grupos:
    if (atacantes.size() == 5 && defensores.size() == 5) {
        // Verificar si es mejor que el mejor hasta ahora
        int atacantesGanadoresSuma = 0;
        int atacantesActualesSuma = 0;
        for (Jugador &j: atacantesGanadores) {
            atacantesGanadoresSuma += j.ataque;
        }
        for (Jugador &j: atacantes) {
            atacantesActualesSuma += j.ataque;
        }
        
        //Si mejoramos los puntos de ataque, tenemos nuevo conjunto ganador y entonces los guardamos
        if (atacantesActualesSuma > atacantesGanadoresSuma) {
            atacantesGanadores = atacantes;
            defensoresGanadores = defensores;
        }
        
        //Si empatan en ataque, chequeamos los puntos de defensa: 
        else if (atacantesActualesSuma == atacantesGanadoresSuma) {
            int defensoresGanadoresSuma = 0;
            int defensoresActualesSuma = 0;
            for (Jugador &j: defensoresGanadores) {
                defensoresGanadoresSuma += j.defensa;
            }
            for (Jugador &j: defensores) {
                defensoresActualesSuma += j.defensa;
            }
            
            //Si mejoramos los puntos de defensa, tenemos nuevo conjunto ganador y entonces los guardamos
            if (defensoresActualesSuma > defensoresGanadoresSuma) {
                atacantesGanadores = atacantes;
                defensoresGanadores = defensores;
            }
            //Si empatan en defensa también, hay que desempatar por orden lexicográfico. 
            else if (defensoresActualesSuma == defensoresGanadoresSuma) {
            
                //Creo los vectores que almacenarán solo los nombres de los jugadores, ignorando los puntos de ataque y defensa. 
                // Esto es para poder usar una función nativa de C++ (lexicographical_compare) que compara dos vectores y nos indica
                // cuál viene primero en orden lexicográfico.
                std::vector<std::string> atacantesNombres(5);
                std::vector<std::string> atacantesGanadoresNombres(5);
                for (Jugador &j: atacantes) {
                    atacantesNombres.push_back(j.nombre);
                }
                for (Jugador &j: atacantesGanadores) {
                    atacantesGanadoresNombres.push_back(j.nombre);
                }
                
                //Si la función lexicographical_compare devuelve true, es porque los atacantes actuales vienen primero en orden lexico-
                //gráfico que los historicamente mejores, entonces tenemos nuevo conjunto ganador y actualizamos:
                if(std::lexicographical_compare(atacantesNombres.begin(), atacantesNombres.end(),
                                             atacantesGanadoresNombres.begin(), atacantesGanadoresNombres.end())){
                    atacantesGanadores = atacantes;
                    defensoresGanadores = defensores;
                }
                //Si devuelve false, entonces los historicamente mejores vienen antes en orden lexicográfico, así que no hay
                // nada que actualizar.
            }
        }
    }
}

int main() {
    int cantidadDeCasos;
    std::cin >> cantidadDeCasos;
    for(int i = 0; i < cantidadDeCasos; i++) {
        std::vector<Jugador> jugadores;
        for(int j = 0; j < 10; j++){
            Jugador jugador;
            std::cin >> jugador.nombre >> jugador.ataque >> jugador.defensa;
            jugadores.push_back(jugador);
        }
        std::vector<Jugador> atacantes;
        std::vector<Jugador> defensores;
        atacantesGanadores.clear();
        defensoresGanadores.clear();
        mejoresAtacantesBT(jugadores, 0, atacantes, defensores);
        std::sort(atacantesGanadores.begin(), atacantesGanadores.end(), [](const Jugador &a, const Jugador &b) {
            return a.nombre < b.nombre;
        });
        std::sort(defensoresGanadores.begin(), defensoresGanadores.end(), [](const Jugador &a, const Jugador &b) {
            return a.nombre < b.nombre;
        });
        std:: cout << "Case " << i+1 << ":" << std::endl;
        std:: cout << "(" << atacantesGanadores.at(0).nombre << ", " << atacantesGanadores.at(1).nombre
                   << ", " << atacantesGanadores.at(2).nombre << ", " << atacantesGanadores.at(3).nombre
                   << ", " << atacantesGanadores.at(4).nombre << ")" << std::endl;
        std:: cout << "(" << defensoresGanadores.at(0).nombre << ", " << defensoresGanadores.at(1).nombre
                   << ", " << defensoresGanadores.at(2).nombre << ", " << defensoresGanadores.at(3).nombre
                   << ", " << defensoresGanadores.at(4).nombre << ")" << std::endl;
        atacantesGanadores.clear();
        defensoresGanadores.clear();


    }


}
