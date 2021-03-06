#pragma once

/**
Motivations qui ont conduit à cette solution pour représenter un graphe :

hypothèses : Un graphe est non orienté. Dans le cas général, une information est associée à chaque sommet, à chaque arête : un nom, un n°, une couleur, etc.

J'ignore totalement la nature de cette information, d'où template <S,T>.
S : info associée à une arête
T : info associée à un sommet

chaque élément du graphe est identifié par une clef unique. Celle-ci est générée automatiquement par l'attribut prochaineClef du graphe.
Celle-ci définit à tout instant la clef qui sera attribuée au prochain élément créé dans le graphe.

*/

#include <utility>
#include <list>
#include "PElement.h"
#include "../Erreur.h"
#include "Sommet.h"
#include "Arete.h"
#include "VSommet.h"

/*
classe sachant dessiner un graphe

template <class S, class T> class Dessinateur; */

template<class S, class T>
class Graphe
{
    protected:

    /** la  clef qui sera attribuée au prochain élément (sommet ou arête) créé dans le graphe par les méthodes creeSommet(info)
    ou creeArete(info,debut,fin) fonctionne comme auto-increment d'une base de données */

        int prochaineClef;
    private:
    bool estPossibleDjikstra=true;






    /**
     * crée un sommet isolé.
     * Attention : on suppose que clef est valide (c'est-à-dire qu'elle
     *											n'est pas déjà utilisée par un élément (sommet ou arête) présent dans le graphe)
     *
     * Ne met pas à jour prochaineClef
     * */
        Sommet <T> *creeSommet1(const int clef, const T &info);

    /**
     * utilisée par les méthodes qui créent des éléments (Sommet ou Arête) en utilisant une clef imposée à l'appel, c'est-à-dire les méthodes
     * creeSommet(clef,info) et creeArete(clef, info, debut, fin)
     *
     * met  à jour prochaineClef
     * */

        void majProchaineClef(const int clef)
        {
            prochaineClef = max(1 + clef, prochaineClef);
        }

    /**
     * crée un sommet isolé
     *
     * Attention : on suppose que clef est valide (c'est-à-dire qu'elle
     *											n'est pas déjà utilisée par un élément (sommet ou arête) présent dans le graphe)
     * Utilisée dans la méthode copie()
     *
     * met à jour prochaineClef
     * */
        Sommet <T> *creeSommet(const int clef, const T &info)
        {
            majProchaineClef(clef);
            return creeSommet1(clef, info);
        }

    /**
     * crée une arête joignant les 2 sommets debut et fin
     *
     * met à jour les champs degre de debut et de fin
     *
     * Ne met pas à jour prochaineClef
     *
     * */

        Arete <S, T> *creeArete1(const int clef, const S &info, Sommet <T> *debut, Sommet <T> *fin);

    /**
     * crée une arête joignant les 2 sommets debut et fin
     *
     * met à jour les champs degre de debut et de fin
     *
     * Attention : on suppose que clef est valide (c'est-à-dire qu'elle
     *											n'est pas déjà utilisée par un élément (sommet ou arête) présent dans le graphe)
     *
     * met à jour prochaineClef
     * */

        Arete <S, T> *creeArete(const int clef, const S &info, Sommet <T> *debut, Sommet <T> *fin)
        {
            majProchaineClef(clef);
            return creeArete1(clef, info, debut, fin);
        }

    /*
    * Recopie graphe dans *this : utilisé par le constructeur de copie et par l'opérateur =
    *
    * Attention : suppose que *this est VIDE avant l'appel, c'est-à-dire que lSommets == lAretes == NULL et que prochaineClef == 0
    *
    */

    void copie(const Graphe<S, T> &graphe);

    /*
    * utilisé par l'opérateur = et par le destructeur
    */
    void effaceTout();

    public:

    list<int> *adj;
    int V;

