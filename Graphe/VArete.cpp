//
// Created by arnaud on 09/03/18.
//

#include "VArete.h"

VArete::VArete (string nom, int duree, int c, sf::Color couleur):duree(duree), couleur(couleur), infoAlgo(0, c), nom(nom)
{}

VArete::~VArete ()
= default;

VArete::operator string () const
{
    ostringstream oss;

    oss << "VArete : << nom: "<< nom <<" Duree : " << duree << " Info : " << infoAlgo;
    return oss.str();
}

ostream &operator<< (ostream &o, const VArete &va)
{
    o << (string)va;
}







