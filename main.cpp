
#include <iostream>
#include "Graphe/Graphe.h"
#include "Screen/Vecteur2D.h"
#include "World/board.h"
#include "Screen/FenetreGrapheSFML.h"


using namespace std;
using namespace sf;


int main()
{

    board B;
    //Vecteur2D coinBG(-2,B.coordMax.second);
    //Vecteur2D coinHD(B.coordMax.first,-2);
    Vecteur2D coinBG(-1, -1);
    Vecteur2D coinHD(5, 5);
    FenetreGrapheSFML window("Graphe !", coinBG, coinHD, 1920,1080);



    B.graphe.dessine(window);
    //window.fenetre.draw(gameOver);
    window.fenetre.display();

    while (window.fenetre.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.fenetre.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.fenetre.close();
        }

    }








    return 0;





}
