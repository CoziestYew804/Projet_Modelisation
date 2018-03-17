//
// Created by arnaud on 09/03/18.
//

#include "VSommet.h"

VSommet::VSommet (Vecteur2D position) : position(position)
{}

VSommet::~VSommet ()
= default;

VSommet::VSommet (const VSommet &vs) : position(vs.position), infoAlgo(vs.infoAlgo)
{}

VSommet::operator string () const
{
    ostringstream oss;

    oss << "VSommet :" << " InfoAStar :" << infoAlgo << " Position : "
        << position;
    return oss.str();
}

ostream &operator<< (ostream &o, const VSommet &vs)
{
    o << (string) vs;
}