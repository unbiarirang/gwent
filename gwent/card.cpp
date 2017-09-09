#include "card.h"

std::ostream & operator<<(std::ostream & os, const Card * m)
{
	os << "the card's id is: " << m->u_id << " name is: " << m->name;
	return os;
}