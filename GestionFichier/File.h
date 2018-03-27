//
// Created by GioUniversita on 16/03/18.
//

#ifndef PROJETSFML_PACMAN_CREATEFILE_H
#define PROJETSFML_PACMAN_CREATEFILE_H

#include <iostream>
#include "../Graphe/Graphe.h"
#include "../Screen/Vecteur2D.h"
#include "../World/board.h"

class File {

public:
    static void Save(board &B){

        string nom = "";
        cout << "veuillez ecrire le nom du fichier a ouvrir:\n>";
        cin.ignore();
        getline(cin, nom);

        fstream file;
        file.open("Graphe files/"+nom+".gpr", ios::out|ios::in);//Attempt to open file.
        if(file.is_open())
        {
            cerr<<"Le fichier que vous souhaitez creer existe deja \n";

        }
        else
        {
            cout<<"Writing\n";
            file.open("Graphe files/"+nom+".gpr", ios::out|ios::in|ios::trunc);//TRUNCATING to make new file!

            file<<"# Graphe N = "<< B.listeSommet.size() << " M = " << B.aretes.size()<<endl;
            file<<endl;
            file<<"ressources 1 "<<endl;
            file<<endl;
            file<<"sectionSommets "<<endl;
            for(int i=0;i<B.sommets.size();i++){
                file<<B.sommets[i]->v.nom<<"  "<<B.sommets[i]->v.bordInf<<"  "<<B.sommets[i]->v.bordSup<<endl;
            }
            file<<endl;
            file<<"sources"<<endl;
            file<<B.sommets[0]->v.nom<<"  "<<B.sommets[0]->v.bordInf<<"  "<<B.sommets[0]->v.bordSup<<endl;
            file<<endl;
            file<<"puits"<<endl;
            file<<B.sommets[B.sommets.size()-1]->v.nom<<"  "<<B.sommets[B.sommets.size()-1]->v.bordInf<<"  "<<B.sommets[B.sommets.size()-1]->v.bordSup<<endl;
            file<<endl;
            file<<"sectionArcs "<<endl;
            for(int i=0;i<B.aretes.size();i++){

                file<<B.aretes[i]->v.nom<<"  "<<B.aretes[i]->debut->v.nom<<"  "<<B.aretes[i]->fin->v.nom<<"  "<<B.aretes[i]->v.getInfoAlgo().c<<"  "<<B.aretes[i]->v.getDuree()<<endl;
            }
            file<<endl;
            file<<"sectionGraphes"<<endl;
            file<<endl;
            file<<nom<<"  "<< B.sommets[0]->v.nom<< "  " <<B.sommets[B.sommets.size()-1]->v.nom <<endl;
            file<<endl;
            cout<< "finished"<<endl;
        }
        file.close();//File must be properly closed if opened! Else issues may arise.


    }

