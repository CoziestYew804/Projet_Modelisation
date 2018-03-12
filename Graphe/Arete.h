#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "GElement.h"
#include "Sommet.h"

using namespace std;

/**

repr�sente une ar�te d'un graphe en g�n�ral.

Une ar�te est d�finie par un sommet-d�but et par un sommet-fin et par une information v.

On ne conna�t pas la nature de v � ce niveau (v pourrait contenir une couleur, une longueur, un nom, etc.)

T est la nature de l'information port�e par un sommet et
S est la nature de l'information port�e par une ar�te

*/

template <class S, class T>
class Arete : public GElement<S>
{
public:
    Sommet <T> *debut, *fin;	// debut et fin peuvent �tre interpr�t�es comme des clefs �trang�res vers une table de sommets

/**
met � jour le degr� des sommets que cette nouvelle ar�te va connecter
*/

    Arete( const int clef, const S & v, Sommet<T> * debut, Sommet<T> * fin) : GElement<S>( clef, v) ,debut( debut), fin( fin)
    {
        debut->degre++;
        fin->degre++;
    }

/**
met � jour le degr� des sommets que cette nouvelle ar�te va d�connecter
*/

    ~Arete()
    {
        debut->degre--;
        fin->degre--;
    }

    explicit operator string () const
    {
        ostringstream oss;

        oss <<"\tArete\n\t("<< endl;
        oss << "\t\t" << GElement<S>::operator string()<<endl;
        oss << "\t\tClef debut = " << debut->clef<< endl;
        oss << "\t\tClef fin = " << fin->clef << endl;
        oss << "\t)";
        return oss.str();
    }


/**
 * v�rifie si *this s'appuie sur s1 et s2
 *
 * DONNEES : *this, s1, s2
 *
 * RESULTATS : true si *this s'appuie sur s1 et s2 c'est-�-dire si (d�but == s1 et fin == s2) ou (d�but == s2 et fin == s1), false sinon
 *
 * */

    bool estEgal( const Sommet<T> * s1, const Sommet<T> * s2) const
    {
        return (s1 == debut && s2 == fin) || (s1 == fin && s2 == debut);
    }

    friend ostream & operator << (ostream & os, const Arete<S,T> & arete)
    {
        return os << (string)arete;
    }
};
