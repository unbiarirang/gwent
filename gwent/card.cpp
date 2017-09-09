#include "card.h"

std::ostream & operator<<(std::ostream & os, const Card * m)
{
	os << "the card's id is: " << m->u_id << " name is: " << m->name;
	return os;
}

ID Card::getID()
{
	return u_id;
}

int Card::getStrength()
{
	return u_strength;
}

int Card::getArmor()
{
	return u_armor;
}

void Card::changeStrength(int v)
{
	u_strength = u_strength + v;
}

void Card::changeArmor(int v)
{
	u_armor = u_armor + v;
}
