#ifndef _tavlcom_h
#define _tavlcom_h
#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"

class TNodoAVL;
class TAVLCom {
    friend ostream & operator<<(ostream &,const TAVLCom &);
    friend class TNodoAVL;
    private:
        TNodoAVL *raiz;
        // AUXILIAR: Devuelve el recorrido en inorden
        void InordenAux(TVectorCom &, int &) const;
        // AUXILIAR: Devuelve el recorrido en preorden
        void PreordenAux(TVectorCom &, int &)const;
        // AUXILIAR: Devuelve el recorrido en postorden
        void PostordenAux(TVectorCom &, int &)const;

        TComplejo BuscarNodo();
        bool Insertar(const TComplejo &c, bool &crece);
        bool Borrar(const TComplejo &tc, bool &i);
        void RotarDerecha();
		void RotarIzquierda();
		void RotarDobleDerecha();
		void RotarDobleIzquierda();
    public:
        // Constructor por defecto
        TAVLCom ();
        // Constructor de copia
        TAVLCom (const TAVLCom &);
        // Destructor
        ~TAVLCom ();
        // Sobrecarga del operador asignación
        TAVLCom & operator=(const TAVLCom &);
        // Sobrecarga del operador igualdad
        bool operator==(const TAVLCom &) const;
        // Sobrecarga del operador desigualdad
        bool operator!=(const TAVLCom &)const;
        // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
        bool EsVacio() const;
        // Inserta el elemento TComplejo en el árbol
        bool Insertar(const TComplejo &);
        // Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
        bool Buscar(const TComplejo &)const;
        // Borra un TComplejo del árbol AVL
        bool Borrar(const TComplejo &);
        // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
        int Altura() const;
        // Devuelve el elemento TComplejo raíz del árbol AVL
        TComplejo Raiz() const;
        // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        int Nodos() const;
        // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
        int NodosHoja() const;
        // Devuelve el recorrido en inorden sobre un vector
        TVectorCom Inorden() const;
        // Devuelve el recorrido en preorden sobre un vector
        TVectorCom Preorden() const;
        // Devuelve el recorrido en postorden sobre un vector
        TVectorCom Postorden() const;

        TVectorCom Niveles() const;
};

class TNodoAVL {
    friend class TAVLCom;
    private:
        TComplejo item;
        TAVLCom iz, de;
        int fe;
    public:
        // Constructor por defecto
        TNodoAVL ();

        TNodoAVL(const TComplejo &c);
        // Constructor de copia
        TNodoAVL (const TNodoAVL &);
        // Destructor
        ~TNodoAVL ();
        // Sobrecarga del operador asignación
        TNodoAVL & operator=(const TNodoAVL &);
};


#endif