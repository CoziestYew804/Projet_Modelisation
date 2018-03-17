//
// Created by GioUniversita on 16/03/18.
//

#ifndef PROJETSFML_PACMAN_CREATEFILE_H
#define PROJETSFML_PACMAN_CREATEFILE_H

#include <iostream>
#include "../Graphe/Graphe.h"
#include "../Screen/Vecteur2D.h"
#include "../World/board.h"

class CreateFile {

public:
    CreateFile(board &B){

        string nom = "";
        cout << "veuillez ecrire le nom du fichier a ouvrir:\n>";
        getline(cin, nom);

        fstream file;
        file.open(nom+".gpr", ios::out|ios::in);//Attempt to open file.
        if(file.is_open())
        {
            cout<<"Le fichier que vous souhaitez creer existe deja espece d'abruti\n";

        }
        else
        {
            cout<<"Writing\n";
            file.open(nom+".gpr", ios::out|ios::in|ios::trunc);//TRUNCATING to make new file!

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









        }
        file.close();//File must be properly closed if opened! Else issues may arise.


    }

};


#endif //PROJETSFML_PACMAN_CREATEFILE_H
