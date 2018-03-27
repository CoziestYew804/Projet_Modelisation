//
// Created by alex on 16/03/18.
//

#ifndef PROJETSFML_PACMAN_ALGOS_H
#define PROJETSFML_PACMAN_ALGOS_H



#pragma once
#include <utility>

#include"PElement.h"
#include "OutilsCarte.h"
#include "Arete.h"

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
        if(graphe.getEstPossibleDjikstra()) {
            libereToutSommet(graphe); // met tous les sommets du graphe à LIBRE et tous les liens-pere à NULL
            PElement<Sommet> *Ouverts;

            //PElement<Sommet> * listeSommets = listeVoisins(s, graphe);
            PElement<Sommet> *l;

            for (l = graphe.lSommets; l; l = l->suivant) {
                c(l->valeur) = -1; // On met tous les couts des sommets du graphe à -1 car on ne connait pas les distances
            }
            pere(depart) = NULL; // Le père du départ est nul, logique puisque on part du point de départ
            c(depart) = 0; // On met le cout du départ à 0, logique puisque la distance entre le départ et lui même est de 0 km !

            Ouverts = new PElement<Sommet>(depart, NULL);
            etat(depart) = OUVERT; //

            while (Ouverts) {
                Sommet *s = PElement<Sommet>::depiler(Ouverts);
                etat(s) = FERME;

                if (estFinal(s)) return s;

                PElement<pair<Sommet *, double> > *listeDesVoisins = listeVoisins(s, graphe);
                PElement<pair<Sommet *, double> > *lvTemp = listeDesVoisins;

                while (lvTemp) {
                    Sommet *v = lvTemp->valeur->first;
                    double coutSversV = graphe.getAreteParSommets(s, v)->v.getInfoAlgo().c;
                    if (etat(v) == LIBRE) {
                        pere(v) = s;
                        c(v) = c(s) + coutSversV;
                        etat(v) = OUVERT;
                        Ouverts = new PElement<Sommet>(v, Ouverts);
                    } else {
                        if (etat(v) == OUVERT && c(s) < (coutSversV + c(v))) {
                            pere(v) = s;
                            c(v) = c(s) + coutSversV;
                            v = PElement<Sommet>::depiler(Ouverts); //Ouverts.depiler(v);
                            Ouverts = new PElement<Sommet>(v, Ouverts);
                        }
                    }
                    lvTemp = lvTemp->suivant;
                }
            }
            return NULL;
        }else{
            cerr<<"ce graphe compte une arrete de poids negatif, djikstra ne peut etre calcule"<<endl;
        }
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

    static Sommet * aStar(Graphe & graphe, Sommet * depart, double (*hh)(const Sommet * s))
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

            PElement<pair<Sommet *, double> >::efface1(listeDesVoisins);
        }

        return NULL;

    }

    static Sommet * rechercheCoutUniforme(Graphe & graphe, Sommet * depart)
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

            if (estFinal(s))
            {
                PElement<Sommet>::efface1(Ouverts);
                return s;
            }

            PElement< pair<Sommet*,double> > * listeDesVoisins = listeVoisins(s, graphe);
            PElement< pair<Sommet*,double> > * l;

            for( l = listeDesVoisins; l; l = l->suivant)		// on parcourt les voisins de s
            {
                Sommet * v = l->valeur->first;	// v est le voisin courant de s

                double nouveauCout = c(s) + l->valeur->second;			//l->valeur->second est le coût de l'arête s - v

                if (etat(v) == LIBRE)
                {
                    miseAJourVoisin( v, s, nouveauCout, Ouverts);
                }
                else if ((etat(v) == OUVERT) &&(nouveauCout < c(v)))
                {
                    PElement< Sommet>::retire(v,Ouverts);
                    miseAJourVoisin( v, s, nouveauCout, Ouverts);
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
    cout<< sommet->v.nom<<" -> ";
    PElement<pair<Sommet<VSommet>*, double>>* voisins = listeVoisins(sommet, G);
    PElement<pair<Sommet<VSommet>*, double>>* v;
    for( v = voisins; v; v = v->suivant) {
        if (etat(v->valeur->first) != FERME)
            parcoursDFS(G, v->valeur->first);
    }

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

static void  TriTopologique(Graphe<VArete, VSommet> & graphe,  vector<Sommet<VSommet>*> tri,vector<Arete<VArete, VSommet> *> lAretes)
{
    /*Sommet<VSommet> *resultat;
    OutilsCarte::cible = cible;

    resultat = Algos<Graphe<VArete, VSommet>, Sommet<VSommet> >::rechercheCoutUniforme(graphe, depart);

    if (resultat)
    {
        PElement<Sommet<VSommet>> *chem;
        chemin(cible, chem);
        cout << chem->valeur->v << endl;
        return chem;
    }*/

        vector<Sommet<VSommet>*> temp1;
    Sommet<VSommet> *temp;
    for (int i=0;i <= tri.size() ;i++)
    {
                //topo->insertionOrdonnee(ls->valeur, topo, estPlusPetitouEgal);

                bool aUnPere=false;

                for(Arete<VArete, VSommet> * a : lAretes) // Problem part
                {
                    if(a->fin==tri[i]) {
                        if(std::find(tri.begin(), tri.end(), a->debut) != tri.end()){
                            aUnPere=true;
                        }
                    }
                }
                if(!aUnPere) {
                    cout << tri[i]->v.nom << " , ";
                    temp = tri[i];
                    i = tri.size()+1;
                }


                    //remove(tri.begin(), tri.end(), tri[i])}


    }

    for(int j=0;j<tri.size();j++){

        if(tri[j]!=temp) {
            temp1.push_back(tri[j]);
        }
    }

    if(temp1.size()>0){
    TriTopologique(graphe,temp1,lAretes);

    }




}

    /**
 * Vérifie la présence d'un chemin entre un sommet A et un sommet B. NE DOIT PAS ÊTRE APPELEE EN DEHORS DE EXISTEUNCHEMIN
 * @param graphe
 * @param A
 * @param B
 * @return
 */
    static bool _ExisteUnChemin(const Graphe<VArete,VSommet> &graphe, Sommet<VSommet> * A, Sommet<VSommet> * B)
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
    static bool ExisteUnChemin(Graphe<VArete,VSommet> &graphe, Sommet<VSommet> * A, Sommet<VSommet> * B)
    {
        libereToutSommet(graphe);
        return _ExisteUnChemin(graphe,A,B);
    }

    double _getDiametre(Graphe<VArete,VSommet> &graphe, Sommet<VSommet> * s, double resultat = 0) {
        resultat = c(s);
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

    static double getDiametre(Graphe<VArete,VSommet> &graphe, Sommet<VSommet> * s)
    {
        libereToutSommet(graphe);
        return  _getDiametre(graphe,s);
    }
/*static bool isCyclicUtil(int v, bool visited[], bool *recStack,vector<vector<int>> adj)
{
    if(visited[v] == false)
    {
        //marque le sommet courant comme marquee et a ete part de la recursivite
        visited[v] = true;
        recStack[v] = true;

        //parcours pour tous les sommets leur voisins
        vector<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack,adj) )
                return true;
            else if (recStack[*i])
                return true;
        }

    }
    recStack[v] = false;  // remove the vertex from recursion stack
    return false;
}
static bool isCyclic(int V,vector<vector<int>> adj)
{
    // Marque tous les sommet comme non marques et ont pas participe a la recursion
    // stack
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    // appelle la fonction recursive afin de checker dans les differents
    // arbres DFS
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack,adj))
            return true;

    return false;
}*/



#endif //PROJETSFML_PACMAN_ALGOS_H
