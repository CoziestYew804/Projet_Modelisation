//
// Created by alex on 10/03/18.
//

#include "Pacman.h"

Pacman::Pacman(Pacman &p):Personnage(p){}

Pacman::Pacman (Sommet<VSommet> *position, string nom, string image, Texture *texture, Vector2u imageCount,
                float switchTime, float speed, TransfoAffine2D t, int etat):Personnage(position, image, nom,
                                                                                       texture, imageCount,
                                                                                       switchTime, speed, t,
                                                                                       etat)
{}

Pacman::~Pacman(){}


void Pacman::setPosition (Sommet<VSommet> *position, TransfoAffine2D &t)
{
    Personnage::setPosition(position, t);
    if(this->getPosition()->v.isGom())
    {
        this->getPosition()->v.setGom(false);

    }
}
