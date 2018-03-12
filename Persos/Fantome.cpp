//
// Created by alex on 10/03/18.
//

#include "Fantome.h"
#include "Pacman.h"

Fantome::Fantome(Fantome &p):Personnage(p){}


Fantome::Fantome (Sommet<VSommet> *position, string nom, string image, Texture *texture, Vector2u imageCount,
                  float switchTime, float speed, TransfoAffine2D t, int etat):Personnage(position, image,
                                                                                         nom, texture,
                                                                                         imageCount,
                                                                                         switchTime, speed,
                                                                                         t, etat)
{}

Fantome::~Fantome ()
{};


void Fantome::setPosition (Sommet<VSommet> *position, Pacman &pacman, TransfoAffine2D &t)
{
    Personnage::setPosition(position, t);
    if(this->position == pacman.getPosition())
        pacman.setEtat(false);
}