    // This function is a variation of DFSUytil() in https://www.geeksforgeeks.org/archives/18212
     bool isCyclicUtil(int v, bool visited[], bool *recStack)
    {
        if(visited[v] == false)
        {
            // Mark the current node as visited and part of recursion stack
            visited[v] = true;
            recStack[v] = true;

            // Recur for all the vertices adjacent to this vertex
            list<int>::iterator i;
            for(i = adj[v].begin(); i != adj[v].end(); ++i)
            {
                if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                    return true;
                else if (recStack[*i])
                    return true;
            }

        }
        recStack[v] = false;  // remove the vertex from recursion stack
        return false;
    }
     bool isCyclic()
    {
        // Mark all the vertices as not visited and not part of recursion
        // stack
        bool *visited = new bool[V];
        bool *recStack = new bool[V];
        for(int i = 0; i < V; i++)
        {
            visited[i] = false;
            recStack[i] = false;
        }

        // Call the recursive helper function to detect cycle in different
        // DFS trees
        for(int i = 0; i < V; i++)
            if (isCyclicUtil(i, visited, recStack))
                return true;

        return false;
    }
    void setEstPossibleDjikstra(const bool val){
        estPossibleDjikstra=val;
    }

    bool getEstPossibleDjikstra() const {
        return estPossibleDjikstra;
    }

    /**
     * crée un graphe vide
     */
    Graphe() : prochaineClef(0), lSommets(NULL), lAretes(NULL)
    {}

    Graphe(const Graphe<S, T> &graphe) : Graphe()
    { this->copie(graphe); }

    const Graphe<S, T> &operator=(const Graphe<S, T> &graphe)
    {
        this->effaceTout();
        this->copie(graphe);
        return *this;
    }


    //------------------- destructeur ----------------------------------------------

    ~Graphe()
    {
        this->effaceTout();
    }


    //------------------- opérations de consultation ----------------------------------------------

    int nombreSommets() const
    {
        return PElement < Sommet < T > > ::taille(lSommets);
    }

    int nombreAretes() const
    {
        return PElement < Arete < S, T > > ::taille(lAretes);
    }


    /**

    recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe

    */
        PElement<pair < Sommet < T> *, Arete <S, T>* > >  *

        adjacences(const Sommet <T> *sommet) const;

        PElement <Arete<S, T>> *aretesAdjacentes(const Sommet <T> *sommet) const;

        PElement <Sommet<T>> *voisins(const Sommet <T> *sommet) const;

    /**
     * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
     *
     * DONNEES : s1 et s2 deux sommets quelconques du graphe
     * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
     *
     * */
        Arete <S, T> *getAreteParSommets(const Sommet <T> *s1, const Sommet <T> *s2) const;

        operator string() const;

    /**
    dessine toutes les arêtes du graphe de manière indépendante de la librairie graphique utilisée

    Attention ! ici, Fenetre représente n'importe quelle classe munie de la méthode appelée.
    On n'a pas forcément Fenetre == Fenetre<S,T> !
    Cette solution est plus générale
    renvoie true en cas de succès complet, false en cas d'échec partiel
    */
    template<class Fenetre>
    bool dessineToutesAretes(Fenetre &Fen) const;

    /**
    dessine tous les sommets du graphe de manière indépendante de la librairie graphique utilisée

    Attention ! ici, Fenetre représente n'importe quelle classe munie de la méthode appelée.
    On n'a pas forcément Fenetre == Fenetre<S,T> !
    Cette solution est plus générale
    renvoie true en cas de succès complet, false en cas d'échec partiel
    */
    template<class Fenetre>
    bool dessineTousSommets(Fenetre &Fen) const;

    /**
    dessine le graphe de manière indépendante de la librairie graphique utilisée

    Attention ! ici, Fenetre représente n'importe quelle classe munie des 2 méthodes appelées.
    On n'a pas forcément Fenetre == Fenetre<S,T> !
    Cette solution est plus générale
    renvoie true en cas de succès complet, false en cas d'échec partiel
    */
    template <class Fenetre>
    bool dessine(Fenetre &Fen) const;

