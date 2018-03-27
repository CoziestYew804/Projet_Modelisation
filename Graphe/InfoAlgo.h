#pragma once

#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

#include "AElement.h"

using namespace std;

/**
Le déroulement correct de A* nécessite que l'information suivante soit associée à tout Sommet
*/

//#define LIBRE 0
//#define OUVERT 1
//#define FERME 2

constexpr int LIBRE = 0;
constexpr int OUVERT = 1;
constexpr int FERME = 2;


class InfoAlgo
{
public:
const static char *ETATS []; // = {"LIBRE","OUVERT","FERME"};

AElement * pere;	// pointeur sur un Sommet<?>. où ? est une classe composée ou dérivée de InfoStar
int etat;		// LIBRE, OUVERT ou FERMé
double c;		// coût déjà calculé. cf. A* ou Dijkstra
double h;		// estimation heuristique. cf. A*
double g;		// coût total : g = h+c
int num;

    explicit InfoAlgo (int num = 0, const double & c = 0, AElement *pere = nullptr, const int etat = LIBRE,
                         const double & h = 0, const double & g = 0) :
		   	pere(pere), etat(etat), c(c), h(h), g(g), num(0) {}

    explicit operator string () const;

friend ostream & operator << ( ostream & os, const InfoAlgo & InfoAlgo) { return os << (string)InfoAlgo; }
};


