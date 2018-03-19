//
// Created by alex on 16/03/18.
//

#ifndef PROJETSFML_PACMAN_ALGOS_H
#define PROJETSFML_PACMAN_ALGOS_H



#pragma once
#include <utility>

#include"PElement.h"
#include "OutilsCarte.h"

/**
suppose que pour tout s sommet de graphe, on a:
s.etat = LIBRE

suppose que les fonctions coût et  h sont toujours >= 0
*/

template <class Graphe, class Sommet>
class Algos
{
public:
    static bool estPlusPetitOuEgal(const Sommet * sommet1, const Sommet * sommet2)
    {
        return g(sommet1) <= g(sommet2);
    }



/**

recherche  dans graphe le plus court chemin de départ à cible par l'algo A*.
en cas de succès, les liens "père" des sommets indiquent le chemin à suivre en partant de cible vers départ.
le père de départ vaut toujours NULL en sortie (c'est la racine du chemin ou bien encore la fin de la liste chaînée "père")

retourne vrai si succès et faux si échec

suppose que tout sommet s du graphe
dispose des attributs suivants publics :
int etat (peut prendre l'une des 3 valeurs suivantes : LIBRE, OUVERT ou FERMé)
pere : Sommet * pere
double c;		// coût réel entre départ et s
double h;		// estimation du coût entre s et cible
double g;		// g == c+h

suppose que la méthode listeVoisins(sommet,graphe) retourne la liste des paires (voisin, coût de l'arête sommet-voisin)

hh est l'heuristique à appliquer entre 2 sommets quelconques du graphe

*/
    static bool aStar1Cible(Graphe & graphe, Sommet * depart, Sommet * cible,
                            double (*hh)(const Sommet * s1, const Sommet * s2)/*,
			PElement< pair<Sommet*,double> > * (*listeVoisins)(const Sommet * s, const Graphe & graphe),
			void (*libereToutSommet)(Graphe & graphe)*/)
    {
        libereToutSommet(graphe); // met tous les sommets du graphe à LIBRE et tous les liens-pere à NULL
        PElement<Sommet> * Ouverts;

        pere(depart) = NULL; c(depart) = 0; // depart->h = h(depart,cible); depart->g = depart->c + depart->h; // ces 2 dernières affectations sont inutiles

        Ouverts = new PElement<Sommet>(depart,NULL); etat(depart) = OUVERT;

        while(Ouverts)
        {
            Sommet  * s =PElement<Sommet>::depiler(Ouverts); etat(s) = FERME;

            if (s == cible) { PElement<Sommet>::efface1(Ouverts); return true;}

            PElement< pair<Sommet*,double> > * listeDesVoisins = listeVoisins(s, graphe);
            PElement< pair<Sommet*,double> > * l;

            for( l = listeDesVoisins; l; l = l->suivant)		// on parcourt les voisins de s
            {
                Sommet * v = l->valeur->first;	// v est le voisin courant de s

                double nouveauCout = c(s) + l->valeur->second;			//l->valeur->second est le coût de l'arête s - v

                if (etat(v) == LIBRE)
                {
                    h(v) = hh(v,cible);
                    miseAJourVoisin( v, s, nouveauCout, Ouverts);
                }
                else			// v est Fermé ou Ouvert

                if ( nouveauCout < c(v))
                {
                    if (etat(v) == OUVERT)
                        PElement< Sommet>::retire(v,Ouverts);

                    miseAJourVoisin( v, s, nouveauCout, Ouverts);

                }				// if (nouveauCout < v->c)
            }			// for

            PElement< pair<Sommet*,double> >::efface2(listeDesVoisins);
        }	// while (Ouverts)

        return false; // échec

    }	// aStar1Cible

/**
 * Recherche  dans graphe le plus court chemin de départ à un état final par l'algo de Dijkstra.
 * en cas de succès, les liens "père" des sommets indiquent le chemin à suivre en partant du sommet-cible trouvé vers départ.
 * le père de départ vaut toujours NULL en sortie (c'est la racine du chemin ou bien encore la fin de la liste chaînée "père")
 * @param graphe : Le graphe utilisé
 * @param depart : Sommet de départ
 * @return : Pointeur sur le sommet cible trouvé (le 1er sommet rencontré qui satisfait estFinal()) si succès et NULL si échec
 */
    static Sommet * Djikstra(Graphe & graphe, Sommet * depart)
    {
        libereToutSommet(graphe); // met tous les sommets du graphe à LIBRE et tous les liens-pere à NULL
        PElement<Sommet> * Ouverts;
        while(graphe->lSommets)
        {
            c(graphe->lSommets->valeur) = -1; // On met tous les couts des sommets du graphe à -1 car on ne connait pas les distances
        }
        pere(depart) = NULL; // Le père du départ est nul, logique puisque on part du point de départ
        c(depart) = 0; // On met le cout du départ à 0, logique puisque la distance entre le départ et lui même est de 0 km !

        Ouverts = new PElement<Sommet>(depart,NULL);
        etat(depart) = OUVERT; //

        while(Ouverts)
        {
            Sommet  * s =PElement<Sommet>::depiler(Ouverts);
            etat(s) = FERME;

            if(estFinal(s)) return s;

            PElement< pair<Sommet*,double> > * listeDesVoisins = listeVoisins(s, graphe);
            PElement< pair<Sommet*,double> > * lvTemp = listeDesVoisins;

            while(lvTemp)
            {
                Sommet * v = lvTemp->valeur->first;
                double coutSversV = graphe->getAreteParSommets(s, v)->v.getInfoAlgo().c;
                if(etat(v)==LIBRE)
                {
                    pere(v) = s;
                    c(v) = c(s) + coutSversV;
                    etat(v) = OUVERT;
                    Ouverts = new PElement<Sommet>(v,Ouverts);
                }
                else
                {
                    if(etat(v) == OUVERT && c(s) < (coutSversV + c(v)))
                    {
                        pere(v) = s;
                        c(v)= c(s) + coutSversV;
                        Ouverts->depiler(v);
                        Ouverts = new PElement<Sommet>(v,Ouverts);
                    }
                }
                lvTemp = lvTemp -> suivant;
            }
        }
        return NULL;
    }
/**

recherche  dans graphe le plus court chemin de départ à un état final par l'algo A*.
en cas de succès, les liens "père" des sommets indiquent le chemin à suivre en partant du sommet-cible trouvé vers départ.
le père de départ vaut toujours NULL en sortie (c'est la racine du chemin ou bien encore la fin de la liste chaînée "père")

retourne un pointeur sur le sommet-cible trouvé  (le 1er sommet rencontré qui satisfait estFinal()) si succès et NULL si échec

suppose que tout sommet s du graphe
dispose des attributs suivants publics :
int etat (peut prendre l'une des 3 valeurs suivantes : LIBRE, OUVERT ou FERMé)
pere : Sommet * pere
double c;		// coût réel entre départ et s
double h;		// estimation du coût entre s et cible
double g;		// g == c+h

suppose que la méthode listeVoisins(sommet,graphe) retourne la liste des paires (voisin, coût de l'arête sommet-voisin)

hh est l'heuristique à appliquer entre 1 sommet quelconque du graphe et un état final

bool estFinal(const Sommet * s) est une méthode indiquant si le sommet correspond à un état final

*/

