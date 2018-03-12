//
// Created by arnaud on 22/01/18.
//

#ifndef GRAPHES_RenderTexture_H
#define GRAPHES_RenderTexture_H

#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../Graphe/Graphe.h"

using namespace sf;

template<class S, class T>
class backgroundRender:public RenderTexture
{
private:
    unsigned int width{}, height{};
    bool depthBuffer{};
public:
    backgroundRender<S, T>(unsigned int width, unsigned int height, bool depthBuffer=false);
    backgroundRender<S, T>(backgroundRender &bR);

    virtual ~backgroundRender ();

    bool dessine(Arete<S, T> *arete);
    bool dessine(Sommet<T> *sommet);

};

template<class S, class T>
backgroundRender<S, T>::backgroundRender(unsigned int width, unsigned int height, bool depthBuffer)
        :RenderTexture(), width(width), height(height), depthBuffer(depthBuffer)
{
    this->create(width, height, depthBuffer);
}

template<class S, class T>
backgroundRender<S, T>::backgroundRender(backgroundRender &bR):RenderTexture()
{
    this->create(bR.width, bR.height, bR.depthBuffer);
}

template<class S, class T>
bool backgroundRender<S, T>::dessine(Arete<S, T> *arete)
{
    int x1 = 100+100*(arete->debut->clef / 5), y1 = 100+100*(arete->debut->clef % 5), x2 = 100+100*(arete->fin->clef / 5), y2 = 100+100*(arete->fin->clef % 5);
    RectangleShape A(Vector2f(20, (float)sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))));
    A.setOutlineColor(Color::Cyan);
    A.setOutlineThickness(8);
    A.setFillColor(Color::Black);
    int sens = arete->v.getSens1();
    A.rotate(45*sens);
    if (sens== 0)
        A.setPosition(x1-10, y1);
    else if (sens == -3)
        A.setPosition(x1, y1+15);
    else if (sens == -2)
        A.setPosition(x1, y1+10);
    else if (sens == -1)
        A.setPosition(x1-15, y1);
    draw(A);
    return true;
}

template<class S, class T>
bool backgroundRender<S, T>::dessine(Sommet<T> *sommet)
{
    CircleShape C(30, 100);
    //C.setPosition((100*(sommet->clef / 5))-C.getRadius()+100, 100*((sommet->clef % 5))-C.getRadius()+100);
    C.setPosition(sommet->v.getPosition());
    C.setOutlineThickness(10);
    C.setOutlineColor(Color::Cyan);
    C.setFillColor(Color::Black);
    draw(C);
    return true;
}

template<class S, class T>
backgroundRender<S, T>::~backgroundRender ()
{};


#endif //GRAPHES_RenderTexture_H
