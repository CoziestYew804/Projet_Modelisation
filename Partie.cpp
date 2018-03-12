//
// Created by alex on 10/03/18.
//

#include "Partie.h"
#include "Persos/Pacman.h"
#include "Persos/Fantome.h"
#include "Persos/deplacement.h"
#include <SFML/Audio.hpp>

/*
Partie::pacman;
Partie::fantome1;
Partie::fantome2;
Partie::fantome3;
*/




Partie::Partie()
        {
  cout << "lol je marche pas"<<endl;

}

Partie::~Partie() {

}

Partie &Partie::Instance() {
    static Partie p_instance = Partie();
    return p_instance;
}

void Partie::lancerPartie(FenetreGrapheSFML &window,board &B) {

    Font font;
    cout<< "ok mais bon"<< endl;


    if (!font.loadFromFile("KINKEE.TTF"))
    {
        throw ("Erreur lors du chargement de la police du score");
    }

    srand(static_cast<unsigned int>(time(NULL)));
    float deltatime;
    Clock clock;



        //window.fenetre.clear();
        B.graphe.dessine(window);
        //window.fenetre.draw(gameOver);
        window.fenetre.display();



}


