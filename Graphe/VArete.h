//
// Created by arnaud on 01/03/18.
//

#ifndef PROJETSFML_PACMAN_VARETE_H
#define PROJETSFML_PACMAN_VARETE_H

#include <utility>
#include <sstream>
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

class VArete
{
private:
    int temps, duree;
private:
    sf::Color couleur;
public:
    VArete (int temps, int duree, sf::Color couleur = sf::Color::Cyan);
    virtual ~VArete ();
    VArete (const VArete &va);

    explicit operator string () const;

    friend ostream& operator<< (ostream &o, const VArete &va);

    inline int getTemps() const;
    inline void setTemps(int temps);
    inline int getDuree() const;
    inline void setDuree(int duree);
};

inline int VArete::getTemps() const {
    return temps;
}

inline void VArete::setTemps(int temps) {
    VArete::temps = temps;
}

inline int VArete::getDuree() const
{
    return duree;
}
inline void VArete::setDuree(int duree)
{
    VArete::duree = duree;
}



#endif //PROJETSFML_PACMAN_VARETE_H
