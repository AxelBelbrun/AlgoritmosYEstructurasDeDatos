#include <iostream>
#include <vector>

void swapLetters(std::string str1, std::string str2, int tamanio) {
    int contador = 0;
    std::vector<std::pair<int, int>> swapeos;
    for (int i = 0; i < tamanio; i++) {
        if (str1[i] != str2[i]) {
            bool encontrado = false;
            for(int j = i + 1; j < tamanio; j++){
                if(str1[i] == str1[j] && str2[i] == str2[j]){
                    std::pair <int, int> par = std::make_pair(i, j);
                    swapeos.push_back(par);
                    std::swap(str1[i], str2[j]);
                    contador++;
                    encontrado = true;
                    break;
                }
            }
            if(!encontrado){
                std::swap(str1[i], str2[i]);
                std::pair <int, int> par = std::make_pair(i, i);
                swapeos.push_back(par);
                contador++;
                for(int j = i + 1; j < tamanio; j++){
                    if(str1[i] == str1[j] && str2[i] == str2[j]){
                        std::pair <int, int> par = std::make_pair(i, j);
                        swapeos.push_back(par);
                        std::swap(str1[i], str2[j]);
                        contador++;
                        encontrado = true;
                        break;
                    }
                }
                if(!encontrado){
                    std::cout << -1;
                    return;
                }
            }
        }
    }
    std:: cout << contador << std:: endl;
    for(std:: pair x: swapeos){
        std:: cout << x.first + 1 << " " << x.second + 1 << std::endl;
    }
}


int main() {
    int tamanio;
    std::cin >> tamanio;
    std::string str1, str2;
    std::cin >> str1;
    std::cin >> str2;
    swapLetters(str1, str2, tamanio);

}
