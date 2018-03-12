//
// Created by arnaud on 09/03/18.
//

#include "VSommet.h"

VSommet::VSommet (Vecteur2D position, bool Perso, bool Gom, const InfoAStar &infoAStar) : position(position),
                                                                                          Perso(Perso), Gom(Gom),
                                                                                          infoAStar(infoAStar)
{}

VSommet::~VSommet ()
= default;

VSommet::VSommet (const VSommet &vs) : position(vs.position), Perso(vs.Perso), Gom(vs.Gom), infoAStar(vs.infoAStar)
{}

VSommet::operator string () const
{
    ostringstream oss;

    oss << "VSommet : Perso : " << Perso << " Gom : " << Gom << " InfoAStar :" << infoAStar << " Position : "
        << position;
    return oss.str();
}

ostream &operator<< (ostream &o, const VSommet &vs)
{
    o << (string) vs;
}