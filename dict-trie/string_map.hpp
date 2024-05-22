template <typename T>
string_map<T>::string_map() : _size(0), claves({}){
    raiz = nullptr;

}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    /* Inserto en el diccionario nuevo cada una de las claves
     * del dicionario a copiar */
    for(string t: d.claves){
        pair<string, T> c = make_pair(t,d.at(t));
        this->insert(c);

    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
set<string> res = this->claves;
for(string s: res){
    this->erase(s);
}
delete raiz;
}

template <typename T>
void string_map<T>:: insert(const pair<string, T>& c){
    Nodo* actual = raiz;
    Nodo* padre;
    int i = 0;
    string clave = c.first;
    T* def = new T (c.second);
    while((i < clave.size())){
        /* Si la raíz es nula (por defecto en el constructor es null), creo un nuevo nodo y apunto la raíz ahí. */
        if (raiz == nullptr){
            raiz = new Nodo();
            padre = raiz;
            /* Me muevo al nodo siguiente que representa a mi letra actual */
            actual = raiz->siguientes[int(clave[i])];
            i++;
        }
        /* En caso de que esté parado en un nodo nulo, vuelvo al padre, y en el nodo hijo que
         * representaría a mi actual, creo un nuevo nodo */
        else if (actual == nullptr){

           padre->siguientes[int(clave[i-1])] = new Nodo();

           actual = padre->siguientes[int(clave[i-1])];
       }
        else{
            padre = actual;
            actual = actual->siguientes[int(clave[i])];
            i++;
        }
    }
    /* Ya llegué al nodo que representa a mi palabra. Si es null, vuelvo al padre,
     * creo un nodo nuevo en el hijo que representa la última letra y luego le asigno el
     * significado */
    if(actual == nullptr) {

        padre->siguientes[int(clave[i - 1])] = new Nodo();
        padre->siguientes[int(clave[i - 1])]->definicion = def;
        _size++;
    }
    /* Si era un nodo no null, simplemente actualizo la definición */
    else {
        /* Si no había nada definido es porque estoy ingresando una nueva
         * clave */
        if (actual->definicion == nullptr){
            delete actual->definicion;
            actual->definicion = def;
            _size++;
        }
        /* Si no, simplemente estoy modificandp el significado de una clave ya existente */
        else{
            delete actual->definicion;
            actual->definicion = def;
        }
    }
    /* Me guardo la nueva clave en mi conjunto de claves */
    claves.insert(clave);
}



template <typename T>
int string_map<T>::count(const string& clave) const{
  Nodo* actual = raiz;
  /* Recorro el trie */
  for(char c : clave){
      /* Si el nodo es nulo es porque en algún momento el camino deja de existir,
       * entonces esa clave no pertenece al diccionario */
      if (actual == nullptr){
          return 0;
      }
      else {
          actual = actual->siguientes[int(c)];
      }
  }
  /*Si salió del for es porque llegó al final del camino.
   * Hay varios casos: */
  /* Si el nodo final es nulo, es porque no existe esa clave: */
  if(actual == nullptr){
      return 0;
  }
  /* Si el nodo existe pero no tiene definición, la clave tampoco
   * existe */
  else if ((actual->definicion) == nullptr){
      return 0;
  }
  /* De otro modo, la clave existe: */
  else {
      return 1;
  }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = raiz;
    /* Recorro el trie y devuelvo el significado */
    for(char elem: clave){
        actual = actual->siguientes[int(elem)];
    }
    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = raiz;
    for(char elem: clave){
        actual = actual->siguientes[int(elem)];
    }

   return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = raiz;
    Nodo* padre;
    int indice = -1;

    /*Recorro una vez el árbol para identificar el nodo que representa la palabra y también
     * para saber cuál es el último nodo no eliminable */
    int j = 0;
    while (j< clave.size()){
        /*Si no es eliminable, es candidato a ser el último nodo
         * no eliminable */
        if(!(actual->esNodoEliminable(*actual))){
            indice = j;

            padre = actual;
            actual = actual->siguientes[int(clave[j])];
            j++;

        }
        /* Si es eliminable, sigo avanzando */
        else {
            padre = actual;
            actual = actual->siguientes[int(clave[j])];

            j++;
        }
    }
    /* Recorrí el trie "anotando" cuál es el último nodo no eliminable
     * Ahora vuelvo a recorrer y elimino los nodos que sean necesarios (puede que no se borre ninguno)*/
    int i = 0;
    /* Actual es el nodo que representa a la palabra total, entonces me fijo si es eliminable chequeando que no tenga hijos. */
    if (actual->esNodoFinalEliminable(*actual)){
        actual = raiz;
        /* Si era eliminable, y mi indice de último nodo no eliminable se quedó en -1, significa que todos los nodos que recorrí
         * eran eliminables, por lo tanto, borro todos*/
        if (indice == -1){
            for(char c: clave){
                Nodo* temp = actual->siguientes[int(c)];
                delete actual->definicion;
                delete actual;
                actual = temp;
            }
            /* Dejo la raíz como null, ya que se borró todo*/
            raiz = nullptr;
        }
        /* Si mi indice se movió, significa que algunos nodos serán eliminados y otros no. Así que me muevo hasta pasarme del
         * último no eliminable, y a partir de ahí, elimino */
        else {
            for (char c: clave) {
                if (i <= indice) {
                    padre = actual;
                    actual = actual->siguientes[int(c)];
                    i++;
                } else {
                    /* Este if hace que el último nodo no eliminable apunte, ahora, en el hijo que representa a la letra
                     * correspondiente, a nullptr */
                    if (i == indice + 1) {
                        Nodo* temp = actual->siguientes[int(c)];
                        delete actual->definicion;
                        delete actual;
                        actual = temp;
                        padre->siguientes[int(clave[i-1])] = nullptr;
                        i++;
                    /* Una vez hecho eso, simplemente elimino todos los nodos necesarios*/
                    } else {
                        Nodo* temp = actual->siguientes[int(c)];
                        delete actual->definicion;
                        delete actual;

                        actual = temp;
                        i++;
                    }
                }
            }
        }
        /* Al final, estoy nuevamente en el nodo que representaba a la palabra completa, lo elimino también*/
        /* Si el índice de último nodo no eliminable subió hasta el final significa que solo ese nodo se elimina
         * y hay que hacer que su padre apunte a null, caso no contemplado arriba! Lo contemplo acá: */
        if ((i == indice + 1)and(raiz!=nullptr)){
            delete actual->definicion;
            delete actual;
            padre->siguientes[int(clave[i-1])] = nullptr;

        }
        else{
        delete actual->definicion;
        delete actual;
        }
    }
    /* Si el último nodo no era eliminable, simplemente le borro el significado que tenía y dejo a este último como nullptr*/
    else {
        delete padre->siguientes[int(clave[(clave.size()-1)])]->definicion ;
        padre->siguientes[int(clave[(clave.size()-1)])]->definicion = nullptr;

    }

    claves.erase(clave);
    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    if (_size == 0){
        return true;
    }

        return false;

}