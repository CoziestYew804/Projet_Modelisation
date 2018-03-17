#include "InfoAlgo.h"

const /*static*/ char *InfoAlgo::ETATS []= {"LIBRE","OUVERT","FERME"};

InfoAlgo::operator string() const
{
ostringstream oss;

oss << "clef pere = ";

if (pere)
	oss << pere->clef;
else
	oss << "non définie";

oss <<", état = " << ETATS[etat] << ", coût = " << c<<", h = " << h <<", g = "<< g;

return oss.str();
}


