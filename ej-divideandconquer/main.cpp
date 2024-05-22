#include <iostream>
#include <string>

bool comparadorDeStrings(std::string &a, std::string &b) {

    if(a.size() == 1 || a.size() % 2 != 0){
        return a == b;
    }
    else{
        std::string a1 = a.substr(0, a.size()/2);
        std::string a2 = a.substr(a.size()/2, a.size());
        std::string b1 = b.substr(0, b.size()/2);
        std::string b2 = b.substr(b.size()/2, b.size());
        return (comparadorDeStrings(a1, b2) && comparadorDeStrings(a2, b1)) || (comparadorDeStrings(a1, b1) && comparadorDeStrings(a2, b2))
        ;

    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::string a, b;
    std::cin >> a >> b;
    if(comparadorDeStrings(a, b)){
        std::cout << "YES";
    }
    else{
        std::cout << "NO";
    }

}
