#ifndef PROJETSFML_Thing_GOM_H
#define PROJETSFML_Thing_GOM_H

#include "../Graphe/Sommet.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "../Screen/FenetreSFML.h"
#include "../Screen/FenetreGrapheSFML.h"
#include "../Screen/TransfoAffine2D.h"

using namespace std;

/**
 *
 */
class Thing
{
public:
    Sommet<VSommet> *position;
private:
    int etat;
    string nom, image;
public:
    Sommet<VSommet>* getPosition () const;

    virtual void setPosition (Sommet<VSommet> *position);
public:
    explicit Thing(Sommet<VSommet> *position, string image, string nom, int etat=1);
    Thing(Thing &p);
    virtual ~Thing ();

    inline void setEtat(bool etat);
    inline int getEtat() const;
    string getNom () const;
    void setNom (const string &nom);
    const string &getImage () const;
    void setImage (const string &sprite);

    virtual const void dessine (FenetreGrapheSFML &window) = 0;
};



inline void Thing::setEtat(bool etat)
{
    Thing::etat = etat;
}

inline int Thing::getEtat () const
{
    return etat;
}


inline string Thing::getNom () const
{
    return nom;
}



#endif //PROJETSFML_Thing_GOM_H