    PElement <Sommet<T>> *lSommets; // liste de sommets
    PElement <Arete<S, T>> *lAretes; // liste d'arêtes

    /**
     * crée un sommet isolé
     * met à jour prochaineClef
     * */
    Sommet <T> *creeSommet(const T &info)
    {
        return creeSommet1(prochaineClef++, info);
    }

    /**
     * crée une arête joignant les 2 sommets debut et fin
     *
     * met à jour les champs degre de debut et de fin
     *
     * met à jour prochaineClef
     *
     * */

    Arete <S, T> *creeArete(const S &info, Sommet <T> *debut, Sommet <T> *fin)
    { return creeArete1(prochaineClef++, info, debut, fin); }


    template<class Sommet>
    void DFS(Sommet &s);
};

template<class S, class T>
ostream &operator<<(ostream &os, const Graphe<S, T> &gr)
{
    return os << (string) gr;
}

/**
 * crée un sommet isolé.
 * Attention : on suppose que clef est valide (c'est-à-dire qu'elle
 *											n'est pas déjà utilisée par un élément (sommet ou arête) présent dans le graphe)
 *
 * Ne met pas à jour prochaineClef
 * */
template<class S, class T>
Sommet <T> *Graphe<S, T>::creeSommet1(const int clef, const T &info)
{
    Sommet <T> *sommetCree = new Sommet<T>(clef, info);
    lSommets = new PElement <Sommet<T>>(sommetCree, lSommets);

    return sommetCree;
}

/**
 * crée une arête joignant les 2 sommets debut et fin
 *
 * met à jour les champs degre de debut et de fin
 *
 * Ne gère pas prochaineClef
 *
 * */
template<class S, class T>
Arete <S, T> *Graphe<S, T>::creeArete1(const int clef, const S &info, Sommet <T> *debut, Sommet <T> *fin)
{

    // ici tester que les 2 sommets sont bien existants dans le graphe
    if (!PElement < Sommet < T > > ::appartient(debut, lSommets))
        throw Erreur("début d'arête non défini");
    if (!PElement < Sommet < T > > ::appartient(fin, lSommets))
        throw Erreur("fin d'arête non définie");

    Arete <S, T> *nouvelleArete = new Arete<S, T>(clef, info, debut, fin);

    lAretes = new PElement <Arete<S, T>>(nouvelleArete, lAretes);

    return nouvelleArete;
}

/**
 * crée une arête joignant les 2 sommets debut et fin
 *
 * met à jour les champs degre de debut et de fin
 *
 * Attention : on suppose que clef est valide (c'est-à-dire qu'elle
 *											n'est pas déjà utilisée par un élément (sommet ou arête) présent dans le graphe)
 *
 * met à jour prochaine Clef
 *
 * */
/*template <class S, class T>
Arete<S,T> * Graphe<S,T>::creeArete( const int clef, const S & info, Sommet<T> * debut, Sommet<T> * fin)
{
majProchaineClef(clef);
return creeArete1(clef,info,debut,fin);
}
*/

/**
utile pour les opérations de copie d'un graphe
*/
template<class T>
class SommetDejaPresentDansLaCopie
{
public:
    const Sommet <T> *s;

    SommetDejaPresentDansLaCopie(const Sommet <T> *s) : s(s)
    {}

    bool operator()(const Sommet <T> *sommet) const
    { return sommet->clef == s->clef; }
};

