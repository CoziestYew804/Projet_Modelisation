//
// Created by arnaud on 09/03/18.
//

#include "VArete.h"

VArete::VArete (int dir, int temp) : dir(dir), temp(temp)
{}

VArete::~VArete ()
= default;

VArete::VArete (const VArete &va): dir(va.dir), temp(va.temp)
{}

VArete::operator string () const
{
    ostringstream oss;

    oss << "VArete : Dir : " << dir << " temp : " << temp;
    return oss.str();
}

ostream &operator<< (ostream &o, const VArete &va)
{
    o << (string)va;
}

void VArete::operator-- ()
{
    if(temp > 0)
    {
        temp--;
    }
}

void VArete::rechauffe ()
{
    this->temp = 5;
}