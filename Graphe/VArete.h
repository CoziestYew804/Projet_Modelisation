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
    int _temps, _duree, dir;
public:


private:
    inline void setDir (int dir);
    sf::Color couleur;
public:
    VArete (int dir,int temps, int duree, sf::Color couleur = sf::Color::Cyan);
    virtual ~VArete ();
    VArete (const VArete &va);

    explicit operator string () const;
    void operator--();
    void rechauffe();

    friend ostream& operator<< (ostream &o, const VArete &va);

    inline int getDir () const;
    inline int get_temps() const;
    inline void set_temps(int _temps);
};

inline void VArete::setDir (int dir)
{
    VArete::dir = dir;
}


inline int VArete::getDir () const
{
    return dir;
}

inline int VArete::get_temps() const {
    return _temps;
}

inline void VArete::set_temps(int temps) {
    VArete::_temps = temps;
}



#endif //PROJETSFML_PACMAN_VARETE_H
