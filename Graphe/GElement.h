#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "AElement.h"

using namespace std;

/**

Repr�sente la classe template de base des �l�ments d'un graphe qui peuvent �tre des sommets ou des ar�tes.

A ce niveau, on ne peut que d�finir que la clef d'un �l�ment et la valeur (c'est-�-dire l'information ) inscrite dans cet �l�ment.

En effet tout �l�ment d'un graphe est d�fini par une clef (c-�-d une valeur non nulle et unique) et contient  g�n�ralement une information,
qui peut �tre un nom, une couleur, une position, etc.



*/

template <class T>
class GElement : public AElement
{
public:
T v;
GElement(const int clef, const T & v): AElement(clef), v(v) {}

    explicit operator string () const
    {
        ostringstream o;
        o << this->AElement::operator string() << ", v = " << v;
        return o.str();
    }

friend ostream & operator << (ostream & os, const GElement<T>& gElement) {return os << (string) gElement;}
};


