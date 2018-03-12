//
// Created by arnaud on 28/02/18.
//

#ifndef PROJETSFML_PACMAN_VSOMMET_H
#define PROJETSFML_PACMAN_VSOMMET_H


#include <SFML/System.hpp>
#include "InfoAStar.h"
#include "../Screen/Vecteur2D.h"

class VSommet
{
public:
    InfoAStar infoAStar;
private:
    bool Perso, Gom;
    Vecteur2D position;
public:
    explicit VSommet (Vecteur2D position, bool Perso = false, bool Gom = true,
                      const InfoAStar &infoAStar = InfoAStar());
    virtual ~VSommet ();
    VSommet (const VSommet &vs);

    explicit operator string () const;

    friend ostream &operator<< (ostream &o, const VSommet &vs);

    inline bool isPerso () const;
    inline void setPerso (bool Perso);
    inline bool isGom () const;
    inline void setGom (bool Gom);
    inline InfoAStar &getInfoAStar ();
    inline void setInfoAStar (const InfoAStar &infoAStar);

    inline const Vecteur2D &getPosition () const;

    inline void setPosition (const Vecteur2D &position);

};

inline bool VSommet::isPerso () const
{
    return Perso;
}

inline void VSommet::setPerso (bool Perso)
{
    VSommet::Perso = Perso;
}

inline bool VSommet::isGom () const
{
    return Gom;
}

inline void VSommet::setGom (bool Gom)
{
    VSommet::Gom = Gom;
}

inline InfoAStar &VSommet::getInfoAStar ()
{
    return infoAStar;
}

inline void VSommet::setInfoAStar (const InfoAStar &infoAStar)
{
    VSommet::infoAStar = infoAStar;
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
