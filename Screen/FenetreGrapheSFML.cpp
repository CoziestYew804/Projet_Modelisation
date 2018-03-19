//
// Created by alex on 10/03/18.
//

#include "FenetreGrapheSFML.h"
#include "../Graphe/Graphe.h"


template<>
bool FenetreGrapheSFML::dessine<VSommet> (const Sommet<VSommet> *sommet)
{
    return dessineSommet(this->fenetre, this->t, sommet->v);
}

template<>
bool FenetreGrapheSFML::dessine<VArete, VSommet> (const Arete<VArete, VSommet> *arete)
{
    return dessineArete(this->fenetre, this->t, arete->debut->v.getPosition(), arete->fin->v.getPosition(),
                            arete->v);
}

template<>
bool FenetreGrapheSFML::changeCouleurChemin (const PElement<Sommet<VSommet>> *chemin, Graphe<VArete, VSommet> &G)
{
    while(chemin)
    {
        chemin->valeur->v.setCouleur(sf::Color::Red);
        if(chemin->suivant)
        {
            G.getAreteParSommets(chemin->valeur, chemin->suivant->valeur)->v.setCouleur(sf::Color::Red);
        }
        chemin = chemin->suivant;
    }
    return true;
}