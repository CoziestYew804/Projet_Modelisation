//
// Created by alex on 10/03/18.
//

#include "FenetreGrapheSFML.h"



template<>
bool FenetreGrapheSFML::dessine<VSommet> (const Sommet<VSommet> *sommet)
{
    return dessineSommet(this->fenetre, this->t, sommet->v);
}

/*
{
Vecteur2D position = t.applique(sommet->v.p)-VSommet::rayonDisquePixels*Vecteur2D(1,1);

// si on appliquait la transfo t globalement � tout le graphe avant de commencer � dessiner, on optimiserait
// bcp de calculs !!!!

CircleShape disque((float)VSommet::rayonDisquePixels);
disque.setFillColor(Color(sommet->v.couleur));
float epaisseurBord = (float)(0.15*VSommet::rayonDisquePixels);
disque.setOutlineThickness(epaisseurBord);
disque.setOutlineColor(Color(VSommet::couleurBord));
float x,y;
position.arrondit(x,y);

disque.setPosition(x, y);

fenetre.draw(disque);

unsigned int tailleEnPixels = 15;
Text texte(sommet->v.nom, font,tailleEnPixels);
texte.setFillColor(Color::Black);
texte.setPosition(x,y);
fenetre.draw(texte);
return true;
}
*/

template<>
bool FenetreGrapheSFML::dessine<VArete, VSommet> (const Arete<VArete, VSommet> *arete)
{
    return dessineArete(this->fenetre, this->t, arete->debut->v.getPosition(), arete->fin->v.getPosition(),
                            Color::Cyan);
}
