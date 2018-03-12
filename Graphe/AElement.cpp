//
// Created by arnaud on 22/01/18.
//

#include "AElement.h"

AElement::AElement(const int clef):clef(clef) {}



ostream & operator << (ostream & os, const AElement& aElement)
{
    return os << (string) aElement;
}

AElement::operator string() const
{
    ostringstream o;
    o << "Clef = " << clef;
    return o.str();
}
