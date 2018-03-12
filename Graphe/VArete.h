//
// Created by arnaud on 01/03/18.
//

#ifndef PROJETSFML_PACMAN_VARETE_H
#define PROJETSFML_PACMAN_VARETE_H

#include <utility>
#include <sstream>
#include <string>

using namespace std;

class VArete
{
private:
    int dir, temp;
    inline void setDir (int dir);
public:
    VArete (int dir, int temp = 0);
    virtual ~VArete ();
    VArete (const VArete &va);

    explicit operator string () const;
    void operator--();
    void rechauffe();

    friend ostream& operator<< (ostream &o, const VArete &va);

    inline int getDir () const;
    inline int getTemp () const;
    inline void setTemp (int temp);
};

inline void VArete::setDir (int dir)
{
    VArete::dir = dir;
}

inline void VArete::setTemp (int temp)
{
    VArete::temp = temp;
}

inline int VArete::getDir () const
{
    return dir;
}

inline int VArete::getTemp () const
{
    return temp;
}


#endif //PROJETSFML_PACMAN_VARETE_H
