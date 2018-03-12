#include "OutilsCarte.h"


/*static*/ double OutilsCarte::distance( const Sommet<VSommet> * s1, const Sommet<VSommet> * s2)
{
return norme(s1->v.getPosition() - s2->v.getPosition());
//return 0;
}

/*static*/ Arete<VArete, VSommet> *  OutilsCarte::creeArete(Sommet<VSommet> * sA, Sommet<VSommet> * sB, Graphe<VArete, VSommet> & graphe)
{
return graphe.creeArete( VArete( OutilsCarte::distance(sA,sB) ), sA, sB);
}

/*static*/ void OutilsCarte::libereToutSommet(Graphe<VArete, VSommet> & graphe)
{
PElement < Sommet<VSommet> > * l;


for (  l = graphe.lSommets; l ; l = l->suivant)
	{
	etat(l->valeur) = LIBRE;
	pere(l->valeur) = NULL;
	}
}


/*static*/ double OutilsCarte::hh(const Sommet<VSommet> * s)
{
return OutilsCarte::distance(s,OutilsCarte::cible);
}

/*static*/ PElement< pair<Sommet<VSommet>*,double> > * OutilsCarte::listeVoisins(const Sommet<VSommet> * s, const Graphe<VArete, VSommet> & graphe)
{
PElement< pair < Sommet<VSommet> *, Arete<VArete,VSommet> * > > * ladj, *lA;						// pair < Sommet<VSommet> *, Arete<VArete,VSommet> * >

ladj = graphe.adjacences(s);

PElement< pair<Sommet<VSommet>*,double> > * lVC;

for ( lA = ladj, lVC = NULL; lA; lA = lA->suivant)
	lVC = new PElement< pair<Sommet<VSommet>*,double> >( new pair<Sommet<VSommet>*,double>(lA->valeur->first,1),lVC);


PElement< pair< Sommet<VSommet> *, Arete<VArete,VSommet> * > >::efface2(ladj);
return lVC;

}

/*static*/ Sommet<VSommet> *  OutilsCarte::pere(const Sommet<VSommet> * sommet)
{
return (Sommet<VSommet>*)sommet->v.infoAStar.pere;
}


/*static*/ Sommet<VSommet> * & OutilsCarte::pere( Sommet<VSommet> * sommet)
{
return (Sommet<VSommet> *&)(sommet->v.infoAStar.pere);
}

/*static*/ int & OutilsCarte::etat( Sommet<VSommet> * sommet)
{
return sommet->v.infoAStar.etat;
}

/*static*/ double & OutilsCarte::c( Sommet<VSommet> * sommet)
{
return sommet->v.infoAStar.c;
}

/*static*/ double & OutilsCarte::h( Sommet<VSommet> * sommet)
{
return sommet->v.infoAStar.h;
}

/*static*/ double OutilsCarte::g( const Sommet<VSommet> * sommet)
{
return sommet->v.infoAStar.g;
}


/*static*/ double & OutilsCarte::g( Sommet<VSommet> * sommet)
{
return sommet->v.infoAStar.g;
}

/*static*/ bool OutilsCarte::estFinal(const Sommet<VSommet> * sommet)
{
return sommet == cible;
}

/*static*/ Sommet<VSommet> * OutilsCarte::cible = NULL;


//--------------------- et maintenant les méthodes ordinaires appelées par A* -------------------------------------



void libereToutSommet(Graphe<VArete, VSommet> & graphe)
{
return OutilsCarte::libereToutSommet(graphe);
}

PElement< pair<Sommet<VSommet>*,double> > * listeVoisins(const Sommet<VSommet> * s, const Graphe<VArete, VSommet> & graphe)
{
return OutilsCarte::listeVoisins(s,graphe);
}

Sommet<VSommet> *  pere( const Sommet<VSommet> * sommet)
{
return OutilsCarte::pere(sommet);
}

Sommet<VSommet> * & pere( Sommet<VSommet> * sommet)
{
return OutilsCarte::pere(sommet);
}

int & etat( Sommet<VSommet> * sommet)
{
return OutilsCarte::etat(sommet);
}

double & c( Sommet<VSommet> * sommet)
{
return OutilsCarte::c(sommet);
}

double & h( Sommet<VSommet> * sommet)
{
return OutilsCarte::h(sommet);
}

double g( const Sommet<VSommet> * sommet)
{
return OutilsCarte::g(sommet);
}

double & g( Sommet<VSommet> * sommet)
{
return OutilsCarte::g(sommet);
}


/**
compte le nombre de maillons de la liste chaînée "pere" dont le maillon de tête est "tête".
*/
int longueurChemin(const Sommet<VSommet>* tete)
{
if (!tete)
	return 0;
else
	return 1 + longueurChemin(pere(tete));
}


const Sommet<VSommet> * dernierMaillon(const Sommet<VSommet>* tete)
{
if (!tete) return NULL;
else
	if (pere(tete) == NULL)
		return tete;
	else
		return dernierMaillon(pere(tete));

}


bool estFinal(const Sommet<VSommet> * sommet)
{
return OutilsCarte::estFinal(sommet);
}
