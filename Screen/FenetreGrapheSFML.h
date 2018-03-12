#ifndef FENETREGRAPHESFML_H
#define FENETREGRAPHESFML_H


#include<SFML/Graphics.hpp>
#include "../Graphe/Sommet.h"
#include "../Graphe/Arete.h"
//#include <InfoSommet.h>
//#include <InfoArete.h>
#include "TransfoAffine2D.h"
#include "../Graphe/VSommet.h"
#include "../Graphe/VArete.h"
#include "Vecteur2D.h"
#include "../Erreur.h"

using namespace sf;
using namespace std;

/**
Prend en charge le dessin d'un graphe.
Suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re Monde.
Prend en charge le passage fen�tre-cl�ture
*/


inline const Vector2f vecteur2DToVector2f (const Vecteur2D &v)
{
    float x, y;
    v.arrondit(x, y);
    return Vector2f(x, y);
}


/**

vSommet : en coordonn�es monde
*/
inline bool dessineSommet (RenderWindow &fenetre, const TransfoAffine2D &t, const VSommet &vSommet)
{
    Vecteur2D position = t.applique(vSommet.getPosition());
    Vecteur2D position1 = position - 30 * Vecteur2D(1, 1);

    CircleShape disque((float) 30);
    disque.setFillColor(Color::Black);
    //float epaisseurBord = (0.15f * 30.0f);
    disque.setOutlineThickness(8);
    disque.setOutlineColor(Color::Cyan);

    Vector2f p1 = vecteur2DToVector2f(position1);
    disque.setPosition(p1);
    fenetre.draw(disque);

    if (vSommet.isGom())
    {
        sf::Image img;
        img.loadFromFile("imgpacman/superpellet.png");
        img.createMaskFromColor(Color::Black);
        sf::Texture texture;
        if (!texture.loadFromImage(img))
        {
            Erreur("Chargement pellet");
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(vecteur2DToVector2f(position - 6 * Vecteur2D(1, 1)));
        fenetre.draw(sprite);
    }

    return true;
}

/**
d�but et fin sont en coordonn�es monde
*/
inline bool dessineArete (RenderWindow &fenetre, const TransfoAffine2D &t, const Vecteur2D &debut, const Vecteur2D &fin,
                          const Color couleur)
{
    Vecteur2D A, B;    // {AB] est l'ar�te � repr�senter

    A = t.applique(debut);
    B = t.applique(fin);        // on passe des coordonn�es monde aux coordonn�es �cran

    Vecteur2D u = B - A;

    double nU = norme(u);
    u /= nU;
    Vecteur2D n = u.rotationDirecteQuartDeTour();

    //double e = 1;	// �paisseur du rectangle = 2*e. longueur du rectangle == AB
    double e = 10;    // �paisseur du rectangle = 2*e. longueur du rectangle == AB

    Vecteur2D v = e * n;

    Vecteur2D A0 = A - v, A1 = B - v, A2 = B + v, A3 =
            A + v; // on calcule les 4 sommets du rectangle dont l'ar�te [AB] est un axe de sym�trie

    Vector2f F0 = vecteur2DToVector2f(A0);
    Vector2f F1 = vecteur2DToVector2f(A1);
    Vector2f F2 = vecteur2DToVector2f(A2);
    Vector2f F3 = vecteur2DToVector2f(A3);

    ConvexShape rectangle(4);
    rectangle.setPoint(0, F0);
    rectangle.setPoint(1, F1);
    rectangle.setPoint(2, F2);
    rectangle.setPoint(3, F3);


    rectangle.setFillColor(couleur);
    fenetre.draw(rectangle);

    return true;
}


/**
Prend en charge le dessin d'un graphe
Prend en charge le passage de coordonn�es monde ---> �cran
*/
class FenetreGrapheSFML
{
public:
    RenderWindow fenetre;
    TransfoAffine2D t;    // r�alise le passage fen�tre-cl�ture (ou encore monde vers �cran)
/**
Cr�e la fen�tre qui va contenir le dessin du graphe.

DONNEES : titre : titre de la fen�tre
		  fondCarte : couleur du fond de la sc�ne au formar RGBA
          coinBG : coin Bas Gauche de la sc�ne en coordonn�es monde
          coinHD : coin Haut Droit de la sc�ne en coordonn�es monde
          largeur : largeur de la fen�tre �cran (en pixels)
          hauteur : hauteur de la fen�tre �cran (en pixels)
          font : police � utiliser pour les annotations sur les sommets

*/
    FenetreGrapheSFML (const string &titre,
                       const Vecteur2D &coinBG, const Vecteur2D &coinHD,
                       const unsigned int largeur, const unsigned int hauteur) :
            fenetre(sf::VideoMode(largeur, hauteur), titre)
    {
        fenetre.clear();
// calcul de la transformation affine - changement de rep�re : monde ---> �cran
        Vecteur2D coinEcranBG(0, 0), coinEcranHD(largeur, hauteur);
        t = TransfoAffine2D::passageMondeEcran(coinBG, coinHD, coinEcranBG, coinEcranHD);
    }

/**
Dessine un sommet du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es du sommet sont d�finies par rapport au rep�re du monde
*/
    template<class T>
    bool dessine (const Sommet<T> *sommet);

/**
Dessine un ar�te du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re du monde
*/
    template<class S, class T>
    bool dessine (const Arete<S, T> *arete);

};


/*{
// on va dessiner un rectangle tr�s fin pour repr�senter l'ar�te

Vecteur2D A(arete->debut->v.p), B(arete->fin->v.p);	// {AB] est l'ar�te � repr�senter

A = t.applique(A); B = t.applique(B);		// on passe des coordonn�es monde aux coordonn�es �cran

Vecteur2D u = B-A;

double nU = norme(u);
u /=nU;
Vecteur2D  n = u.rotationDirecteQuartDeTour();

double e = 1;	// �paisseur du rectangle = 2*e. longueur du rectangle == AB

Vecteur2D v = e*n;

Vecteur2D A0= A-v,A1 = B-v, A2 = B+v,A3 = A+v; // on calcule les 4 sommets du rectangle dont l'ar�te [AB] est un axe de sym�trie

Vector2f F0 = vecteur2DToVector2f(A0);
Vector2f F1 = vecteur2DToVector2f(A1);
Vector2f F2 = vecteur2DToVector2f(A2);
Vector2f F3 = vecteur2DToVector2f(A3);

ConvexShape rectangle(4);
rectangle.setPoint(0,F0);
rectangle.setPoint(1,F1);
rectangle.setPoint(2,F2);
rectangle.setPoint(3,F3);

rectangle.setFillColor(Color(arete->v.fond));
fenetre.draw(rectangle);
rectangle.setFillColor(Color(arete->v.devant));
fenetre.draw(rectangle);

return true;
}*/

//---------------------------------------dessine le cas particulier de InfoSommet et InfoArete ------------------------------

/* *
Dessine un sommet du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es du sommet sont d�finies par rapport au rep�re du monde
* /
template <>
bool FenetreGrapheSFML::dessine<InfoSommet>(const Sommet<InfoSommet> * sommet)
{
return dessinePetitRond(this->fenetre, this->t, sommet->v.vSommet, this->font);
}

/ **
Dessine un ar�te du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re du monde
* /
template <>
bool FenetreGrapheSFML::dessine<InfoArete,InfoSommet>(const Arete<InfoArete,InfoSommet> * arete)
{
return dessineSegment( this->fenetre, this->t, arete->v.couleur, arete->debut->v.vSommet.p, arete->fin->v.vSommet.p);
}
*/


//----------------------------------------------------------------------------------



#endif // FENETRE_H
