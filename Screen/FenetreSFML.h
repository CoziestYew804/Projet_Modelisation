//
// Created by arnaud on 22/01/18.
//

#ifndef GRAPHES_FENETRESFML_H
#define GRAPHES_FENETRESFML_H

#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../Graphe/Graphe.h"

using namespace sf;

template<class S, class T>
class FenetreSFML:public RenderWindow
{
public:
    FenetreSFML<S, T>(unsigned int width, unsigned int height, string name):RenderWindow(VideoMode(width, height), name){}
    FenetreSFML<S, T>(FenetreSFML &f):RenderWindow(f){}
    bool dessine(Arete<S, T> *arete);
    bool dessine(Sommet<T> *sommet);

};

template<class S, class T>
bool FenetreSFML<S, T>::dessine(Arete<S, T> *arete)
{

    int x1 = 100+100*(arete->debut->clef / 5), y1 = 100+100*(arete->debut->clef % 5), x2 = 100+100*(arete->fin->clef / 5), y2 = 100+100*(arete->fin->clef % 5);
    RectangleShape A(Vector2f(20, (float)(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)))-30));
    int temp = arete->v.getTemp();
    if(temp == 0)
        A.setOutlineColor(Color::Cyan);
    else if(temp == 1)
        A.setOutlineColor(Color::Magenta);
    else if(temp == 2)
        A.setOutlineColor(Color::Yellow);
    else if(temp == 3)
        A.setOutlineColor(Color(237, 127, 16));
    else if(temp == 4)
        A.setOutlineColor(Color::Red);
    A.setOutlineThickness(8);
    A.setFillColor(Color::Black);
    int dir = arete->v.getDir();
    A.rotate(45*dir);
    if (dir == 0)
        A.setPosition(x1-10, y1);
    else if (dir == -3)
        A.setPosition(x1, y1+15);
    else if (dir == -2)
        A.setPosition(x1, y1+10);
    else if (dir == -1)
        A.setPosition(x1-15, y1);
    draw(A);
    return true;
}

template<class S, class T>
bool FenetreSFML<S, T>::dessine(Sommet<T> *sommet)
{
    CircleShape C(2, 30);
    //C.setPosition((100*(sommet->clef / 5))-C.getRadius()+100, 100*((sommet->clef % 5))-C.getRadius()+100);
    C.setPosition(sommet->v.getPosition());
    C.setOutlineThickness(2);
    C.setOutlineColor(Color::Cyan);
    C.setFillColor(Color::Black);
    draw(C);
    return true;
}


#endif //GRAPHES_FENETRESFML_H
