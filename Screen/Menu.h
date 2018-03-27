//
// Created by alex on 19/03/18.
//

#ifndef PROJETSFML_PACMAN_MENU_H
#define PROJETSFML_PACMAN_MENU_H


#include "../World/board.h"
#include "../GestionFichier/File.h"
#include "../Graphe/OutilsCarte.h"
#include "../Graphe/Algos.h"

class Menu
{
public:
    static void MenuAlgo(int arg, board &B)
    {
        string choix1;
        string choix2;
        cout << "Choisissez le numero du premier sommet (i+numero): ";
        cin >> choix1;
        cout << endl <<"Choisissez le numero du deuxième sommet (i+numero):";
        cin >> choix2;
        Sommet<VSommet> * resultat;
        Sommet<VSommet> * s1;
        Sommet<VSommet> * s2;
        if(choix1.empty() && choix2.empty())
        {

            s1 = B.sommets.front();
            s2 = B.sommets.back();
        }
        else
        {
            s1 = B.listeSommet[choix1];
            s2 = B.listeSommet[choix2];
        }

        switch(arg)
        {
            case 1:
            {
                OutilsCarte::cible = s2;
                cout << "AStar ;" << endl;
                resultat = Algos<Graphe<VArete, VSommet>, Sommet<VSommet> >::aStar(B.graphe, s1, OutilsCarte::hh);
                if(!resultat) throw("Chemin astar non trouve");
                PElement<Sommet<VSommet>> * c;
                chemin(s2,c);
                break;
            }
            case 2:
            {
                OutilsCarte::cible = s2;
                cout << "Dijkstra ;" << endl;
                resultat = Algos< Graphe<VArete,VSommet>,Sommet<VSommet> >::Djikstra( B.graphe, s1);
                if(!resultat) throw("Chemin astar non trouve");
                PElement<Sommet<VSommet>> * c;
                chemin(s2,c);
                break;
            }
            case 3:
            {
                OutilsCarte::cible = s2;
                cout << "Connexité entre les deux sommets : " << ExisteUnChemin(B.graphe, s1, s2) << endl;
                break;
            }
            case 4:
            {
                cout << "Parcours DFS ;" << endl;
                parcoursDFS(B.graphe, s1);
                break;
            }
            case 5:
            {
                cout << "Numérotation du graphe ;" << endl;
                NumeroteGraphe(B.graphe,s1);
                break;
            }
            case 6:
            {
                cout << "Tri topologique ;" << endl;
                if(!B.graphe.isCyclic()) {
                    vector<Sommet<VSommet> *> tri;
                    PElement<Sommet<VSommet>> *ls = B.graphe.lSommets;
                    while (ls != NULL) {
                        tri.push_back(ls->valeur);
                        ls = ls->suivant;
                    }
                    TriTopologique(B.graphe, tri, B.aretes);
                }
                else{
                    cerr<< " le graphe a un cycle il n'est donc pas possible d'effectuer le tri topologique"<<endl;
                }
                break;
            }

        }


    }
    static void MenuPrincipal(board &B)
    {
            int choix;
            File::Read(B);
            cout << "Que voulez vous faire avec ce graphe ?" << endl;


            cout << endl << "\t\tCONSULTATION/MANIPULATION DU GRAPHE" << endl << endl;


            cout << "1  - Astar entre deux sommets" << endl;
            cout << "2  - Dijkstra entre deux sommets" << endl;
            cout << "3  - Vérifier la connexité entre deux sommets" << endl;
            cout << "4  - Parcours DFS " << endl;
            cout << "5  - Numéroter les sommets" << endl;
            cout << "6  - Tri topologique" << endl;
            cout << "7  - Vérifie la présence de circuit" << endl;

            cout << endl << "\t\tMANIPULATION DE FICHIER" << endl << endl;


            cout << "9  - Sauvegarder le graphe " << endl;
            cout << "10 - Charger un autre fichier gpr" << endl;

            cout << endl << "\t\tAUTRE" << endl << endl;

            cout << "11 - Afficher le graphe" << endl;
            cout << "0 - Quitter le logiciel" << endl << endl;

            cout << "Votre choix : ";
            cin >> choix;

            if (choix >= 1 && choix <= 7) {
                MenuAlgo(choix, B);
            } else {
                switch (choix) {
                    case 0:
                        exit (EXIT_SUCCESS);
                    case 9:
                    {
                        File::Save(B);
                        break;
                    }
                    case 10:
                    {
                        File::Read(B);
                        break;
                    }
                    case 11:
                        break;
                    default :
                        cout << "Erreur de frappe !" << endl;
                }
            }

    }
};


#endif //PROJETSFML_PACMAN_MENU_H
