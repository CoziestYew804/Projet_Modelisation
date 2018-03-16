//
// Created by arnaud on 01/03/18.
//

#ifndef PROJETSFML_PACMAN_VARETE_H
#define PROJETSFML_PACMAN_VARETE_H

#include <utility>
#include <sstream>
#include <string>
#include "SFML/Graphics.hpp"
#include "InfoAlgo.h"

using namespace std;

class VArete
{
private:
    int duree;
    sf::Color couleur;
    InfoAlgo infoAlgo;
public:
    VArete (int duree, double c, sf::Color couleur = sf::Color::Cyan);
    virtual ~VArete ();
    VArete (const VArete &va);

    explicit operator string () const;

    friend ostream& operator<< (ostream &o, const VArete &va);

    inline int getDuree() const;
    inline void setDuree(int duree);
    inline InfoAlgo getInfoAlgo() const;
    inline void setInfoAlgo(const InfoAlgo &infoAlgo);
};

inline int VArete::getDuree() const
{
    return duree;
}
inline void VArete::setDuree(int duree)
{
    VArete::duree = duree;
}

inline InfoAlgo VArete::getInfoAlgo() const
{
    return infoAlgo;
}
inline void VArete::setInfoAlgo(const InfoAlgo &infoAlgo)
{
    VArete::infoAlgo = infoAlgo;
}

#endif //PROJETSFML_PACMAN_VARETE_H
