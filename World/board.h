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
    map<string, Sommet<VSommet>*> listeSommet; // map qui contient les sommet par leur nom
    vector<Sommet<VSommet> *> sommets;

    vector<Arete<VArete, VSommet> *> aretes;
    //map<string, Arete<VArete,VSommet>*> aretes; // map qui contient les arcs par leur nom
    int fichierLignes=1;
    std::pair < int, int> pSommet;


    board()
    {
        /*string input = "";
        cout << "veuillez ecrire le nom du fichier a ouvrir:\n>";
        getline(cin, input);
        ifstream fichier("Graphe files/"+input+".gpr", ios::in);  // on ouvre en lecture
        std::pair <  int, int> pArcs;

        if (fichier)  // si l'ouverture a fonctionné
        {
            string line;//contient une ligne du fichier
            int numeroSommet = 0;

            while (getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
            {
                        int len = line.length();
                        vector<string> subArray;

                        for (int j = 0, k = 0; j < len; j++) {
                            if (line[j] ==' ') {
                                string ch = line.substr(k, j - k);
                                k = j + 1;
                                subArray.push_back(ch);
                            }
                            if (j == len - 1) {
                                string ch = line.substr(k, j - k + 1);
                                subArray.push_back(ch);
                            }


                        }
                if(subArray.size()>0)
                {
                    subArray[0].erase(std::remove(subArray[0].begin(), subArray[0].end(), '\r'),
                                      subArray[0].end());
                    cout<<subArray[0]<<endl;
                    cout<<subArray[0].size()<<endl;
                    cout<< !subArray[0].compare("sectionSommets")<<endl;
                    if (!subArray[0].compare("sectionSommets")) {
                        pSommet.first = fichierLignes;
                        cout << subArray[0] << endl;
                        cout << "je l'ai le section sommet" << endl;
                    }
                    if (!subArray[0].compare("sources")) {
                        pSommet.second = fichierLignes - 2;
                        cout<<subArray[0]<<endl;
                        cout << "je l'ai le section source" << endl;
                    }

                    if (!subArray[0].compare("sectionArcs")) {
                        pArcs.first = fichierLignes + 1;
                        cout <<  "arc debut"<< subArray[0] << endl;
                        cout<< fichierLignes<<endl;
                        cout << "je l'ai le section arcs" << endl;
                    }
                    if (!subArray[0].compare("sectionGraphes")) {
                        pArcs.second = fichierLignes - 2;
                        cout << "arc final"<< subArray[0] << endl;
                        cout<< fichierLignes<<endl;
                        cout << "je l'ai le section graphe" << endl;
                    }
                }
                fichierLignes++;
            }
            fichier.close();
        }
        else
        {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }
        ExtractionSommet(pSommet,input);
        ExtractionArc(pArcs,input);
    }

    virtual ~board ()
    = default;

    void ExtractionSommet( pair<int,int>  pSommet, string input ) {

        ifstream fichier("Graphe files/" + input+".gpr", ios::in);
        int num = 0;
        string line;
        int ligne = 0;
        int tempX,tempY;
        if (fichier)  // si l'ouverture a fonctionné
        {
            while (getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
            {
                int len = line.length();
                vector<string> subArray;
                if (ligne >= pSommet.first && ligne < pSommet.second) {


                    for (int j = 0, k = 0; j < len; j++) {
                        if (line[j] ==' ') {
                            string ch = line.substr(k, j - k);
                            k = j + 1;
                            subArray.push_back(ch);
                        }
                        if (j == len - 1) {
                            string ch = line.substr(k, j - k + 1);
                            subArray.push_back(ch);
                        }

                    }

                    cout << "taille "<< subArray.size()<<endl;
                    int max=(pSommet.first-ligne)*-1;
                    listeSommet[subArray[0]]=graphe.creeSommet(VSommet(Vecteur2D(max/5, max%5),subArray[0],stoi(subArray[2]),stoi(subArray[4])));
                    listeSommet[subArray[0]]->v.getInfoAlgo().num = ++num;
                    cout<<"le nom du bordSup : " <<subArray[2]<<endl;

                    sommets.push_back(listeSommet[subArray[0]]);
                }
                ligne++;
            }
            fichier.close();
        } else {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }
    }
    void ExtractionArc( pair<int,int>  pArcs, string input ) {
        ifstream fichier("Graphe files/" + input+".gpr", ios::in);
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
                    aretes.push_back(graphe.creeArete(VArete(subArray[0],stoi(subArray[8]), stoi(subArray[6])), listeSommet[subArray[2]], listeSommet[subArray[4]]));
                    //cout << aretes.back()->v << endl;
                }
                ligne++;
            }
            fichier.close();
        } else {

            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }*/
    }
};


#endif //PROJETSFML_PACMAN_BOARD_H