/*
* Recopie graphe dans *this : utilisé par le constructeur de copie et par l'opérateur =
*
* Attention : suppose que *this est VIDE avant l'appel, c'est-à-dire que lSommets == lAretes == NULL et que prochaineClef == 0
*
*/
template<class S, class T>
void Graphe<S, T>::copie(const Graphe<S, T> &graphe)
{
    const PElement <Sommet<T>> *pS;

// -------------- d'abord on recopie les sommets --------------------

    for (pS = graphe.lSommets; pS; pS = pS->suivant)
    {                                    // parcourt les sommets du graphe "graphe" et les crée un par un dans *this en tant que sommets isolés
        const Sommet <T> *sommet = pS->valeur;                // sommet courant à recopier
        this->creeSommet(sommet->clef, sommet->v);        // on crée la copie du sommet courant avec la même clef
    }


// -------------------- et maintenant on recopie les arêtes --------------------

// attention, la recopie des arêtes est plus compliquée car il faut rebrancher les arêtes sur les nouveaux sommets qui viennent d'être créés.
// Pour retrouver les "bons sommets" on utilise les clefs qui ont été conservées

    const PElement <Arete<S, T>> *pA;
    for (pA = graphe.lAretes; pA; pA = pA->suivant)    // parcourt les arêtes de l'ancien graphe et les recopie une par une
    {
        const Arete <S, T> *a = pA->valeur;            // arête courante à recopier
        Sommet <T> *d, *f;                        // le début et la fin de la nouvelle arête qui va être créée
        PElement <Sommet<T>> *p;                // pour retrouver d et f dans la nouvelle liste de sommets grâce aux clefs qui ont été conservées

        // on recherche d dans la nouvelle liste de sommets grâce à sa clef
        SommetDejaPresentDansLaCopie<T> conditionDebut(a->debut);
        bool c = conditionDebut(a->debut);
        p = PElement < Sommet < T > > ::appartient(lSommets, c);
        d = p->valeur;

        // on recherche f dans la nouvelle liste de sommets grâce à sa clef
        SommetDejaPresentDansLaCopie<T> conditionFin(a->fin);
        c = conditionFin(a->fin);
        p = PElement < Sommet < T > > ::appartient(lSommets, c);
        f = p->valeur;

        this->creeArete(a->clef, a->v, d, f);
    }
}

/*
* utilisé par l'opérateur = et par le destructeur
*/
template<class S, class T>
void Graphe<S, T>::effaceTout()
{
    PElement < Arete < S, T >> ::efface2(this->lAretes);
    PElement < Sommet < T > > ::efface2(this->lSommets);
    this->prochaineClef = 0;
}

/**
 * crée un sommet isolé.
 *
 * ancienne version qui ne prend pas en compte le ctor de copie ni l'opérateur =
 * Gère prochaineClef
 *
 * */
/*template <class S, class T>
Sommet<T> * Graphe<S,T>::creeSommet( const T & info)
{
Sommet<T> * sommetCree = new Sommet<T>( prochaineClef++,info);
lSommets = new PElement< Sommet<T> >( sommetCree, lSommets);

return sommetCree;
}
*/
/**
 * crée une arête joignant les 2 sommets debut et fin
 *
 * met à jour les champs degre de debut et de fin
 *
 * ancienne version qui ne prend pas en compte le ctor de copie ni l'opérateur =
 * */
/*template <class S, class T>
Arete<S,T> * Graphe<S,T>::creeArete( const S & info, Sommet<T> * debut, Sommet<T> * fin)
{

// ici tester que les 2 sommets sont bien existants dans le graphe
if (! PElement< Sommet<T> >::appartient(debut,lSommets) ) throw Erreur("début d'arête non défini");
if (! PElement< Sommet<T> >::appartient(fin,lSommets)) throw Erreur("fin d'arête non définie");

Arete<S,T> * nouvelleArete = new Arete<S,T>( prochaineClef++, debut, fin,  info);

lAretes = new PElement< Arete<S,T> >( nouvelleArete, lAretes);

return nouvelleArete;
}
*/

/**

recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe

*/
template<class S, class T>
PElement<pair < Sommet < T> *, Arete <S, T>* > >  *

Graphe<S, T>::adjacences(const Sommet <T> *sommet) const
{
    const PElement <Arete<S, T>> *l;

    PElement < pair < Sommet < T > *, Arete < S, T > * > > *r;                // pair< Sommet<T> *, Arete<S,T>* >

    for (l = lAretes, r = NULL; l; l = l->suivant)

        if (sommet == l->valeur->debut)
            r = new PElement < pair < Sommet < T > *, Arete < S, T > * > >
                                                                 (new pair < Sommet < T > *, Arete < S, T > * >
                                                                                                        (l->valeur->fin, l->valeur), r);
    return r;
}