    static void Read(board &B)
    {
        string input = "";
        cout << "veuillez ecrire le nom du fichier a ouvrir:\n>";
        getline(cin, input);
        ifstream fichier("Graphe files/"+input+".gpr", ios::in);  // on ouvre en lecture
        std::pair <  int, int> pArcs;
        std::pair <  int,  int> fPuits;
        int lignePuits;

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
                    subArray[0].erase(std::remove(subArray[0].begin(), subArray[0].end(), '\r'), subArray[0].end());
                    if (!subArray[0].compare("sectionSommets")) {
                        B.pSommet.first = B.fichierLignes;
                        //cout << subArray[0] << endl;
                    }
                    if (!subArray[0].compare("sources")) {
                        B.pSommet.second = B.fichierLignes - 2;
                        //cout<<subArray[0]<<endl;
                    }

                    if (!subArray[0].compare("sectionArcs")) {
                        pArcs.first = B.fichierLignes ;
                        //cout <<  "arc debut"<< subArray[0] << endl;
                        //cout<< B.fichierLignes<<endl;
                    }
                    if (!subArray[0].compare("sectionGraphes")) {
                        pArcs.second = B.fichierLignes - 2;
                        //cout << "arc final"<< subArray[0] << endl;
                        //cout<< B.fichierLignes<<endl;
                    }
                    if (!subArray[0].compare("puits")) {
                        lignePuits = B.fichierLignes + 1;
                    }
                    if (B.fichierLignes== lignePuits) {
                        int x;
                        int y;
                        for(int i=1; i<subArray.size();i++){
                            if(is_number(subArray[i])){
                                if(x!=-1){
                                    y=stoi(subArray[i]);
                                }
                                else{
                                    x=stoi(subArray[i]);
                                }
                            }
                        }

                        fPuits.first = x;
                        fPuits.second = y;
                        //cout << " 1 " << subArray[1] << " 2 " << stoi(subArray[2]) << " 4 " << stoi(subArray[4]) << endl;
                    }

                        //cout << "arc final"<< subArray[0] << endl;
                        //cout<< B.fichierLignes<<endl;

                }
                B.fichierLignes++;
            }
            fichier.close();
        }
        else
        {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }
        ExtractionSommet(B.pSommet,input, B,fPuits);
        ExtractionArc(pArcs,input, B);
    }

    static void ExtractionSommet( pair<int,int>  pSommet, string input, board &B, pair<int,int> fPuits) {

        ifstream fichier("Graphe files/"+input+".gpr", ios::in);

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
                    int max=(pSommet.first-ligne)*-1;
                    if(subArray.size()==1){
                        B.listeSommet[subArray[0]]=B.graphe.creeSommet(VSommet(Vecteur2D(max/5, max%5),subArray[0],fPuits.first,fPuits.second));
                    }
                    else {
                        //cout<<"a"<<subArray[2]<<"a"<<endl;
                        int k=0;
                        int x=-1;
                        int y=-1;
                        for(int i=1; i<subArray.size();i++){
                            if(is_number(subArray[i])){
                               if(x!=-1){
                                   y=stoi(subArray[i]);
                               }
                                else{
                                   x=stoi(subArray[i]);
                               }
                            }
                        }
                        B.listeSommet[subArray[0]] = B.graphe.creeSommet(
                                VSommet(Vecteur2D(max / 5, max % 5), subArray[0], x, y));
                    }

                    B.sommets.push_back(B.listeSommet[subArray[0]]);
                }
                ligne++;
            }

            fichier.close();
        } else {

           cerr<<"Impossible d'ouvrir le fichier !" << endl;
        }
    }
    static void ExtractionArc( pair<int,int>  pArcs, string input, board &B) {
        ifstream fichier("Graphe files/"+input+".gpr", ios::in);
        string line;
        int ligne = 0;
        //cout<<pArcs.first<< ","<< pArcs.second<<endl;
        if (fichier)  // si l'ouverture a fonctionné
        {
            while (getline(fichier, line))  // tant que l'on peut mettre la ligne dans "contenu"
            {

                int len = line.length();
                vector<string> subArray;

                if (ligne >= pArcs.first && ligne < pArcs.second) {
                    for (int j = 0, k = 0; j < len; j++) {
                        /*if (line[j] =='  ') {
                            string ch = line.substr(k, j - k);
                            k = j + 1;
                            subArray.push_back(ch);
                        }*/
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

                    B.aretes.push_back(B.graphe.creeArete(VArete(subArray[0],stoi(subArray[8]), stoi(subArray[6])), B.listeSommet[subArray[2]], B.listeSommet[subArray[4]]));
                    if(stoi(subArray[6])<0){B.graphe.setEstPossibleDjikstra(false);}
                    //cout <<  stoi(subArray[2].substr(1))<<endl;
                    //cout << subArray[4].substr(1)<<endl;
                    //B.adj[stoi(subArray[2].substr(1))].push_back(stoi(subArray[4].substr(1)));
                }
                ligne++;
            }
            fichier.close();
        } else {

            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }
    }
    static bool is_number( std::string s)
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }

};


#endif //PROJETSFML_PACMAN_CREATEFILE_H
