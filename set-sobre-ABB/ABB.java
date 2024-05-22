package aed;

import java.util.*;

// Todos los tipos de datos "Comparables" tienen el método compareTo()
// elem1.compareTo(elem2) devuelve un entero. Si es mayor a 0, entonces elem1 > elem2
public class ABB<T extends Comparable<T>> implements Conjunto<T> {
    // Agregar atributos privados del Conjunto

    private class Nodo {
        Nodo(T elem){
            izq = null;
            der = null;
            padre = null;
            valor = elem;
        }
        Nodo izq;
        Nodo der;
        Nodo padre;
        T valor;
    }

    private Nodo _raiz;
    private int _cardinal;
    public ABB() {
        _raiz = null;
        _cardinal = 0;
    }

    public int cardinal() {
        return _cardinal;
    }

    public T minimo(){
        Nodo actual = _raiz;
        
        if (_raiz.izq != null) {
            while (actual.izq != null) {
                
                actual = actual.izq;
            }
            return actual.valor;
        }
        else {
            return _raiz.valor;
        }
    }

    public T maximo(){
        Nodo actual = _raiz;
        
        while (actual.der != null) {
            
            actual = actual.der;
        }
    return actual.valor;
    }

    public void insertar(T elem){
         // Si ya está, no hago nada
    if (pertenece(elem)) {
        return;
    }

    //Si no hay nada en el conjunto, creo un nuevo nodo que será la raíz
    else if (_cardinal == 0) {
        _raiz = new Nodo(elem);
        _cardinal++;

    }
    else {
        Nodo actual = _raiz;
        Nodo anterior = null;

        /* Busco el lugar donde estaría el nodo si perteneciera */
        while (actual != null) {
            if (elem.compareTo(actual.valor) < 0) {
                anterior = actual;
                actual = actual.izq;
            } else {
                anterior = actual;
                actual = actual.der;
            }
        }

        /* Chequeo si el último "movimiento" fue a izq o der, e inserto
          ahí el nuevo nodo */
        Nodo nuevo = new Nodo(elem);
        if (elem.compareTo(anterior.valor) < 0) {
            anterior.izq = nuevo;
            nuevo.padre = anterior;
        } else {
            anterior.der = nuevo;
            nuevo.padre = anterior;
        }
        _cardinal++;
    }
    }

    public boolean pertenece(T elem){
        Nodo actual = _raiz;
        while (actual != null) {
            if (elem.compareTo(actual.valor) == 0) {
                return true;
            }
            else if (elem.compareTo(actual.valor) < 0) {
                actual = actual.izq;
            }
            else {
                actual = actual.der;
            }
    
        }
    
        return false;
    }

    public void eliminar(T elem){
        Nodo actual = _raiz;
        Nodo anterior = null;

        // Si no está en el conj, no hago nada.
        if (!(pertenece(elem))) {
            return;
        }
            /* Si quiero remover la raíz y además esta es el único elemento
            del conjunto (no tiene hijos)*/
        else if ((elem.compareTo(_raiz.valor) == 0) && (_cardinal == 1)) {
            
            _raiz = null;
            _cardinal--;
        } else {
            /* Busco el nodo, que sé que está, de lo contrario hubiera entrado
            al primer if */
            while (actual.valor.compareTo(elem) != 0) {
                if (elem.compareTo(actual.valor) < 0) {
                   
                    actual = actual.izq;

                } else {
                   
                    actual = actual.der;

                }
            }
            anterior = actual.padre;

            /* Caso en que el nodo no tiene hijos y además NO ES la raíz */
            if ((actual.der == null) && (actual.izq == null)) {
                if (anterior.der == actual) {
                    anterior.der = null;
                    actual = null;
                    _cardinal--;

                } else {
                    anterior.izq = null;
                    actual = null;
                    _cardinal--;

                }

            }

                /* Caso en que tiene un solo hijo a la izquierda */
            else if ((actual.der == null) && (actual.izq != null)) {
                // Si es la raíz //
                if (elem.compareTo(_raiz.valor) == 0) {
                   
                    
                    _raiz = _raiz.izq;
                    _raiz.padre =null;
                    _cardinal--;
                }
                    // Si no es la raíz //
                else if (anterior.der == actual) {
                    anterior.der = actual.izq;
                    actual.izq.padre = anterior;
                    _cardinal--;

                } else {
                    anterior.izq = actual.izq;
                    actual.izq.padre = anterior;
                    _cardinal--;
                }

            }
                // Caso en que tiene un solo hijo a la derecha //
            else if ((actual.izq == null) && (actual.der != null)) {
                // Si es la raíz //
                if (elem.compareTo(_raiz.valor) == 0) {
                    
                    
                    _raiz = _raiz.der;
                    _raiz.padre =null;
                    _cardinal--;
                }
                    // Si no es la raíz //
                else if (anterior.der == actual) {
                    anterior.der = actual.der;
                    actual.der.padre = anterior;
                    
                    _cardinal--;

                } else {
                    anterior.izq = actual.der;
                    actual.der.padre = anterior;

                    _cardinal--;

                }

            } else { // Caso en que tiene dos hijos //
                /* Busco el mínimo en el subárbol derecho
                y lo llevo al lugar del nodo que estoy eliminando */

                //Busco el mínimo//
                Nodo minimo = actual.der;
                while (minimo.izq != null) {
                    minimo = minimo.izq;
                }

                //Me guardo el valor del mínimo y elimino "la copia" //
                T nuevo_valor = minimo.valor;
                eliminar(nuevo_valor);
                /* Actualizo el árbol con el valor que reemplaza al que quiero
                borrar */
                actual.valor = nuevo_valor;
                
            }
        }

    }

    public String toString(){
        String res = "{";
        Iterador<T> t = iterador(); 
        while(t.haySiguiente()){
            res = res + t.siguiente() + ",";
        }
        res = res.substring(0, res.length() - 1);
        res = res+"}";
        return res;
    }
    private Nodo obtenerNodoMinimo(){
        Nodo _actual = _raiz;
        while(_actual.izq != null){
            _actual = _actual.izq;
        }
        return _actual;
    }

    private class ABB_Iterador implements Iterador<T> {
        private Nodo _actual;
        public ABB_Iterador(){
            _actual = obtenerNodoMinimo();
        }
        
        
        private int contador = 0;

        public boolean haySiguiente() {            
            return contador < _cardinal;
        }
    
        public T siguiente() {
            T valor = _actual.valor;
        if (contador < _cardinal -1){
                if(_actual.der != null){
                    _actual = _actual.der;
                    while(_actual.izq != null){
                        _actual = _actual.izq;
                    }
                    contador++;
                    return valor;
                }
                Nodo y = _actual.padre;
                while (y != null && _actual == y.der ){
                    _actual = y;
                    y = y.padre;
                }
                _actual = y;
                
                }
        
        else {
            
            
            _actual = null;
            
                }
                contador++;
                return valor;
        }
    }

    public Iterador<T> iterador() {
        return new ABB_Iterador();
    }

}
