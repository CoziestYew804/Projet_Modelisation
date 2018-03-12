#ifndef AELEMENT_H
#define AELEMENT_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**

Représente la classe de base des éléments d'un graphe qui peuvent être des sommets ou des arêtes.

A ce niveau, on ne peut que définir que la clef d'un élément inscrite dans cet élément.

En effet tout élément d'un graphe est tout d'abord défini par une clef (c-à-d une valeur non nulle et unique)

*/

class AElement
{
public:
    int clef;

    explicit AElement (const int clef);

    virtual operator string () const;

    friend ostream &operator<<(ostream &os, const AElement &aElement);
};
#endif // AELEMENT_H
