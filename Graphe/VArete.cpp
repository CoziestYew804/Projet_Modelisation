//
// Created by arnaud on 09/03/18.
//

#include "VArete.h"

VArete::VArete (int temps, int duree, sf::Color couleur):temps(temps), duree(duree), couleur(couleur)
{
    //VArete::couleur = couleur;
}

VArete::~VArete ()
= default;

VArete::VArete (const VArete &va):temps(va.temps), duree(va.duree), couleur(va.couleur)
{}

VArete::operator string () const
{
    ostringstream oss;

    oss << "VArete : Dir : " << " temps : " << temps << " duree : " << duree;
    return oss.str();
}

ostream &operator<< (ostream &o, const VArete &va)
{
    o << (string)va;
}







