//
// Created by arnaud on 24/01/18.
//

#ifndef GRAPHES_FANTOME_H
#define GRAPHES_FANTOME_H


#include "Personnage.h"
#include "../World/board.h"
#include "Pacman.h"


class Fantome : public Personnage
{
public:
    explicit Fantome (Sommet<VSommet> *position, string image, string nom, Texture *texture, Vector2u imageCount,
                            float switchTime, float speed, TransfoAffine2D t, int etat = 1);
    Fantome(Fantome &p);
    virtual ~Fantome ();

    void setPosition (Sommet<VSommet> *position, Pacman &pacman, TransfoAffine2D &t);
};




#endif //GRAPHES_FANTOME_H
