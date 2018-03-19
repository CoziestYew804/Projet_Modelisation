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
bool FenetreGrapheSFML::dessineChemin (const PElement<Sommet<VSommet>> *chemin, Graphe<VArete, VSommet> &G)
{
    while(chemin)
    {
        chemin->valeur->v.setCouleur(sf::Color::Red);
        dessine(chemin->valeur);
        if(chemin->suivant)
        {
            Arete<VArete, VSommet> *arete = G.getAreteParSommets(chemin->valeur, chemin->suivant->valeur);
            arete->v.setCouleur(sf::Color::Red);
            dessine(arete);
        }
        chemin = chemin->suivant;
    }
    return true;
}