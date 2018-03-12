//
// Created by alex on 28/02/18.
//
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <chrono>

/*#define LEFT 1
#define RIGHT 0
#define UP 2
#define DOWN 3
#define UPLEFT 4
#define UPRIGHT 5
#define DOWNLEFT 6
#define DOWNRIGHT 7*/

using namespace std;
using namespace sf;

#ifndef TESTANIMATION_ANIMATION_H
#define TESTANIMATION_ANIMATION_H


class Animation
{

private:

    //Vector2U qui fixe une sorte de "tableau" à deux dimensions pour séparer chaque sprite de sa planche
    //X : Nb de sprite pour une animation
    //Y : Nb d'animations sur la planche
    Vector2u _imageCount;

    //Image actuelle
    Vector2u _currentImage;

    //Temps total que met une animation pour se faire
    float _totalTime;

    //Définit le temps que met une image pour se changer. Plus le switchTime est élevé, plus l'animation sera lente
    float _switchTime;


public:


    //Sous rectangle correspondant à un sprite dans la planche
    IntRect _textureRect;

public:
    /**
     *
     * @param textures   : Pointeur vers la planche de texture utilisée pour l'animation
     * @param imageCount : Vector2U qui fixe une sorte de "tableau" à deux dimensions pour séparer chaque sprite de sa planche
     * @param switchTime : Définit le temps que met une image pour se changer. Plus le switchTime est élevé, plus l'animation sera lente
     */
    Animation (Texture *textures, Vector2u imageCount, float switchTime);

    //Animation(Animation &animation);
    /**
     *
     * @param row       : Indique la ligne de la planche correspondant à l'animation désirée
     * @param deltaTime : Temps affichée par le chrono pour faire toutes les instructions de la boucle principale.
     *                    Ce paramètre permet à ce que l'animation soit toujours identique peu importe la machine
     */
    void Update (int row, float deltaTime);
};


#endif //TESTANIMATION_ANIMATION_H
