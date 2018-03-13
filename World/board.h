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
    map<string, Sommet<VSommet>*> listeSommet;
    vector<Sommet<VSommet> *> sommets;
    vector<Arete<VArete, VSommet> *> aretes;
    std::vector<std::vector<std::pair <  int, int>>> graph = std::vector<std::vector<std::pair < int, int>>> (24);

    int score;

    board()
    {
        string input = "";
        cout << "veuillez ecrire le nom du fichier a ouvrir:\n>";
        getline(cin, input);
        ifstream fichier("Graphe files/"+input, ios::in);  // on ouvre en lecture
        std::pair <  int, int> pSommet;
        std::pair <  int, int> pArcs;
        if (fichier)  // si l'ouverture a fonctionné
        {
            string line;
            int numeroSommet = 0;
            int ligne=1;
            //bool pSommet;
            while (getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
            {
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
                if(subArray.size()>0) {
                    if (!subArray[0].compare("sectionSommets")) {
                        pSommet.first = ligne;
                        cout << subArray[0] << endl;
                    }
                    if (!subArray[0].compare("sources")) {
                        pSommet.second = ligne - 2;
                        cout<<subArray[0]<<endl;

                    }

                    if (!subArray[0].compare("sectionArcs")) {
                        pArcs.first = ligne + 1;
                        cout <<  "arc debut"<< subArray[0] << endl;
                        cout<< ligne<<endl;
                    }
                    if (!subArray[0].compare("sectionGraphes")) {
                        pArcs.second = ligne - 2;
                        cout << "arc final"<< subArray[0] << endl;
                        cout<< ligne<<endl;
                    }
                }


                     ligne++;


            }


            fichier.close();
        } else {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }


        ExtractionSommet(pSommet,input);
        ExtractionArc(pArcs,input);


    }

    virtual ~board ()
    = default;

    void ExtractionSommet( pair<int,int>  pSommet, string input ) {

        ifstream fichier("Graphe files/" + input, ios::in);

        string line;
        int ligne = 0;
        if (fichier)  // si l'ouverture a fonctionné
        {
            while (getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
            {

                int len = line.length();
                vector<string> subArray;
                if (ligne >= pSommet.first && ligne < pSommet.second) {


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
                    //cout << "taille ligne "<< ligne << " vediamo : " << subArray.size()<< endl;
                    cout << stoi(subArray[2]) << " , " << subArray[4] << endl;
                    listeSommet[subArray[0]]=graphe.creeSommet(VSommet(Vecteur2D(stoi(subArray[2]), stoi(subArray[4]))));
                    sommets.push_back(listeSommet[subArray[0]]);
                    //cout << stoi(subArray[subArray.size()-1]);
                }

                ligne++;


            }


            fichier.close();
        } else {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }

    }
    void ExtractionArc( pair<int,int>  pArcs, string input ) {
        cout<<"je suis dans extraction arcs"<<endl;
        ifstream fichier("Graphe files/" + input, ios::in);
        string line;
        int ligne = 0;
        cout<<pArcs.first<< ","<< pArcs.second<<endl;
        if (fichier)  // si l'ouverture a fonctionné
        {
            while (getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
            {

                int len = line.length();
                vector<string> subArray;

                if (ligne >= pArcs.first && ligne < pArcs.second) {
                    cout << "oui c est bon"<<endl;
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

                    cout << (subArray[2]) << " , " << subArray[4] << endl;
                    aretes.push_back(graphe.creeArete(-2, listeSommet[subArray[2]], listeSommet[subArray[4]]));

                }

                ligne++;


            }



            fichier.close();

        } else {

            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }

    }


};


#endif //PROJETSFML_PACMAN_BOARD_H
