//
// Created by alex on 10/03/18.
//

#include "Thing.h"

Thing::Thing(Thing &p):position(p.position), image(p.image), nom(p.nom), etat(p.etat){}

Thing::Thing(Sommet<VSommet> *position, string image, string nom, int etat):position(position), image(image), nom(nom), etat(etat){}

Thing::~Thing(){};

void Thing::setNom(const string &nom)
{
    Thing::nom = nom;
}


const string &Thing::getImage () const
{
    return image;
}


void Thing::setImage (const string &sprite)
{
    Thing::image = sprite;
}

/*
const void Thing::dessine (FenetreGrapheSFML &window)
{
    sf::Image img;
    img.loadFromFile("images/" + image + ".png");
    img.createMaskFromColor(Color::Black);
    sf::Texture texture;
    if (!texture.loadFromImage(img))
    {
        Erreur("Chargement" + image);
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(vecteur2DToVector2f(window.t.applique(position->v.getPosition()) - 10 * Vecteur2D(1, 1)));
    window.fenetre.draw(sprite);
}*/


Sommet<VSommet>* Thing::getPosition () const
{
    return position;
}


void Thing::setPosition (Sommet<VSommet> *position)
{
    this->position = position;
}
