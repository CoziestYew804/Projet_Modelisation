//
// Created by arnaud on 28/02/18.
//

#ifndef PROJETSFML_PACMAN_VSOMMET_H
#define PROJETSFML_PACMAN_VSOMMET_H


#include <SFML/System.hpp>
#include "InfoAlgo.h"
#include "../Screen/Vecteur2D.h"

class VSommet
{
public:
    InfoAlgo infoAlgo;
    string nom;
    int bordInf,bordSup;
private:
    Vecteur2D position;
public:
    explicit VSommet (Vecteur2D position,string nom, int bordInf, int bordSup);
    virtual ~VSommet ();
    //VSommet (const VSommet &vs);

    explicit operator string () const;

    friend ostream &operator<< (ostream &o, const VSommet &vs);

    inline string &getNom ();

    inline InfoAlgo &getInfoAlgo ();
    inline void setInfoAlgo (const InfoAlgo &InfoAlgo);

    inline const Vecteur2D &getPosition () const;

    inline void setPosition (const Vecteur2D &position);

    inline void switchMarked();

    inline bool isMarked() const;

};

inline InfoAlgo &VSommet::getInfoAlgo ()
{
    return infoAlgo;
}

inline string &VSommet::getNom  ()
{
    return nom;
}

inline void VSommet::setInfoAlgo (const InfoAlgo &InfoAlgo)
{
    VSommet::infoAlgo = InfoAlgo;
}

inline const Vecteur2D &VSommet::getPosition () const
{
    return position;
}

inline void VSommet::setPosition (const Vecteur2D &position)
{
    VSommet::position = position;
}

#endif //PROJETSFML_PACMAN_VSOMMET_H
