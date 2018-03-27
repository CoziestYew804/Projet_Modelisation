#include <iostream>
#include "Graphe/Graphe.h"
#include "World/board.h"
#include "Screen/FenetreGrapheSFML.h"
#include "GestionFichier/File.h"
#include "Graphe/Algos.h"
#include "Screen/Menu.h"


using namespace std;
using namespace sf;


int main()
{
    board B;
    //File::Read(B);
    Menu::MenuPrincipal(B);

    Vecteur2D coinBG(-0.5, ((B.listeSommet.size()-1)%5)+0.5);
    Vecteur2D coinHD(((B.listeSommet.size()-1)/5), -0.5);
    FenetreGrapheSFML window("Graphe !", coinBG, coinHD,1920,1080);
    sf::View view(sf::FloatRect(0,0,1920,1080));

// on l'active

    window.fenetre.setView(view);
    //B.graphe.dessine(window);
    //cout << B.graphe << endl;
    //cout << B.aretes[1] << endl;

    //cout << B.graphe << endl;
    //Algos< Graphe<VArete,VSommet>,Sommet<VSommet> >::rechercheCoutUniforme(B.graphe, B.sommets[0]);
    //Algos< Graphe<VArete,VSommet>,Sommet<VSommet> >::Djikstra(B.graphe, B.sommets[0]);
    PElement<Sommet<VSommet>>* ch;
    chemin(OutilsCarte::cible, ch);
    //cout << ch << endl;
    //window.dessineChemin(ch, B.graphe);
    //cout << B.graphe << endl;
    B.graphe.dessine(window);
    window.dessineChemin(ch, B.graphe);
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
            if (event.type == sf::Event::Resized)
            {
                // on met à jour la vue, avec la nouvelle taille de la fenêtre
                //sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                view.zoom(1.5f);
                //window.fenetre.setView(sf::View(visibleArea));

                window.fenetre.clear();
                B.graphe.dessine(window);
                window.dessineChemin(ch, B.graphe);
                window.fenetre.display();
            }
            if(event.type == sf::Event::MouseWheelScrolled)
            {
                if(event.mouseWheelScroll.delta == 1)
                {
                    view.zoom(0.5f);

                    //window.fenetre.setView(sf::View(visibleArea));
                    window.fenetre.clear();
                    window.fenetre.setView(view);
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }
                else if (event.mouseWheelScroll.delta == -1)
                {
                    //view.zoom(2.0f);
                    //window.fenetre.setView(sf::View(visibleArea));
                    view=window.fenetre.getDefaultView();
                    window.fenetre.setView(window.fenetre.getDefaultView());
                    window.fenetre.clear();
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Z)
                {

                    view.zoom(0.5f);

                    //window.fenetre.setView(sf::View(visibleArea));
                    window.fenetre.clear();
                    window.fenetre.setView(view);
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }

                if (event.key.code == sf::Keyboard::X)
                {
                    //view.zoom(2.0f);
                    //window.fenetre.setView(sf::View(visibleArea));
                    view=window.fenetre.getDefaultView();
                    window.fenetre.setView(window.fenetre.getDefaultView());
                    window.fenetre.clear();
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }

                if (event.key.code == sf::Keyboard::Left)
                {
                    view.move(-10,0);

                    //window.fenetre.setView(sf::View(visibleArea));
                    window.fenetre.clear();
                    window.fenetre.setView(view);
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    view.move(0,-10);

                    //window.fenetre.setView(sf::View(visibleArea));
                    window.fenetre.clear();
                    window.fenetre.setView(view);
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    view.move(0,10);

                    //window.fenetre.setView(sf::View(visibleArea));
                    window.fenetre.clear();
                    window.fenetre.setView(view);
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    File::Save(B);
                }

                if (event.key.code == sf::Keyboard::Right)
                {
                    view.move(10,0);

                    //window.fenetre.setView(sf::View(visibleArea));
                    window.fenetre.clear();
                    window.fenetre.setView(view);
                    B.graphe.dessine(window);
                    window.dessineChemin(ch, B.graphe);
                    window.fenetre.display();
                }
            }
        }
    }
    return 0;
}
