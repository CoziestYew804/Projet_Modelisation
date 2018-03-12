//
// Created by arnaud on 08/01/18.
//

#ifndef UNTITLED_PELEMENT_H
#define UNTITLED_PELEMENT_H
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;
template<class T>
class PElement {
public:
    T * valeur;
    PElement<T> * suivant;


    PElement(T * v, PElement<T> * s):valeur(v), suivant(s)
    {
        /* valeur = v;
         suivant = s;*/
    }

    //calcule la taille de la liste l (la solution récursive est plus simple).
    static int taille(const PElement<T> * i)
    {
        if (i == nullptr)
            return 0;
        else
            return 1 + taille(i->suivant);
    }

    /*transforme la liste p en string (la solution avec une boucle est plus simple).
    Le plus simple est d'utiliser un ostringstream intermédiaire.
    On suppose que l'opérateur << d'écriture sur un flux est défini pour la classe T.*/
    static const string toString(const PElement<T> * p,
                                 const string debut = "( ",
                                 const string separateur = ", ",
                                 const string fin = ")")
    {
        std::ostringstream o;
        o << debut;
        const PElement<T> * copie = p;
        for (int i = taille (copie) ; i > 0 ; --i)
        {
            o << *copie->valeur << separateur;
            copie = copie->suivant;
        }
        o << fin;
        delete(copie);
        return o.str();
    }

    /*insère en ordre la nouvelle valeur a dans la liste l en se servant de la méthode de comparaison estPlusPetitOuEgal.
     * l peut être modifiée par l'appel (d'où le &).*/
    static void insertionOrdonnee(  T * a,
                                    PElement<T> * & l,
                                    bool (*estPlusPetitOuEgal)(const T * a1, const T * a2))
    {
        if (l != NULL)
        {
            if (estPlusPetitOuEgal(a, l->valeur))
            {
                PElement<T> *tmp = l;
                l = new PElement<T>(a, tmp);
            }
            else
                insertionOrdonnee(a, l->suivant, estPlusPetitOuEgal);
        }
        else
            l = new PElement<T>(a, NULL);
    }
    static T * depiler(PElement<T> * & l)
    {
        if (l == NULL)
            throw ("Erreur");
        T* res = l->valeur;
        delete(&l->valeur);
        l = l->suivant;
        return res;
    }

    /*retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien.
    L'élément trouvé v n'est pas effacé mais le maillon le contenant est effacé.
    La version récursive est nettement plus facile à écrire.
    La comparaison est faite sur les pointeurs v.*/
    static bool retire(const T * a, PElement<T> * & l)
    {
        if (l == NULL)
            return false;
        else
        {
            if (a == l->valeur)
            {
                delete(&l->valeur);
                l = l->suivant;
                return true;
            }
            else
                retire(a, l->suivant);
        }
    }

    /*efface tous les maillons de  la liste l mais qui n'efface pas les données *v.
     * En sortie l vaut NULL. Ne fait rien si l vaut NULL à l'appel.*/
    static void efface1(PElement<T>* & l)
    {
        if (l != NULL)
        {
            if(l->suivant != nullptr)
            {
                efface1(l->suivant);
                delete(l);
            }
        }
    }

    /*efface tous les maillons de  la liste l et toutes les données *v.
     * En sortie l vaut NULL. Ne fait rien si l vaut NULL à l'appel.*/
    static void efface2(PElement<T>* & l)
    {
        /*if (l!=NULL)
        {
            delete &l->valeur;
            efface2(l->suivant);
            //delete l;
            l = NULL;
        }*/
    }

    /*réalise une copie de la liste l sans réaliser une copie des données *v.
     * Réalise donc une copie partageant les données *v avec l.*/
    static PElement<T> * copie1( PElement<T> * l)
    {
        if(l!=NULL)
            return new PElement<T>(l->valeur,copie2(l->suivant));
        else
            return NULL;
    }

    /*réalise une copie de la liste l en recopiant toutes les données *v.
     * Réalise donc une copie ne partageant aucune  donnée  avec l.*/
    static PElement<T> * copie2( PElement<T> * l)
    {
        if(l!=NULL)
            return new PElement<T>(new T(*(l->valeur)),copie2(l->suivant));
        else
            return NULL;
    }


    /*recherche si a appartient à l. renvoie un pointeur sur le maillon de l contenant a.
     * Renvoie NULL si a n'appartient pas à l.*/
    static PElement< T > * appartient(const T * a,  PElement<T> * l)
    {
        if(l != NULL)
        {
            if(l->valeur == a)
                return l;
            else
                return appartient(a, l->suivant);
        }
        else
            return NULL;
    }

    /*recherche dans l le premier élément vérifiant la condition condition. renvoie un pointeur sur le premier  maillon de l vérifiant la condition.
     * Renvoie NULL si aucun maillon ne vérifie la conditon.*/
    template <class FONCTEUR>
    static PElement< T > * appartient(PElement<T> * l, const FONCTEUR & condition)
    {
        if(l != NULL)
        {
            if(condition)
            {
                return l;
            }
            else
                return appartient(l->suivant, condition);
        }
        else
            return NULL;
    }
};

template<class T>
ostream & operator << (ostream & os, const PElement<T> * p)
{
    os << PElement<T>::toString(p);
    return os;
}

template<class T> bool estPlusPetitouEgal(const T * a, const T * b)
{
    return *a<=*b;
}

#endif //UNTITLED_PELEMENT_H