//
// Created by alex on 10/03/18.
//

#include "Personnage.h"

Personnage::Personnage (Personnage &p):Thing(p), body(p.body), animation(p.animation), row(p.row),
                                       speed(p.speed), movement(p.movement), texture(p.texture)
{};


Personnage::Personnage (Sommet<VSommet> *position, string nom, string image, Texture *texture, Vector2u imageCount,
                        float switchTime, float speed, TransfoAffine2D &t, int etat):
        Thing(position, image, nom, etat), animation(texture, imageCount, switchTime), speed(speed), row(0)
{
    //this->getPosition()->v.setGom(false);
    body.setSize(Vector2f(64.0f, 64.0f));
    body.setPosition(vecteur2DToVector2f(t.applique(this->getPosition()->v.getPosition()) - Vecteur2D(32, 32)));
    //t = Texture();
    //if(!t.loadFromFile("imgpacman/Textures.png")) throw ("Erreur lors du chargement des textures.");
    body.setTexture(texture);
}

Personnage::~Personnage(){};


void Personnage::Update (float deltaTime)
{
    movement.x = 0.0f;
    movement.y = 0.0f;
    if (Keyboard::isKeyPressed(Keyboard::Numpad4)) //Left
    {
        movement.x -= speed * deltaTime;
        movement.y = 0.0f;
    }

    if (Keyboard::isKeyPressed(Keyboard::Numpad6)) //Right
    {
        movement.x += speed * deltaTime;
        movement.y = 0.0f;
    }

    if (Keyboard::isKeyPressed(Keyboard::Numpad8)) //Up
    {
        movement.y -= speed * deltaTime;
        movement.x = 0.0f;
    }

    if (Keyboard::isKeyPressed(Keyboard::Numpad2)) //Down
    {
        movement.y += speed * deltaTime;
        movement.x = 0.0f;
    }


    if (Keyboard::isKeyPressed(Keyboard::Numpad7)) //UpLeft
    {
        movement.x -= speed * deltaTime;
        movement.y -= speed * deltaTime;
    }

    if (Keyboard::isKeyPressed(Keyboard::Numpad9)) //DownRight
    {
        movement.x += speed * deltaTime;
        movement.y -= speed * deltaTime;
    }

    if (Keyboard::isKeyPressed(Keyboard::Numpad1)) //UpLeft
    {
        movement.x -= speed * deltaTime;
        movement.y += speed * deltaTime;
    }

    if (Keyboard::isKeyPressed(Keyboard::Numpad3)) //UpRight
    {
        movement.x += speed * deltaTime;
        movement.y += speed * deltaTime;
    }

    if (movement.x < 0)
    {
        if (movement.y < 0)         //UpLeft
        {
            row = 7;
        } else if (movement.y > 0)    //DownLeft
        {
            row = 6;
        } else                        //Left
        {
            row = 3;
        }
    } else if (movement.x > 0)
    {
        if (movement.y < 0)         //UpRight
        {
            row = 4;
        } else if (movement.y > 0)    //DownRight
        {
            row = 5;
        } else                        //Right
        {
            row = 1;
        }
    } else // movement.x = 0
    {
        if (movement.y < 0)         //Down
        {
            row = 0;
        } else if (movement.y > 0)    //Up
        {
            row = 2;
        } else                        //Immobile
        {

        }
    }
    animation.Update(row, deltaTime);
    body.setTextureRect(animation._textureRect);
    //body.move(movement.x, movement.y);

}


const void Personnage::dessine (FenetreGrapheSFML &window)
{
    window.fenetre.draw(body);
}


Texture *Personnage::getTexture () const
{
    return texture;
}


void Personnage::setPosition (Sommet<VSommet> *position, TransfoAffine2D t)
{
    Thing::setPosition(position);
    body.setPosition(vecteur2DToVector2f(t.applique(this->getPosition()->v.getPosition()) - Vecteur2D(32, 32)));
}