    static Sommet * aStar(Graphe & graphe, Sommet * depart,
                          double (*hh)(const Sommet * s)/*,
			PElement< pair<Sommet*,double> > * (*listeVoisins)(const Sommet * s, const Graphe & graphe),
			void (*libereToutSommet)(Graphe & graphe)*/)
    {
        libereToutSommet(graphe); // met tous les sommets du graphe à LIBRE et tous les liens-pere à NULL
        PElement<Sommet> * Ouverts;

        pere(depart) = NULL; c(depart) = 0; // depart->h = h(depart,cible); depart->g = depart->c + depart->h; // ces 2 dernières affectations sont inutiles

        Ouverts = new PElement<Sommet>(depart,NULL); etat(depart) = OUVERT;

        while(Ouverts)
        {
            Sommet *s = PElement<Sommet>::depiler(Ouverts);
            etat(s) = FERME;

            if (estFinal(s))
            {
                PElement<Sommet>::efface1(Ouverts);
                return s;
            }

            PElement<pair<Sommet *, double> > *listeDesVoisins = listeVoisins(s, graphe);
            PElement<pair<Sommet *, double> > *l;

            for (l = listeDesVoisins; l; l = l->suivant)        // on parcourt les voisins de s
            {
                Sommet *v = l->valeur->first;    // v est le voisin courant de s

                double nouveauCout =
                        c(s) + l->valeur->second;            //l->valeur->second est le coût de l'arête s - v

                if (etat(v) == LIBRE)
                {
                    h(v) = hh(v);
                    miseAJourVoisin(v, s, nouveauCout, Ouverts);
                } else            // v est Fermé ou Ouvert

                if (nouveauCout < c(v))
                {
                    if (etat(v) == OUVERT)
                        PElement<Sommet>::retire(v, Ouverts);

                    miseAJourVoisin(v, s, nouveauCout, Ouverts);

                }
            }

            PElement<pair<Sommet *, double> >::efface2(listeDesVoisins);
        }

        return NULL;

    }

