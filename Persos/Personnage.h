//
// Created by arnaud on 24/01/18.
//

#ifndef GRAPHES_PERSONNAGE_H
#define GRAPHES_PERSONNAGE_H

#include "../Graphe/Sommet.h"
#include "../World/Thing.h"
#include "Animation.h"
#include <string>

using namespace std;


class Personnage : public Thing
{
private:
    RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    Vector2f movement;
    Texture *texture;
public:
    explicit Personnage (Sommet<VSommet> *position, string image, string nom, Texture *texture, Vector2u imageCount,
                               float switchTime, float speed, TransfoAffine2D &t, int etat = 1);
    Personnage(Personnage &p);
    virtual ~Personnage ();

    void Update (float deltaTime);

    virtual const void dessine (FenetreGrapheSFML &window);

    Texture *getTexture () const;

    virtual void setPosition (Sommet<VSommet> *position, TransfoAffine2D t);
};

#endif //GRAPHES_PERSONNAGE_H