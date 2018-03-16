//
// Created by arnaud on 09/03/18.
//

#include "VArete.h"

VArete::VArete(int dir, int temps, int duree, sf::Color couleur = sf::Color::Cyan) : dir(dir), _temps(temps), _duree(duree)
{

}

VArete::~VArete ()
= default;

VArete::VArete (const VArete &va): dir(va.dir), _temps(va._temps), _duree(va._duree)
{}

VArete::operator string () const
{
    ostringstream oss;

    oss << "VArete : Dir : " << dir << " temps : " << _temps << " duree : " << _duree;
    return oss.str();
}

ostream &operator<< (ostream &o, const VArete &va)
{
    o << (string)va;
}






