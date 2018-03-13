
#include <iostream>
#include "Graphe/Graphe.h"
#include "Screen/Vecteur2D.h"
#include "World/board.h"
#include "Screen/FenetreGrapheSFML.h"


using namespace std;
using namespace sf;


int main()
{
    Vecteur2D coinBG(0, -15);
    Vecteur2D coinHD(0, 100);
    board B;
    FenetreGrapheSFML window("PacmanSFML !", coinBG, coinHD, 1280,720);



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
