#pragma once

#include "../Screen/AlgebreLineaire.h"
#include "Sommet.h"
#include "VSommet.h"
#include "VArete.h"

#include "Arete.h"

#include "Graphe.h"

using namespace std;

//#include "AStarT.h"

/**
sert d'intermédiaire entre A* et une carte routière. Définit pour une carte routière, toutes les méthodes que
réclame l'algo A*.
L'information inscrite dans une arête est une VArete qui contient une couleur et la longueur de l'arête
L'information inscrite dans un sommet est une VSommet qui contient 2 attributs : VSommet et InfoAStar.

Par conséquent :

Une carte routière est un Graphe <VArete, VSommet >

A savoir, A* réclame les méthodes suivantes :

libereToutSommet(graphe) : met l'état de tous les sommets à LIBRE et tous les liens père à NULL
listeVoisins(sommet,graphe) : renvoie une liste de paires (voisin, coût entre sommet et voisin)
pere(sommet)
etat(sommet)
c(sommet)
g(sommet)
h(sommet)
estFinal(sommet)

*/


class OutilsCarte
{
public:
static double distance( const Sommet<VSommet> * s1, const Sommet<VSommet> * s2);
static Arete<VArete, VSommet> *  creeArete(Sommet<VSommet> * sA, Sommet<VSommet> * sB,Graphe<VArete, VSommet> & graphe);
static void libereToutSommet(Graphe<VArete, VSommet> & graphe);
static double hh(const Sommet<VSommet> * s);
static PElement< pair<Sommet<VSommet>*,double> > * listeVoisins(const Sommet<VSommet> * s, const Graphe<VArete, VSommet> & graphe);

static Sommet<VSommet> *  pere( const Sommet<VSommet> * sommet);
static Sommet<VSommet> * & pere( Sommet<VSommet> * sommet);
static int & etat( Sommet<VSommet> * sommet);
static double & c( Sommet<VSommet> * sommet);
static double & h( Sommet<VSommet> * sommet);
static double g( const Sommet<VSommet> * sommet);
static double & g( Sommet<VSommet> * sommet);

static bool estFinal(const Sommet<VSommet> * sommet);

static Sommet<VSommet> * cible;
};

void libereToutSommet(Graphe<VArete, VSommet> & graphe);
PElement< pair<Sommet<VSommet>*,double> > * listeVoisins(const Sommet<VSommet> * s, const Graphe<VArete, VSommet> & graphe);

Sommet<VSommet> *  pere( const Sommet<VSommet> * sommet);
Sommet<VSommet> * & pere( Sommet<VSommet> * sommet);
int & etat( Sommet<VSommet> * sommet);
double & c( Sommet<VSommet> * sommet);
double & h( Sommet<VSommet> * sommet);
double g( const Sommet<VSommet> * sommet);
double & g( Sommet<VSommet> * sommet);

bool estFinal(const Sommet<VSommet> * sommet);


/**
compte le nombre de maillons de la liste chaînée "pere" dont le maillon de tête est "tête".
*/
int longueurChemin(const Sommet<VSommet>* tete);

const Sommet<VSommet> * dernierMaillon(const Sommet<VSommet>* tete);