    static Sommet * rechercheCoutUniforme(Graphe & graphe, Sommet * depart, Sommet * cible)
    {
        libereToutSommet(graphe); // met tous les sommets du graphe à LIBRE et tous les liens-pere à NULL
        PElement<Sommet> * Ouverts;

        c(depart) = 0;
        etat(depart) = OUVERT;
        Ouverts = new PElement<Sommet>(depart,NULL);

        while(Ouverts)
        {
            Sommet  * s =PElement<Sommet>::depiler(Ouverts);
            etat(s) = FERME;

            if (cible == s)
            {
                PElement<Sommet>::efface1(Ouverts);
                return s;
            }

            PElement< pair<Sommet*,double> > * listeDesVoisins = listeVoisins(s, graphe);
            PElement< pair<Sommet*,double> > * l;

            for( l = listeDesVoisins; l; l = l->suivant)		// on parcourt les voisins de s
            {
                Sommet * v = l->valeur->first;	// v est le voisin courant de s

                //double nouveauCout = c(s) + l->valeur->second;			//l->valeur->second est le coût de l'arête s - v

                if (etat(v) == LIBRE)
                {
                    pere(v) = s;
                    c(v)=c(s)+graphe.getAreteParSommets(s, v)->v.getInfoAlgo().c;
                    etat(v) = OUVERT;
                    PElement<Sommet>::insertionOrdonnee( v, Ouverts, estPlusPetitOuEgal);
                    //miseAJourVoisin( v, s, nouveauCout, Ouverts);
                }
                else if ((etat(v) == OUVERT) &&(c(s)+graphe.getAreteParSommets(s, v)->v.getInfoAlgo().c < c(v)))
                {
                    pere(v) = s;
                    c(v)=c(s)+graphe.getAreteParSommets(s, v)->v.getInfoAlgo().c;
                    PElement< Sommet>::retire(v,Ouverts);
                    PElement<Sommet>::insertionOrdonnee( v, Ouverts, estPlusPetitOuEgal);
                    //miseAJourVoisin( v, s, nouveauCout, Ouverts);
                }
            }
            PElement< pair<Sommet*,double> >::efface1(listeDesVoisins);
        }
        return NULL;
    }

    static void miseAJourVoisin(Sommet * v, Sommet * s, const double & nouveauCout, PElement<Sommet> * & Ouverts)
    {
        pere(v) = s;
        c(v) = nouveauCout;
        g(v) = c(v) + h(v);
        PElement<Sommet>::insertionOrdonnee( v, Ouverts, estPlusPetitOuEgal); etat(v) = OUVERT;
    }
};

/**
Tâche : Construit sous une forme plus pratique le résultat de l'algo A* et l'algo Dijkstra:
transforme sous forme de liste chaînée PElement<Sommet> la liste chaînée définie par les liens père qui a été produite par A* ou Dijkstra.

Rappel : L'algo A* et Dijkstra créent une liste chaînée dont le maillon de tête est cible et dont le maillon final est départ.
La méthode chemin(,) construit une liste chaînée qui inverse le sens de parcours de la liste "lien père" produite par A* ou Dijkstra.
DONNEES :
cible : sommet final trouvé par A* (celui qui vérifie la condition estFinal(...))

RESULTATS : debut : qui pointe sur le 1er maillon de la nouvelle liste créée (il pointe donc aussi sur le sommet depart de l'algo A* ou de l'algo de Dijkstra)
et par return un pointeur sur le dernier maillon de la liste chaînée PElement<Sommet> * construite.
Le pointeur renvoyé par return pointe donc sur cible.

HYPOTHESE :
*/
template <class Sommet>
PElement<Sommet> * chemin(Sommet * cible, PElement<Sommet> * & debut)
{
    if (!cible) 	// le chemin trouvé est vide (il n'y a donc pas de chemin)
    {
        debut = NULL; return NULL;
    }

    else
    if (!pere(cible))		// le chemin trouvé contient un seul sommet. Cela signifie que départ = cible
    {
        debut = new PElement<Sommet>(cible,NULL);
        return debut;
    }
    else	// le chemin trouvé a au moins 2 sommets
    {
        PElement<Sommet> * d = chemin(pere(cible), debut);
        d->suivant = new PElement<Sommet>(cible,NULL);
        return d->suivant;
    }
}

