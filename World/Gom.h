//
// Created by arnaud on 29/01/18.
//

#ifndef PROJETSFML_PACMAN_GOM_H
#define PROJETSFML_PACMAN_GOM_H

#include "Thing.h"


template<class S, class T>
class Gom : public Thing<S, T>
{
public:
    Gom<S, T> (Sommet<T> *position, string image, string nom = "Gom", int etat = 1);
    Gom<S, T>(Gom &p);
    virtual ~Gom ();
};
template<class S, class T>
Gom<S, T>::Gom(Gom<S, T> &p):Thing<S, T>(p){}
template<class S, class T>
Gom<S, T>::Gom (Sommet<T> *position, string image, string nom, int etat):Thing<S, T>(position, image, nom, etat)
{}
template<class S, class T>
Gom<S, T>::~Gom ()= default;


#endif //PROJETSFML_PACMAN_GOM_H
