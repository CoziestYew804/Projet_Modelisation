//
// Created by arnaud on 24/01/18.
//

#ifndef GRAPHES_PACMAN_H
#define GRAPHES_PACMAN_H

#include "Personnage.h"


class Pacman : public Personnage
{
public:
    explicit Pacman (Sommet<VSommet> *position, string image, string nom, Texture *texture, Vector2u imageCount,
                           float switchTime, float speed, TransfoAffine2D t, int etat = 1);
    Pacman(Pacman &p);
    virtual ~Pacman ();

    void setPosition (Sommet<VSommet> *position, TransfoAffine2D &t);

    //const void dessine (FenetreGrapheSFML &window) override;
};



//
/*template<>
const void Pacman<VArete, VSommet>::dessine (FenetreGrapheSFML &window)
{
    Time time= milliseconds(100);
    Clock c;
    Texture t1;
    t1.loadFromFile("imgpacman/pacman-spritesheet.png");


    Sprite s[5];
    for (int i = 0; i < 5; i++)
    {
        s[i] = Sprite(t1);
        s[i].setTextureRect(IntRect(i*120,0,110,110));
        s[i].setPosition(vecteur2DToVector2f(window.t.applique(getPosition()->v.getPosition())));
    }

    //window.fenetre.clear(Color::Black);
    window.fenetre.draw(s[0]);
    window.fenetre.display();
    sleep(milliseconds(100));
    //window.fenetre.clear(Color::Black);
    window.fenetre.draw(s[1]);
    window.fenetre.display();
    sleep(milliseconds(100));
    //window.fenetre.clear(Color::Black);
    window.fenetre.draw(s[2]);
    window.fenetre.display();
    sleep(milliseconds(100));
    //window.fenetre.clear(Color::Black);
    window.fenetre.draw(s[3]);
    window.fenetre.display();
    sleep(milliseconds(100));
    //window.fenetre.clear(Color::Black);
    window.fenetre.draw(s[4]);
    window.fenetre.display();
    sleep(milliseconds(100));
}*/


#endif //GRAPHES_PACMAN_H