static void parcoursDFS(Graphe<VArete, VSommet> &G,Sommet<VSommet> * sommet)
{
    etat(sommet) = FERME;
    PElement<pair<Sommet<VSommet>*, double>>* voisins = listeVoisins(sommet, G);
    PElement<pair<Sommet<VSommet>*, double>>* v;
    for( v = voisins; v; v = v->suivant)
        parcoursDFS(G, v->valeur->first);
}

static bool aUnCircuit(Graphe<VArete, VSommet> &G)
{

    PElement<Arete<VArete, VSommet>> * aretes = G.lAretes;
    while (aretes)
    {
        parcoursDFS(G, aretes->valeur->fin);
        return etat(aretes->valeur->debut) == OUVERT;
    }
}

static void NumeroteGraphe(const Graphe<VArete, VSommet> &graphe, Sommet<VSommet> * s, int numero = 0)
{
    s->v.infoAlgo.num = numero;
    numero++;
    PElement<pair<Sommet<VSommet>*, double>>* voisins = listeVoisins(s,graphe);
    PElement<pair<Sommet<VSommet>*, double>>* v;
    for( v = voisins; v; v = v->suivant)
    {
        if (!(v->valeur->first->v.getInfoAlgo().num)) NumeroteGraphe(graphe,v->valeur->first,numero);
    }
}

static PElement<Sommet<VSommet>> * TriTopologique(Graphe<VArete, VSommet> & graphe, Sommet<VSommet> * depart, Sommet<VSommet> * cible)
{
    Sommet<VSommet> * resultat;
    OutilsCarte::cible = cible;

    resultat = Algos<Graphe<VArete,VSommet>,Sommet<VSommet> >::rechercheCoutUniforme(graphe, depart, cible);

    if (resultat)
    {
        PElement<Sommet<VSommet>> * chem;
        chemin(cible, chem);
        return chem;
    }

    /**
 * Vérifie la présence d'un chemin entre un sommet A et un sommet B. NE DOIT PAS ÊTRE APPELEE EN DEHORS DE EXISTEUNCHEMIN
 * @param graphe
 * @param A
 * @param B
 * @return
 */
    static bool _ExisteUnChemin(const Graphe &graphe, Sommet * A, Sommet * B)
    {
        if (A == B) return true;
        etat(A) = FERME;
        PElement<pair<Sommet<VSommet>*, double>>* voisins = listeVoisins(A,graphe);
        PElement<pair<Sommet<VSommet>*, double>>* v;
        for( v = voisins; v; v = v->suivant)
        {
            if(v->valeur->first->v.getInfoAlgo().etat == OUVERT)
            {
                return _ExisteUnChemin(graphe, v->valeur->first, B);
            }
        }
        return false;

    }
/**
 * Initialise les sommets avant l'appel à _ExisteUnChemin
 * @param graphe
 * @param A
 * @param B
 * @return
 */
    static bool ExisteUnChemin(Graphe &graphe, Sommet * A, Sommet * B)
    {
        libereToutSommet(graphe);
        return _ExisteUnChemin(graphe,A,B);
    }

    double _getDiametre(Graphe &graphe, Sommet * s, double resultat = c(s)) {
        etat(s) = FERME;
        PElement<pair<Sommet<VSommet> *, double>> *voisins = listeVoisins(s, graphe);
        PElement<pair<Sommet<VSommet> *, double>> *v;
        for (v = voisins; v; v = v->suivant) {
            if (v->valeur->first->v.getInfoAlgo().etat == OUVERT && c(v->valeur->first) > resultat) {
                resultat = _getDiametre(graphe, v->valeur->first, c(v->valeur->first));
            }
        }
        return resultat;
    }


    static double getDiametre(Graphe &graphe, Sommet * s)
    {
        libereToutSommet(graphe);
        return  _getDiametre(graphe,s);

    }
};

#endif //PROJETSFML_PACMAN_ALGOS_H
