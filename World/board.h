//
// Created by arnaud on 27/02/18.
//

#ifndef PROJETSFML_PACMAN_BOARD_H
#define PROJETSFML_PACMAN_BOARD_H

#include "../Graphe/Graphe.h"
#include "../Graphe/Arete.h"
#include "../Graphe/VSommet.h"
#include "../Graphe/VArete.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>




class board
{
public:
    Graphe<VArete, VSommet> graphe;
    map<string, int> listeSommet;
    vector<Sommet<VSommet> *> sommets;
    vector<Arete<VArete, VSommet> *> aretes;
    std::vector<std::vector<std::pair <  int, int>>> graph = std::vector<std::vector<std::pair < int, int>>> (24);

    int score;

    board()
    {
        /*for (unsigned int i = 0; i < 25; i++)
        {
            sommets.push_back(graphe.creeSommet(VSommet(Vecteur2D(i / 5, i % 5))));
        }*/

        ifstream fichier("Graphe files/data_VRPTW_10_3_2_4.gpr", ios::in);  // on ouvre en lecture

        if (fichier)  // si l'ouverture a fonctionné
        {
            string line;
            int numeroSommet = 0;
            int ligne=1;
            while (getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
            {

                if ((ligne>5)&&(ligne < 16)) {

                        int len = line.length();
                        vector<string> subArray;

                        for (int j = 0, k = 0; j < len; j++) {
                            if (line[j] == ' ') {
                                string ch = line.substr(k, j - k);
                                k = j + 1;
                                subArray.push_back(ch);
                            }
                            if (j == len - 1) {
                                string ch = line.substr(k, j - k + 1);
                                subArray.push_back(ch);
                            }

                        }
                        //cout<<subArray.size()<<endl;
                        cout << "taille ligne "<< ligne << " vediamo : " << subArray.size()<< endl;
                        cout<<stoi(subArray[2])<<" , " << subArray[4]<<endl;
                        sommets.push_back(graphe.creeSommet(VSommet(Vecteur2D(stoi(subArray[2]), stoi(subArray[4])))));
                        //cout << stoi(subArray[subArray.size()-1]);


                    } ligne++;


            }

                /*for (int i = 0; i < subArray.size(); i = i + 2) {
                    //graph[numeroSommet].push_back(make_pair(stoi(subArray[i]),stoi(subArray[i+1])));
                    sommets.push_back(graphe.creeSommet(VSommet(Vecteur2D(i / 5, i % 5))));

                }*/

                //numeroSommet++;

                //cout<<line<<endl;


            fichier.close();
        } else {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }


        /*for(int i=0; i<24; i++){
            for(int j=0; j<graph[i].size(); j++) {
                aretes.push_back(graphe.creeArete(graph[i][j].first, sommets[i], sommets[graph[i][j].second]));
            }
        }*/




    }

    virtual ~board ()
    = default;

    void refroiditToutesAretes()
    {
        for(unsigned int i = 0; i < aretes.size(); i++)
        {
            aretes[i]->v.operator--();
        }
    }

    bool aMangayTouteGommes() const
    {
        for (Sommet<VSommet> * s: sommets)
        {
            if (s->v.isGom()) return false;
        }
        return true;
    }

    void reinitialiserGommes()
    {
        for (Sommet<VSommet> * s: sommets)
        {
            s->v.setGom(true);
        }
    }

    void incrementScore()
    {
        score = (score / 2500) * 2500;
        if(score == 1)
            score = 0;

        for (Sommet<VSommet> * s: sommets)
        {
            score+=100 * (!s->v.isGom());
        }
    }


};


#endif //PROJETSFML_PACMAN_BOARD_H
