//
// Created by arnaud on 09/03/18.
//

#include "VSommet.h"

VSommet::VSommet (Vecteur2D position, bool marked = false, const InfoAStar &infoAStar) : position(position), infoAStar(infoAStar)
{}

VSommet::~VSommet ()
= default;

VSommet::VSommet (const VSommet &vs) : position(vs.position), infoAStar(vs.infoAStar)
{}

VSommet::operator string () const
{
    ostringstream oss;

    oss << "VSommet :" << " InfoAStar :" << infoAStar << " Position : "
        << position;
    return oss.str();
}

ostream &operator<< (ostream &o, const VSommet &vs)
{
    o << (string) vs;
}