template<class S, class T>
PElement <Arete<S, T>> *Graphe<S, T>::aretesAdjacentes(const Sommet <T> *sommet) const
{
    PElement < pair < Sommet < T > *, Arete < S, T > * > > *ladj = this->adjacences(sommet);
    PElement < pair < Sommet < T > *, Arete < S, T > * > > *l;

    PElement <Arete<S, T>> *r;

    for (l = ladj, r = NULL; l; l = l->suivant)
        r = new PElement <Arete<S, T>>(l->valeur->second, r);

    PElement < pair < Sommet < T > *, Arete < S, T > * > > ::efface2(ladj);

    return r;
}

template<class S, class T>
PElement <Sommet<T>> *Graphe<S, T>::voisins(const Sommet <T> *sommet) const
{
    PElement < pair < Sommet < T > *, Arete < S, T > * > > *ladj = this->adjacences(sommet);
    PElement < pair < Sommet < T > *, Arete < S, T > * > > *l;

    PElement <Sommet<T>> *r;

    for (l = ladj, r = NULL; l; l = l->suivant)
        r = new PElement <Sommet<T>>(l->valeur->first, r);

    PElement < pair < Sommet < T > *, Arete < S, T > * > > ::efface2(ladj);

    return r;
}

/**
 * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
 *
 * DONNEES : s1 et s2 deux sommets quelconques du graphe
 * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
 *
 * */
template<class S, class T>
Arete <S, T> *Graphe<S, T>::getAreteParSommets(const Sommet <T> *s1, const Sommet <T> *s2) const
{
    PElement <Arete<S, T>> *l;

    for (l = this->lAretes; l; l = l->suivant)
        if (l->valeur->estEgal(s1, s2))
            return l->valeur;

    return NULL;
}


template<class S, class T>
Graphe<S, T>::operator string() const
{
    ostringstream oss;
    oss << "Graphe( \n";
    oss << "\tProchaine clef = " << this->prochaineClef << endl;
    oss << "\tNb sommets = " << this->nombreSommets() << "\n";

    oss << PElement < Sommet < T > > ::toString(lSommets, "", "\n", "\n");

    oss << "\tNb arêtes = " << this->nombreAretes() << "\n";

    oss << PElement < Arete < S, T > > ::toString(lAretes, "", "\n", "\n");
    oss << ")";
    return oss.str();
}

/**
dessine toutes les arêtes du graphe de manière indépendante de la librairie graphique utilisée

Attention ! ici, Fenetre représente n'importe quelle classe munie de la méthode appelée.
On n'a pas forcément Fenetre == Fenetre<S,T> !
Cette solution est plus générale
renvoie true en cas de succès complet, false en cas d'échec partiel
*/
template<class S, class T>
template<class Fenetre>
bool Graphe<S, T>::dessineToutesAretes(Fenetre &Fen) const
{

// ------------------------ on dessine les arêtes --------------------------

    PElement <Arete<S, T>> *pA;
    for (pA = this->lAretes; pA; pA = pA->suivant)
        if (!Fen.dessine(pA->valeur)) return false; // tente de dessiner puis retourne false en cas d'échec

    return true;
}

/**
dessine tous les sommets du graphe de manière indépendante de la librairie graphique utilisée

Attention ! ici, Fenetre représente n'importe quelle classe munie de la méthode appelée.
On n'a pas forcément Fenetre == Fenetre<S,T> !
Cette solution est plus générale
renvoie true en cas de succès complet, false en cas d'échec partiel
*/
template<class S, class T>
template<class Fenetre>
bool Graphe<S, T>::dessineTousSommets(Fenetre &Fen) const
{

// ------------------------ on dessine les sommets --------------------------

    PElement <Sommet<T>> *pS;
    for (pS = this->lSommets; pS; pS = pS->suivant)
        if (!Fen.dessine(pS->valeur)) return false;    // tente de dessiner puis retourne false en cas d'échec

    return true;
}

