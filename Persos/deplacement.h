//
// Created by arnaud on 28/02/18.
//

#ifndef PROJETSFML_PACMAN_DEPLACEMENT_H
#define PROJETSFML_PACMAN_DEPLACEMENT_H


#include <SFML/Window/Keyboard.hpp>
#include "Pacman.h"
#include "../World/board.h"
#include "Fantome.h"
#include <cstdlib>
#include <random>
#include "../Graphe/OutilsCarte.h"
#include "../Graphe/AStar.h"

using namespace sf;

class deplacement
{
private:
    
    static bool deplacementPacman (Pacman &pacman, board &B, int dir, bool sens, TransfoAffine2D &t);
    
    static bool deplacementFantome (Fantome &fantome, Pacman &pacman, board &B, int dir, bool sens, TransfoAffine2D &t);

    
    static bool recherchePacmanParDir (board &B, Pacman &pacman, Sommet<VSommet> *actual, int dir, bool sens);

    
    static bool aVuPacmanParDir (board &B, Fantome &fantome, Pacman &pacman, TransfoAffine2D &t);

    
    static Sommet<VSommet> *recherchePacmanParTemp (board &B, Fantome &fantome);

    
    static bool aVuPacmanParTemp (board &B, Fantome &fantome, Pacman &pacman, TransfoAffine2D &t);
public:
    
    static bool gestionPartie (Pacman &pacman, vector<Fantome*> &fantome, board &B, TransfoAffine2D &t, bool (*lvlFantome)(Fantome &fantome, Pacman &pacman, board &B, TransfoAffine2D &t));
    
    static bool gestionDeplacementFantomeLvl1 (Fantome &fantome, Pacman &pacman, board &B, TransfoAffine2D &t);

    
    static bool gestionDeplacementFantomeLvl2 (Fantome &fantome, Pacman &pacman, board &B, TransfoAffine2D &t);

    
    static bool gestionDeplacementFantomeLvl3 (Fantome &fantome, Pacman &pacman, board &B, TransfoAffine2D &t);
};




#endif //PROJETSFML_PACMAN_DEPLACEMENT_H
