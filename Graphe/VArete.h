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
    string nom;
    VArete (string nom,int duree, int c, sf::Color couleur = sf::Color::Cyan);
    virtual ~VArete ();

    explicit operator string () const;

    friend ostream& operator<< (ostream &o, const VArete &va);

    inline int getDuree() const;
    inline void setDuree(int duree);
    inline const InfoAlgo& getInfoAlgo() const;
    inline void setInfoAlgo(const InfoAlgo &infoAlgo);
    inline const sf::Color &getCouleur () const;
    inline void setCouleur (const sf::Color &couleur);
};

inline int VArete::getDuree() const
{
    return duree;
}
inline void VArete::setDuree(int duree)
{
    VArete::duree = duree;
}

inline const InfoAlgo& VArete::getInfoAlgo() const
{
    return infoAlgo;
}
inline void VArete::setInfoAlgo(const InfoAlgo &infoAlgo)
{
    VArete::infoAlgo = infoAlgo;
}

inline const sf::Color &VArete::getCouleur () const
{
    return couleur;
}

inline void VArete::setCouleur (const sf::Color &couleur)
{
    VArete::couleur = couleur;
}

#endif //PROJETSFML_PACMAN_VARETE_H