/**
dessine le graphe de manière indépendante de la librairie graphique utilisée

Attention ! ici, Fenetre représente n'importe quelle classe munie des 2 méthodes appelées.
On n'a pas forcément Fenetre == Fenetre<S,T> !
Cette solution est plus générale
renvoie true en cas de succès complet, false en cas d'échec partiel
*/
template<class S, class T>
template<class Fenetre>
bool Graphe<S, T>::dessine(Fenetre &Fen) const
{

// ------------------------ on dessine les arêtes --------------------------

    return this->dessineToutesAretes(Fen) && this->dessineTousSommets(Fen);

// ------------------------ on dessine les sommets --------------------------

}

/**
dessine le chemin "chemin" sur la fenêtre "fenêtre" en utilisant la couleur "couleur"
et de manière indépendante de la librairie graphique utilisée.
Suppose que les coordonnées des sommets sont définies par rapport au repère monde

Attention ! ici, Fenetre représente n'importe quelle classe munie de la méthode appelée.
On n'a pas forcément Fenetre == Fenetre<S,T> !
Cette solution est plus générale
renvoie true en cas de succès complet, false en cas d'échec partiel
*/
template<class T, class Fenetre>
bool dessine(const PElement <Sommet<T>> *chemin, Fenetre &Fen, const unsigned int couleur)
{
    if (!(chemin && chemin->suivant)) // le chemin est vide ou ne contient qu'un sommet : il n'y  a rien à dessiner
        return true;

    else        // le chemin contient au moins une arête
    {
        // on dessine d'abord la 1ère arête

        Fen.dessine(chemin->valeur, chemin->suivant->valeur, couleur);

        return dessine(chemin->suivant, Fen, couleur);        // puis on dessine les arêtes suivantes
    }
}



/**
dessine le graphe de manière indépendante de la librairie graphique utilisée

Attention ! ici, Fenetre représente n'importe quelle classe munie des 2 méthodes appelées.
On n'a pas forcément Fenetre == Fenetre<S,T> !
Cette solution est plus générale
renvoie true en cas de succès complet, false en cas d'échec partiel
* /
template <class S, class T>
template< class Fenetre>
bool Graphe<S,T>::dessine( Fenetre & Fenetre) const
{

// ------------------------ on dessine les arêtes --------------------------

PElement< Arete<S,T>> * pA;
for ( pA = this->lAretes; pA; pA = pA->s)
	if (!Fenetre.dessine(pA->v)) return false; // tente de dessiner puis retourne false en cas d'échec

// ------------------------ on dessine les sommets --------------------------

PElement< Sommet<T>> * pS;
for ( pS = this->lSommets; pS; pS = pS->s)
	if (!Fenetre.dessine(pS->v)) return false;	// tente de dessiner puis retourne false en cas d'échec

return true;
}*/


/*template <class S, class T>
template< class Fenetre>
bool Graphe<S,T>::dessine( const Fenetre & Fenetre) const
{
// ------------------- on initialise le dessin : axes du repère, légende, etc . -----------------

if (!Fenetre.initDessin(*this, largeur, hauteur)) return false;	// tente de dessiner puis retourne false en cas d'échec

// ------------------------ on dessine les arêtes --------------------------

PElement< Arete<S,T>> * pA;
for ( pA = this->lAretes; pA; pA = pA->s)
	if (!Fenetre.dessine(pA->v)) return false; // tente de dessiner puis retourne false en cas d'échec

// ------------------------ on dessine les sommets --------------------------

PElement< Sommet<T>> * pS;
for ( pS = this->lSommets; pS; pS = pS->s)
	if (!Fenetre.dessine(pS->v)) return false;	// tente de dessiner puis retourne false en cas d'échec

// ---------------------------- on dessine la finition : un chemin, un circuit à surligner, etc. --------------------

return Fenetre.finitDessin(*this);
}*/

